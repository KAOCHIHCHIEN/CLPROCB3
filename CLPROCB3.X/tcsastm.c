#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "tcsastm.h"
#include "mSYSFlag.h"
#include "mcc_generated_files/pin_manager.h"
#include "delay.h"

#define PULL_DELAY_TIME 18
#define P_DELAY_TIME 18

uint8_t button_irq_flag;

button_type Button;

unsigned int other_delay_time;

unsigned char lock_delay_time;
unsigned char k2_delay_time;
unsigned char k2_A_delay_time;
unsigned char hot_delay_time;
unsigned char set_delay_time;
unsigned char cool_delay_time;
unsigned char soda_delay_time;
unsigned char all_delay_time;
unsigned char button_push_flag;

unsigned char lock_push_flag;
unsigned char hot_push_flag;
unsigned char soda_push_flag;
unsigned char cool_push_flag;
unsigned char set_push_flag;

unsigned char has_TCSA_count;

static unsigned char Button_Mode;

uint8_t TCSA_Device_ID(void) {
    return I2C1_Read1ByteRegister(DEVICEADDRESS, TOUCH_RESET_START_ADDR);
}

void TCSA_LED_Updata(void) {
    if (Button_Mode) {
        /* IO */
        Hot_Touch_SetDigitalInput();
        Warm_Touch_SetDigitalInput();
        Cold_Touch_SetDigitalInput();
        if (!HOT_TC_LED()) {
            Hot_Touch_SetDigitalOutput();
            Hot_Touch_SetLow();
        }
        if (!COLD_TC_LED()) {
            Cold_Touch_SetDigitalOutput();
            Cold_Touch_SetLow();
        }
        if (!WARM_TC_LED()) {
            Warm_Touch_SetDigitalOutput();
            Warm_Touch_SetLow();
        }

        TSLED_LAT = BGLED();

    } else {
        /* I2C */
        I2C1_Write1ByteRegister(DEVICEADDRESS, TOUCH_LED_ADDR, LED.byte);
    }
}

void i2c_led_ck(uint8_t led) {
    I2C1_Write1ByteRegister(DEVICEADDRESS, TOUCH_LED_ADDR, led);
}

uint8_t i2c_button_ck(void) {
    return I2C1_Read1ByteRegister(DEVICEADDRESS, TOUCH_BUTTON_ADDR);
}

uint8_t i2c_LS_ck(void) {
    uint8_t tmp;
    tmp = (uint8_t) I2C1_Read1ByteRegister(DEVICEADDRESS, TOUCH_LS_ADDR);
    return tmp;
}

//uint8_t i2c_ID_ck(void) {
//    uint8_t tmp;
//    tmp = (uint8_t) I2C1_Read1ByteRegister(DEVICEADDRESS, TOUCH_RESET_START_ADDR);
//    return tmp;
//}
//
//void i2c_Button_irq(void) {
//    button_irq_flag = 1;
//}

void TCSA_Service_Initialize(unsigned char mode) {

    uint8_t Device_ID;
    
    Button_Mode = mode;

    if (Button_Mode == BUTTON_I2C_MODE) {
        has_TCSA_count = 50;
        for (int i = 0; i < 3; i++) {
            CLRWDT();
            delay_1ms(1000);
            Device_ID = I2C1_Read1ByteRegister(DEVICEADDRESS, TOUCH_RESET_START_ADDR);
            if (Device_ID == 0x02 || Device_ID == 0x03) {
                break;
            } else {
                TS_5V_SetHigh();
                delay_1ms(100);
                TS_5V_SetLow();
                delay_1ms(100);
            }
        }
    }

    //
    //    button_irq_flag = 0;
}

void TCSA_Service_Mainloop(void) {

    if (Button_Mode) {
        /* IO */
        Hot_Touch_SetDigitalInput();
        Warm_Touch_SetDigitalInput();
        Cold_Touch_SetDigitalInput();

        NOP();
        NOP();
        NOP();
        NOP();

        Button.bits.p0 = Hot_Touch_GetValue();
        Button.bits.p1 = Warm_Touch_GetValue();
        Button.bits.p2 = Cold_Touch_GetValue();
        Button.bits.p3 = 1;

        Button.bits.p4 = 1;
        Button.bits.p5 = 1;
        Button.bits.p6 = 1;
        Button.bits.p7 = 1;

        if (!HOT_TC_LED()) {
            Hot_Touch_SetDigitalOutput();
            Hot_Touch_SetLow();
        }
        if (!COLD_TC_LED()) {
            Cold_Touch_SetDigitalOutput();
            Cold_Touch_SetLow();
        }
        if (!WARM_TC_LED()) {
            Warm_Touch_SetDigitalOutput();
            Warm_Touch_SetLow();
        }

        TSLED_LAT = BGLED();
        /* IO END */
    } else {
        /* I2C */
//        Device_ID = I2C1_Read1ByteRegister(DEVICEADDRESS, TOUCH_RESET_START_ADDR);
//        if (Device_ID == 0x02 || Device_ID == 0x03) {
//            has_TCSA_count = 50;
//            err_TCSA_flag = 0;
//        } else {
//            if (has_TCSA_count != 0) {
//                has_TCSA_count--;
//                delay_1ms(100);
//            } else {
//                err_TCSA_flag = 1;
//            }
//        }

        Button.byte = i2c_button_ck();

        i2c_led_ck(LED.byte);

        if (Button.byte == 0) {
            return;
        }

        lock_button_flag = !Button.bits.p4;
        Button.bits.p4 = 1;
        /* I2C END */

    }

    // HOT
    if (Button.byte == 0xFE) {
        //        if (!Button.bits.p0) {
        if (hot_delay_time != 0) {
            hot_delay_time--;
        } else {
            if (!button_push_flag) {
                button_push_flag = 1;
                hot_button_flag = 1;
            }
        }
    }// WARM
    else if (Button.byte == 0xFD) {
        //        else if (!Button.bits.p1) {
        if (soda_delay_time != 0) {
            soda_delay_time--;
        } else {
            if (!button_push_flag) {
                button_push_flag = 1;
                soda_button_flag = 1;
            }
        }
    }// set
    else if (Button.byte == 0xF7) {
        //        else if (!Button.bits.p3) {
        if (set_delay_time != 0) {
            set_delay_time--;
        } else {
            if (!button_push_flag) {
                set_button_flag = 1;
                button_push_flag = 1;
            }
        }
    }// Cold
    else if (Button.byte == 0xFB) {
        //        else if (!Button.bits.p2) {
        if (cool_delay_time != 0) {
            cool_delay_time--;
        } else {
            if (!button_push_flag) {
                cool_button_flag = 1;
                button_push_flag = 1;
            }
        }
    }// Key2
    else if (Button.byte == 0xF9) {
        //        else if ((!Button.bits.p1) & (!Button.bits.p2)) {
        if (k2_delay_time != 0) {
            k2_delay_time--;
        } else {
            if (!button_push_flag) {
                k2_button_flag = 1;
                button_push_flag = 1;
            }
        }
    } else if (Button.byte == 0xFA) {
        //        else if ((!Button.bits.p0) & (!Button.bits.p2)) {
        if (k2_A_delay_time != 0) {
            k2_A_delay_time--;
        } else {
            if (!button_push_flag) {
                k2_A_button_flag = 1;
                button_push_flag = 1;
            }
        }
    }//    
    else if (Button.byte == 0xF8) {
        //        else if ((!Button.bits.p0) & (!Button.bits.p1) & (!Button.bits.p2)) {
        if (all_delay_time != 0) {
            all_delay_time--;
        } else {
            if (!button_push_flag) {
                all_on_button_flag = 1;
                button_push_flag = 1;
            } else {
                if (k2_button_flag == 1) {
                    k2_button_flag = 2;
                }
            }
        }
    }// ALL OFF
    else if (Button.byte == 0xFF) {
        //        else if ((Button.bits.p0) & (Button.bits.p1) & (Button.bits.p2) & (Button.bits.p3)) {
        hot_delay_time = PULL_DELAY_TIME;
        cool_delay_time = PULL_DELAY_TIME;
        soda_delay_time = PULL_DELAY_TIME;
        set_delay_time = PULL_DELAY_TIME;
        all_delay_time = PULL_DELAY_TIME;
        k2_delay_time = PULL_DELAY_TIME;
        k2_A_delay_time = PULL_DELAY_TIME;
        other_delay_time = P_DELAY_TIME;
        k2_button_flag = 0;
        k2_A_button_flag = 0;
        hot_button_flag = 0;
        cool_button_flag = 0;
        soda_button_flag = 0;
        set_button_flag = 0;
        all_on_button_flag = 0;
        button_push_flag = 0;
    } else {
        if (other_delay_time != 0) {
            other_delay_time--;
        } else {
            button_push_flag = 1;
            hot_delay_time = PULL_DELAY_TIME;
            cool_delay_time = PULL_DELAY_TIME;
            soda_delay_time = PULL_DELAY_TIME;
            set_delay_time = PULL_DELAY_TIME;
            all_delay_time = PULL_DELAY_TIME;
            k2_delay_time = PULL_DELAY_TIME;
            k2_A_delay_time = PULL_DELAY_TIME;
        }
    }

    if (hot_button_flag) {
        if (Button.bits.p0) {
            hot_button_flag = 0;
        }
    }
    if (soda_button_flag) {
        if (Button.bits.p1) {
            soda_button_flag = 0;
        }
    }
    if (cool_button_flag) {
        if (Button.bits.p2) {
            cool_button_flag = 0;
        }
    }
}