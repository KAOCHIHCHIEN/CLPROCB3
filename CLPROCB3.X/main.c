/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F15386
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

// Ver : 1.5

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/tmr2.h"
#include "./mcc_generated_files/examples/i2c1_master_example.h"

#include "ACSenserManager.h"
#include "BZManager.h"
#include "LEDManager.h"
#include "SETManager.h"
#include "WaterLeveManager.h"
#include "delay.h"

#include "mTemp.h"
#include "tcsastm.h"
#include "mSET.h"
#include "mSYSFlag.h"
#include "UVManager.h"
#include "mLEDI2C.h"

void Fan_control(void);
void mTest_Mode(void);

#define MHZ 1

#define SET_LED_FLASH_TIME_500MS 5

#define SET_LED_FLASH_TIME_200MS 2

#define SET_LED_FLASH_TIME_100MS 1

#define FAN_OUT_DELAY_TIME 300 * MHZ
unsigned int fan_out_delay;


uint8_t hot_start_flag;

static uint8_t WaterIsInject;
static uint8_t WaterSDIsInject;

#define CAN_NOT_HOT_OUT 0
#define CAN_HOT_OUT 1
static uint8_t waterLevelAState;

static uint8_t UV_ERR_BZ_flag;
static uint8_t Hot_ERR_BZ_flag;

uint16_t water_SD_level_low_delay, water_level_low_delay;

#define WATER_OUT_PROTECTION_TIMER 60 * MHZ
uint16_t Water_out_protection_time;

#define HOT_TMP_MAX 98
#define HOT_TMP_DW_MAX HOT_TMP_MAX - 2

#define SET_TEMP_80 80
#define SET_TEMP_90 90
#define SET_TEMP_100 100

uint8_t mTMP_MAX;

#define TMP_MAX_OFFSET_MODE_H 0
#define TMP_MAX_OFFSET_MODE_M 1
#define TMP_MAX_OFFSET_MODE_L 2
uint8_t mTMP_max_offset_mode;
uint8_t set_mTMP_max_offset_mode;

#define SET_NO_MODE         0
#define SET_HOT_80_MODE     1
#define SET_HOT_90_MODE     2
#define SET_HOT_100_MODE    3
#define SET_ECO_ON_MODE     4
#define SET_ECO_OFF_MODE    5
#define SET_FL_MODE         6
#define TEST_Mode           7
uint8_t SET_Mode;

uint8_t Set_Hot_TEMP;
uint8_t Set_Hot_flag;
#define SET_TIMER         10 * MHZ
uint8_t Set_time;

uint8_t button_irq_flag;

uint8_t hot_temp_to_hi_err;
uint8_t hot_temp_open_err;
uint8_t hot_temp_short_err;
uint8_t hot_temp_no_water_err;
uint8_t hot_temp_heating_time_err;
uint8_t hot_temp_err_flag;
uint16_t hot_temp_err_count;

#define  HEATING_TIME 1800
uint16_t heating_timer;

#define  HEATING_LONG_TIME 3600
uint16_t hot_temp_heating_long_timer;

uint8_t heating_temp;

#define  HEATING_CK 5
uint8_t heating_ck_count;

#define TEST_MODE_TIME 180
uint16_t test_mode_timer;
uint8_t K2_A_Butter_Pull_time;
uint8_t Full_flag;

#define SET_BUTTER_PULL_TIMER 5 * MHZ
uint8_t SET_Butter_Pull_Time;

#define BUTTON_SLEEP_TIMER 10 * MHZ
uint8_t m_key_sleep_time;
uint16_t CK_SODA_Timer;

#define HOT_LOCK_TIME 2 * MHZ
uint8_t m_hot_lock_press_flag;
uint8_t m_hot_lock_time;
uint8_t m_hot_lock_flag;

#define CK_LEVEL_TIMER 10 * MHZ
uint8_t m_ck_level_time;

static uint8_t ck_AC_HEATING_flag;
static uint8_t ck_AC_COOL_flag;
static uint8_t ck_AC_chilling_flag;
static uint8_t ck_AC_Hot_flag;
static uint8_t ck_AC_SODA_flag;

uint8_t Hot_Temp;
uint16_t Hot_adc_v;
uint16_t Hot_adc_add;
uint16_t LI_adc_v;
uint16_t FAN_adc_v;
uint16_t FANdutyValue;

uint8_t Hot_SW_ON_OFF_flag;
uint8_t Hot_SW_ON_OFF_water_in_flag;
uint8_t Hot_SW_ON_OFF_Reheat_flag;
uint8_t Hot_SW_ON_OFF_start_flag;

#define HOT_SW_ON_OFF_DELAY_TIME 5 * MHZ
uint8_t Hot_SW_ON_OFF_water_delay_timer;

#define HOT_SW_DELAY_TIME 5 * MHZ
uint8_t hot_sw_delay_timer;

uint8_t Reheat_flag;

#define HOT_START_TIMER 25 * MHZ
#define HOT_START_CK_TIMER 60 * MHZ
uint8_t hot_start_time;
uint16_t hot_start_ck_time;
uint8_t hot_start_TEMP;


#define FULL_CK_TIMER 5 * MHZ
uint8_t Full_ck_time;

#define LSS_CK_TIMER 5 * MHZ
uint8_t LSS_ck_time;

#define SODA_WATER_CLEAN_TIMER 2 * MHZ
uint8_t soda_water_clean_time;
uint8_t soda_water_clean_flag;

uint8_t hot_water_on_off_flag;
uint8_t warm_water_on_off_flag;
uint8_t cold_water_on_off_flag;

#define ECO_OFF_TIMER 60 * MHZ
#define ECO_OFF_TEST_TIMER 2 * MHZ

#define ECO_ON_RH_TIMER 120 * MHZ
#define ECO_ON_TIMER 600 * MHZ
#define ECO_ON_TEST_TIMER 2 * MHZ
uint8_t eco_on_off_flag;
uint8_t eco_run_flag;
uint16_t eco_on_time;
uint16_t eco_off_time;

uint8_t heating_led_show_count;
uint8_t show_Hot_Temp;

#define HOT_KEY_DELAY_TIMER 3 * MHZ
uint8_t hot_key_delay;

uint8_t err_bz_flag;

uint8_t ls_val_tmep, ls_val_max, ls_val_min;
uint8_t ls_val;
uint16_t st_ls_count;
uint8_t st_ls_flag;
uint8_t LS_ck_delay_time;

uint8_t MDWaterOut_flag;
uint8_t SyncWaterOut_flag;

uint8_t SET_Butter_LCK_flag;
uint8_t All_Butter_Pull_time;
uint8_t k2_Butter_Pull_time;

uint16_t lock_release_time;

uint8_t filter_liter_alarm_bz_flag;

uint16_t MODE_TEST_TIME;

/* LEDI2C Control */
uint8_t LEDI2C_button_pull_flag;
uint8_t LEDI2C_button_pull_count;

#define SHUT_DOWN_MODE 0
#define BOOT_UP_MODE 1
#define SET_MODE 2
uint8_t pwr_mode;

uint8_t ledi2c_set_timer;
/* LEDI2C Control */

#define HOT_WATER_IN_DELAY_20S_TIME 20 * MHZ
#define HOT_WATER_IN_DELAY_10S_TIME 10 * MHZ
#define HOT_WATER_IN_DELAY_8S_TIME 5 * MHZ
uint8_t hot_water_in_delay_timer;

#define HOT_WATER_IN_DELAY_UESR_TIME 5 * MHZ
uint8_t hot_water_in_delay_uesr_timer;

#define HAS_LEDI2C_CK 200
uint8_t has_ledi2c_flag;
uint8_t has_ledi2c_ck_count;
uint8_t has_ledi2c_error;

#define HAS_TCSA_CK 200
uint8_t TCSADeviceID;
uint8_t has_TCSA_time;
uint8_t err_TCSA_flag;
uint8_t has_TCSA_ck_count;

uint8_t waterLevelDetectDelayTimer;
uint8_t waterLevelDetect_flag;
uint8_t waterSDLevelDetect_flag;
uint8_t waterLevelBootDetect_flag;

uint8_t SyncWaterOutDelayTimer;

void TMR0_100ms_irq(void) {
    BZ_MainLoop();
    LEDManager_MainLoop();
}

uint8_t time_1s_t;

void TMR1_1s_irq(void) {

    time_1s_t = ~time_1s_t;

    WaterLeveManager_WaterProtectTimer();

    ACSenserManager_RunTimer();

    if (m_key_sleep_time != 0) {
        m_key_sleep_time--;
    }
    if (m_hot_lock_time != 0) {
        m_hot_lock_time--;
    }
    if (m_ck_level_time != 0) {
        m_ck_level_time--;
    }

    if (fan_out_delay != 0) {
        fan_out_delay--;
    }

    if (UV_CK_time != 0) {
        UV_CK_time--;
    }
    //    mUV_Time_Count();

    if (SET_Butter_Pull_Time != 0) {
        SET_Butter_Pull_Time--;
    }
    if (hot_start_time != 0) {
        hot_start_time--;
    }
    if (hot_start_ck_time != 0) {
        hot_start_ck_time--;
    }
    if (Full_ck_time != 0) {
        Full_ck_time--;
    }
    if (LSS_ck_time != 0) {
        LSS_ck_time--;
    }
    if (hot_key_delay != 0) {
        hot_key_delay--;
    }
    if (Set_time != 0) {
        Set_time--;
    }
    if (Water_out_protection_time != 0) {
        Water_out_protection_time--;
    }
    if (eco_on_time != 0) {
        eco_on_time--;
    }
    if (eco_off_time != 0) {
        eco_off_time--;
    }
    if (LS_ck_delay_time != 0) {
        LS_ck_delay_time--;
    }
    if (test_mode_timer != 0) {
        test_mode_timer--;
    }
    if (MODE_TEST_TIME != 0) {
        MODE_TEST_TIME--;
    }
    if (has_TCSA_time != 0) {
        has_TCSA_time--;
    }
    if (soda_water_clean_time != 0) {
        soda_water_clean_time--;
    }
    if (heating_timer != 0) {
        heating_timer--;
    }
    if (hot_temp_heating_long_timer != 0) {
        hot_temp_heating_long_timer--;
    }
    if (hot_water_in_delay_timer != 0) {
        hot_water_in_delay_timer--;
    }
    if (Hot_SW_ON_OFF_water_delay_timer != 0) {
        Hot_SW_ON_OFF_water_delay_timer--;
    }

    if (hot_water_in_delay_uesr_timer != 0) {
        hot_water_in_delay_uesr_timer--;
    }

    if (hot_sw_delay_timer != 0) {
        hot_sw_delay_timer--;
    }

    if (ledi2c_set_timer != 0) {
        ledi2c_set_timer--;
    }

    if (waterLevelDetectDelayTimer != 0) {
        waterLevelDetectDelayTimer--;
    }

    if (SyncWaterOutDelayTimer != 0) {
        SyncWaterOutDelayTimer--;
    }

    if (CK_SODA_Timer != 0) {
        CK_SODA_Timer--;
    }



}

void modify_mTMP_max_offset(void) {
    if (mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_H) {
        if (!TMP_DW_SET) {
            mTMP_MAX = HOT_TMP_DW_MAX;
        } else {
            mTMP_MAX = HOT_TMP_MAX;
        }
    } else if (mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_M) {
        if (!TMP_DW_SET) {
            mTMP_MAX = HOT_TMP_DW_MAX - 2;
        } else {
            mTMP_MAX = HOT_TMP_MAX - 2;
        }
    } else if (mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_L) {
        if (!TMP_DW_SET) {
            mTMP_MAX = HOT_TMP_DW_MAX - 5;
        } else {
            mTMP_MAX = HOT_TMP_MAX - 5;
        }
    }
}

void UP_Init(void) {
    heating_timer = HEATING_TIME;
    hot_temp_heating_long_timer = HEATING_LONG_TIME;
}

/*
                         Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    TMR1_SetInterruptHandler(TMR1_1s_irq);

    TMR0_SetInterruptHandler(TMR0_100ms_irq);

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    CLRWDT();

    //    WaterLeveManager_InitializeAll();
    WaterLeveManager_Initialize();
    WaterLeveManager_Enable();
    WaterIsInject = DO_NOT_INJECT_WATER;
    WaterSDIsInject = DO_NOT_INJECT_WATER;

    ACSenserManager_InitializeAll();

    TS_5V_SetHigh();

    delay_1ms(100);

    TS_5V_SetLow();

    delay_1ms(500);

    SET_ck();

    /* LEDI2C Control */
    has_ledi2c_error = 0;
    has_ledi2c_flag = 0;
    LEDI2C_Device_ID = 0;
    LEDI2C_button_pull_count = 0;
    LEDI2C_button_pull_flag = 0;
    pwr_mode = BOOT_UP_MODE;
    /* LEDI2C Control */
    mTMP_max_offset_mode = TMP_MAX_OFFSET_MODE_H;
    set_mTMP_max_offset_mode = mTMP_max_offset_mode;
    Set_Hot_TEMP = SET_TEMP_100;

    /* TCSASTM Control */
    err_TCSA_flag = 0;
    /* TCSASTM Control */
    if (COMMUNICATION_SET) {
        TCSA_Service_Initialize(BUTTON_I2C_MODE);
        TCSADeviceID = TCSA_Device_ID();
        LEDI2C_Service_Initialize();
        if (LEDI2C_Device_ID == LEDI2C_DEVICE_ID) {
            mTMP_max_offset_mode = LEDI2C_TEMP_OFFSET_READ();
            set_mTMP_max_offset_mode = mTMP_max_offset_mode;
            has_ledi2c_flag = 1;
        }

    } else {
        TCSA_Service_Initialize(BUTTON_IO_MODE);
        SSP1CON1bits.SSPEN = 0;
        SSP1CLKPPS = 0x00; //RB1->IO;    
        RB1PPS = 0x00; //RB1->IO;    
        RB2PPS = 0x00; //RB2->IO;  
        SSP1DATPPS = 0x00; //RB2->IO;
        TRISBbits.TRISB1 = 1;
        TRISBbits.TRISB2 = 1;
        WPUBbits.WPUB1 = 1;
        WPUBbits.WPUB2 = 1;
    }
    modify_mTMP_max_offset();

    LED_12V_OFF();
    HOT_TC_LED_ON();
    COLD_TC_LED_OFF();
    WARM_TC_LED_OFF();
    BGLED_B();
    TCSA_LED_Updata();
    BZ_user_pushKey(100);
    delay_1ms(500);
    LED_12V_ON();
    HOT_TC_LED_OFF();
    COLD_TC_LED_ON();
    WARM_TC_LED_OFF();
    BGLED_G();
    TCSA_LED_Updata();
    BZ_user_pushKey(100);
    delay_1ms(500);
    LED_12V_OFF();
    HOT_TC_LED_OFF();
    COLD_TC_LED_OFF();
    WARM_TC_LED_ON();
    BGLED_B();
    TCSA_LED_Updata();
    delay_1ms(500);
    LED_12V_ON();
    HOT_TC_LED_OFF();
    COLD_TC_LED_OFF();
    WARM_TC_LED_OFF();
    BGLED_G();
    TCSA_LED_Updata();
    delay_1ms(500);

    // has hot
    Hot_SW_ON_OFF_flag = 0;
    Hot_SW_ON_OFF_water_in_flag = 0;
    Hot_SW_ON_OFF_Reheat_flag = 0;
    Hot_SW_ON_OFF_start_flag = 0;
    //    eco_on_off_flag = (uint8_t) FLASH_ReadWord(0x3FFE);
    //    if (!((eco_on_off_flag == 1) | (eco_on_off_flag == 0))) {
    eco_on_off_flag = 0;
    eco_off_time = 0;
    eco_on_time = 0;
    eco_run_flag = 0;
    //        FLASH_WriteWord(0x3FFE, wdata, eco_on_off_flag);
    //    }

    Reheat_flag = 0;
    SET_Butter_Pull_Time = SET_BUTTER_PULL_TIMER;
    Set_time = 0;
    Set_Hot_flag = 0;

    hot_temp_open_err = 0;
    hot_temp_short_err = 0;
    hot_temp_to_hi_err = 0;
    hot_temp_no_water_err = 0;
    hot_temp_heating_time_err = 0;
    hot_temp_err_flag = 0;
    hot_temp_err_count = 5000;
    hot_water_in_delay_timer = 0;
    hot_water_in_delay_uesr_timer = 0;
    hot_sw_delay_timer = HOT_SW_DELAY_TIME;

    hot_start_time = HOT_START_TIMER;
    hot_start_ck_time = HOT_START_CK_TIMER;

    heating_timer = HEATING_TIME;
    heating_ck_count = HEATING_CK;
    hot_temp_heating_long_timer = HEATING_LONG_TIME;
    heating_temp = Hot_Temp;
    Hot_SW_ON_OFF_water_delay_timer = 0;
    hot_key_delay = 0;
    heating_led_show_count = 0;
    ls_val_tmep = 255;
    st_ls_count = 500;
    ls_val = 0;
    m_hot_lock_time = HOT_LOCK_TIME;
    m_hot_lock_flag = 1;

    for (int i = 0; i < 5; i++) {
        Hot_adc_v = 0;
        Hot_adc_add = Hot_adc_v = adc_get(HOT_ADC_MCU);
        hot_start_TEMP = Hot_Temp = Thermistor(Hot_adc_v);
        delay_1ms(10);
    }
    if (hot_start_TEMP >= 80) {
        hot_start_flag = 0;
    } else {
        hot_start_flag = 1;
    }

    FANdutyValue = 24;
    fan_out_delay = 0;

    soda_water_clean_time = SODA_WATER_CLEAN_TIMER;
    soda_water_clean_flag = 0;

    m_key_sleep_time = BUTTON_SLEEP_TIMER;
    m_ck_level_time = CK_LEVEL_TIMER;

    test_mode_timer = 0;

    // water out
    hot_water_on_off_flag = 0;
    warm_water_on_off_flag = 0;
    cold_water_on_off_flag = 0;
    MDWaterOut_flag = 0;
    SyncWaterOut_flag = 0;

    Full_ck_time = FULL_CK_TIMER;
    Full_flag = 0;
    err_bz_flag = 0;
    filter_liter_alarm_bz_flag = 0;

    LEDManager_Initialize();

    mUV_Initialize();

    Hot_ERR_BZ_flag = 0;
    UV_ERR_BZ_flag = 0;

    waterLevelDetectDelayTimer = 10;
    waterLevelDetect_flag = 0;
    waterSDLevelDetect_flag = 0;
    waterLevelBootDetect_flag = 0;

    LSS_ck_time = LSS_CK_TIMER;

    SET_Mode = SET_NO_MODE;

    CK_SODA_Timer = 0;

    LED_SYS_FLASH();

    while (1) {
        // Add your application code
        CLRWDT();

        LED2_SYS_flag = LED_SYS_flag = LEDManager_GetLEDCommon();

        /* Check Device */
        if (COMMUNICATION_SET) {
            if (err_TCSA_flag) {
                if (has_TCSA_time == 0) {
                    TS_5V_SetHigh();
                    delay_1ms(500);
                    TS_5V_SetLow();
                    delay_1ms(100);
                    has_TCSA_time = 5;
                }
            } else if (has_ledi2c_error) {
                if (has_TCSA_time == 0) {
                    RE_LOCK_BUTTON();
                    RE_HOT_BUTTON();
                    RE_COLD_BUTTON();
                    RE_WARM_BUTTON();
                    RE_SET_BUTTON();
                    RE_ALL_BUTTON();
                    RE_K2_BUTTON();
                    RE_K2_A_BUTTON();
                    warm_water_on_off_flag = 0;
                    hot_water_on_off_flag = 0;
                    cold_water_on_off_flag = 0;
                    TS_5V_SetHigh();
                    delay_1ms(500);
                    TS_5V_SetLow();
                    delay_1ms(100);
                    has_TCSA_time = 10;
                }
            } else {
                has_TCSA_time = 5;
            }
        }
        /* Check Device END */

        /* LEDI2C Control */
        if (has_ledi2c_flag) {

            LEDI2C_Device_ID = LEDI2C_ID_READ();

            if (LEDI2C_Device_ID == LEDI2C_DEVICE_ID) {

                has_ledi2c_ck_count = HAS_LEDI2C_CK;
                has_ledi2c_error = 0;

                LEDI2C_Button_Updata();
                if (LEDI2C_button_flag) {
                    if (pwr_mode == SHUT_DOWN_MODE) {
                        if (!LEDI2C_button_pull_flag) {
                            LEDI2C_button_pull_flag = 1;
                            LEDI2C_button_pull_count = 0;
                            if (pwr_mode == SHUT_DOWN_MODE) {
                                pwr_mode = BOOT_UP_MODE;
                                UP_Init();
                            }
                        }
                    } else {
                        if (LEDI2C_button_pull_count >= 150) {
                            if (!LEDI2C_button_pull_flag) {
                                LEDI2C_button_pull_flag = 1;
                                if (pwr_mode == BOOT_UP_MODE) {
                                    pwr_mode = SHUT_DOWN_MODE;
                                    BZ_RunSet(1, 4);
                                } else if (pwr_mode == SET_MODE) {
                                    mTMP_max_offset_mode = set_mTMP_max_offset_mode;
                                    LEDI2C_SET_TEMP_OFFSET(mTMP_max_offset_mode);
                                    modify_mTMP_max_offset();
                                    pwr_mode = BOOT_UP_MODE;
                                    BZ_RunSet(2, 2);
                                }
                            }
                        } else {
                            LEDI2C_button_pull_count++;
                            delay_1ms(10);
                        }
                    }

                } else {
                    if ((LEDI2C_button_pull_flag == 0) && (LEDI2C_button_pull_count != 0)) {
                        if (pwr_mode == BOOT_UP_MODE) {
                            pwr_mode = SET_MODE;
                            set_mTMP_max_offset_mode = mTMP_max_offset_mode;
                            ledi2c_set_timer = 10;
                        } else if (pwr_mode == SET_MODE) {
                            ledi2c_set_timer = 10;
                            if (set_mTMP_max_offset_mode != TMP_MAX_OFFSET_MODE_H) {
                                set_mTMP_max_offset_mode--;
                            } else {
                                set_mTMP_max_offset_mode = TMP_MAX_OFFSET_MODE_L;
                            }
                        }
                    }
                    LEDI2C_button_pull_count = 0;
                    LEDI2C_button_pull_flag = 0;
                    //                LEDI2C_LED.bits.p4 = 0;
                }

                if (pwr_mode == SET_MODE) {
                    if (ledi2c_set_timer == 0) {
                        pwr_mode = BOOT_UP_MODE;
                    }
                }

                LEDI2C_LED.bits.p4 = 1;

                if (pwr_mode == BOOT_UP_MODE) {
                    LEDI2C_LED.bits.p0 = LED2_LAT;
                    LEDI2C_LED.bits.p1 = LED3_LAT;
                    LEDI2C_LED.bits.p2 = LED4_LAT;
                    LEDI2C_LED.bits.p3 = LED1_LAT;

                    if (hot_temp_err_flag) {
                        if (hot_temp_open_err | hot_temp_short_err) {
                            LEDI2C_LED.bits.p7 = LED_SYS_ON_OFF_FLAG;
                            LEDI2C_LED.bits.p6 = !LED_SYS_ON_OFF_FLAG;
                            LEDI2C_LED.bits.p5 = LED_SYS_ON_OFF_FLAG;
                        } else if (hot_temp_to_hi_err) {
                            LEDI2C_LED.bits.p7 = LED_SYS_ON_OFF_FLAG;
                            LEDI2C_LED.bits.p6 = LED_SYS_ON_OFF_FLAG;
                            LEDI2C_LED.bits.p5 = 0;
                        } else if (hot_temp_no_water_err) {
                            LEDI2C_LED.bits.p7 = LED_SYS_ON_OFF_FLAG;
                            LEDI2C_LED.bits.p6 = 0;
                            LEDI2C_LED.bits.p5 = !LED_SYS_ON_OFF_FLAG;
                        } else if (hot_temp_heating_time_err) {
                            LEDI2C_LED.bits.p7 = LED_SYS_ON_OFF_FLAG;
                            LEDI2C_LED.bits.p6 = LED_SYS_ON_OFF_FLAG;
                            LEDI2C_LED.bits.p5 = LED_SYS_ON_OFF_FLAG;
                        }
                    } else {
                        if (mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_H) {
                            LEDI2C_LED.bits.p7 = 0;
                            LEDI2C_LED.bits.p6 = 0;
                            LEDI2C_LED.bits.p5 = 1;
                        } else if (mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_M) {
                            LEDI2C_LED.bits.p7 = 0;
                            LEDI2C_LED.bits.p6 = 1;
                            LEDI2C_LED.bits.p5 = 0;
                        } else if (mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_L) {
                            LEDI2C_LED.bits.p7 = 1;
                            LEDI2C_LED.bits.p6 = 0;
                            LEDI2C_LED.bits.p5 = 0;
                        }
                    }
                } else if (pwr_mode == SET_MODE) {
                    if (set_mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_H) {
                        LEDI2C_LED.bits.p7 = 0;
                        LEDI2C_LED.bits.p6 = 0;
                        LEDI2C_LED.bits.p5 = LED2_SYS_ON_OFF_FLAG;
                    } else if (set_mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_M) {
                        LEDI2C_LED.bits.p7 = 0;
                        LEDI2C_LED.bits.p6 = LED2_SYS_ON_OFF_FLAG;
                        LEDI2C_LED.bits.p5 = 0;
                    } else if (set_mTMP_max_offset_mode == TMP_MAX_OFFSET_MODE_L) {
                        LEDI2C_LED.bits.p7 = LED2_SYS_ON_OFF_FLAG;
                        LEDI2C_LED.bits.p6 = 0;
                        LEDI2C_LED.bits.p5 = 0;
                    }
                } else if (pwr_mode == SHUT_DOWN_MODE) {
                    LEDI2C_LED.byte = 0;
                }

                LEDI2C_LED_Updata();

                //                while (pwr_mode == SHUT_DOWN_MODE) {
                //
                //                    CLRWDT();
                //
                //                    LED1_LAT = 0;
                //                    LED2_LAT = 0;
                //                    LED3_LAT = 0;
                //                    LED4_LAT = 0;
                //                    RE_HOT_BUTTON();
                //                    RE_WARM_BUTTON();
                //                    RE_COLD_BUTTON();
                //                    RE_SET_BUTTON();
                //                    HotWaterOut_LAT = 0;
                //                    WarmWaterOut_LAT = 0;
                //                    ColdWaterOut_LAT = 0;
                //                    SyncWaterOut_LAT = 0;
                //                    MDWaterOut_LAT = 0;
                //                    HOT_SW_MCU_LAT = 0;
                //                    LED_1_OFF();
                //                    LED_2_OFF();
                //                    LED_3_OFF();
                //                    LED_4_OFF();
                //                    LED_12V_OFF();
                //
                //                    T100_LED_OFF();
                //                    T90_LED_OFF();
                //                    T80_LED_OFF();
                //                    ECO_LED_OFF();
                //                    HOT_TC_LED_OFF();
                //                    COLD_TC_LED_OFF();
                //                    WARM_TC_LED_OFF();
                //                    BGLED_B();
                //                    TCSA_LED_Updata();
                //
                //                    LEDI2C_LED.byte = 0;
                //                    LEDI2C_LED_Updata();
                //
                //                    LEDI2C_Button_Updata();
                //                    if (LEDI2C_button_flag) {
                //                        if (!LEDI2C_button_pull_flag) {
                //                            LEDI2C_button_pull_flag = 1;
                //                            if (pwr_mode == SHUT_DOWN_MODE) {
                //                                pwr_mode = BOOT_UP_MODE;
                //                                UP_Init();
                //                            }
                //                        }
                //                    } else {
                //                        LEDI2C_button_pull_count = 0;
                //                        LEDI2C_button_pull_flag = 0;
                //                    }
                //                    delay_1ms(100);
                //                }
            } else {
                if (has_ledi2c_ck_count != 0) {
                    has_ledi2c_ck_count--;
                } else {
                    has_ledi2c_error = 1;
                }
            }
        } // if (has_ledi2c_flag)
        /* LEDI2C Control END */

        /* Filter_Water CK */
        //        if (FL_SET) {
        //            mFilter_Water_Service_Mainloop(time_1s_t);
        //        }
        /* Filter_Water CK END */

        /* HOT TEMP Control */
        if (HOT_SET) {
            if (pwr_mode == SHUT_DOWN_MODE) {
                ck_AC_Hot_flag = 0;
            }
            if (ck_AC_Hot_flag) {
                // Read ADC
                Hot_adc_add = adc_get(HOT_ADC_MCU);
                if (Hot_adc_add > Hot_adc_v) {
                    Hot_adc_v++;
                } else if (Hot_adc_add < Hot_adc_v) {
                    Hot_adc_v--;
                }

                // Check for short open circuit
                if (Hot_adc_v > 0x3fa || Hot_adc_v < 0x02) {
                    if (hot_temp_err_count != 0) {
                        hot_temp_err_count--;
                    } else {
                        if (Hot_adc_v > 0x3fa) {
                            hot_temp_open_err = 1; // Temp Sensor Open or Short
                        } else if (Hot_adc_v < 0x02) {
                            hot_temp_short_err = 1; // Temp Sensor Open or Short
                        }
                    }
                } else {
                    hot_temp_open_err = 0; // Temp Sensor Open or Short
                    hot_temp_short_err = 0; // Temp Sensor Open or Short
                    hot_temp_err_count = 500;
                }

                // ADC to temperature
                if (hot_temp_open_err == 0 || hot_temp_short_err == 0) {
                    //                if (W1000_SET) {
                    //                    Hot_Temp = Thermistor(Hot_adc_v) + 3;
                    //                } else {
                    Hot_Temp = Thermistor(Hot_adc_v);
                    //                }

                    // Check temperature too high
                    if (Hot_Temp >= HOT_TMP_MAX + 8) {
                        hot_temp_to_hi_err = 1; // Temp Over high
                    } 
//                    else {
//                        hot_temp_to_hi_err = 0; // Temp Over high
//                    }
                }

                // Check temperature error code
                if (hot_temp_open_err | hot_temp_short_err | hot_temp_to_hi_err | hot_temp_no_water_err | hot_temp_heating_time_err) {
                    if (!hot_temp_err_flag) {
                        hot_temp_err_flag = 1;
                        err_bz_flag = 1;
                    }
                    HOT_SW_MCU_SetLow();
                    if (hot_temp_no_water_err) {
                        if (Hot_Temp < 35) {
                            hot_temp_no_water_err = 0;
                            hot_start_TEMP = Hot_Temp;
                            hot_start_flag = 1;
                            hot_start_time = HOT_START_TIMER;
                            hot_start_ck_time = HOT_START_CK_TIMER;
                        }
                    }
                } else {
                    // temperature control
                    if (hot_start_flag) {
                        // Check if there is no water heating
                        if (hot_start_time == 0) {
                            Hot_SW_ON_OFF_start_flag = 0;
                        } else {
                            Hot_SW_ON_OFF_start_flag = 1;
                        }
                        if (hot_start_ck_time == 0) {
                            if (Hot_Temp >= hot_start_TEMP + 20) {
                                hot_temp_no_water_err = 1; // No water heating
                            } else {
                                hot_temp_no_water_err = 0; // No water heating
                            }
                            hot_start_flag = 0;
                        }
                    } else if (Reheat_flag) {
                        if (Hot_Temp >= mTMP_MAX) {
                            Hot_SW_ON_OFF_Reheat_flag = 0;
                            Reheat_flag = 0;
                        } else {
                            Hot_SW_ON_OFF_Reheat_flag = 1;
                        }
                    } else {
                        if (eco_run_flag) {
                            Hot_SW_ON_OFF_flag = 0;
                        } else {
                            if (Set_Hot_TEMP == SET_TEMP_100) {
                                if (Hot_Temp >= mTMP_MAX) {
                                    Hot_SW_ON_OFF_flag = 0;
                                } else if (Hot_Temp <= mTMP_MAX - 4) {
                                    if (SET_Mode == SET_NO_MODE) {
                                        Hot_SW_ON_OFF_flag = 1;
                                    } else {
                                        Hot_SW_ON_OFF_flag = 0;
                                    }
                                }
                            } else {
                                // set TEMP is 90 and 80
                                if (Hot_Temp >= Set_Hot_TEMP) {
                                    Hot_SW_ON_OFF_flag = 0;
                                } else if (Hot_Temp <= Set_Hot_TEMP - 4) {
                                    if (SET_Mode == SET_NO_MODE) {
                                        Hot_SW_ON_OFF_flag = 1;
                                    } else {
                                        Hot_SW_ON_OFF_flag = 0;
                                    }
                                }
                            }
                        }
                    }

                    if (hot_start_flag) {
                        if (Hot_SW_ON_OFF_start_flag) {
                            HOT_SW_MCU_SetHigh();
                        } else {
                            HOT_SW_MCU_SetLow();
                        }
                    } else if (Reheat_flag) {
                        if (SET_Mode == SET_NO_MODE) {
                            if (Hot_SW_ON_OFF_Reheat_flag) {
                                HOT_SW_MCU_SetHigh();
                            } else {
                                HOT_SW_MCU_SetLow();
                            }

                        } else {
                            Hot_SW_ON_OFF_Reheat_flag = 0;
                            HOT_SW_MCU_SetLow();
                            Reheat_flag = 0;
                        }
                    } else {
                        if (SET_Mode == SET_NO_MODE) {
                            if (SYNC_SET) {
                                if (MDWaterOut_LAT) {
                                    Hot_SW_ON_OFF_water_in_flag = 1;
                                    Hot_SW_ON_OFF_water_delay_timer = HOT_SW_ON_OFF_DELAY_TIME;
                                    Reheat_flag = 1;
                                } else {
                                    if (Hot_SW_ON_OFF_water_delay_timer == 0) {
                                        Hot_SW_ON_OFF_water_in_flag = 0;
                                    }
                                }
                            } else {
                                if (SyncWaterOut_LAT) {
                                    Hot_SW_ON_OFF_water_in_flag = 1;
                                    Hot_SW_ON_OFF_water_delay_timer = HOT_SW_ON_OFF_DELAY_TIME;
                                    if (Set_Hot_TEMP == SET_TEMP_100) {
                                        Reheat_flag = 1;
                                    }
                                } else {
                                    if (Hot_SW_ON_OFF_water_delay_timer == 0) {
                                        Hot_SW_ON_OFF_water_in_flag = 0;
                                    }
                                }
                            }

                            if (Hot_SW_ON_OFF_flag | Hot_SW_ON_OFF_water_in_flag) {
                                HOT_SW_MCU_SetHigh();
                            } else {
                                HOT_SW_MCU_SetLow();
                            }
                        } else {
                            HOT_SW_MCU_SetLow();
                        }
                    }

                    hot_temp_err_flag = 0;
                }

                if (HOT_SW_MCU_LAT) {
                    if (heating_temp > Hot_Temp) {
                        heating_temp = Hot_Temp;
                        heating_timer = HEATING_TIME;
                    }
                    if (heating_timer == 0) {
                        if (!(Hot_Temp >= heating_temp + 2)) {
                            hot_temp_heating_time_err = 1;
                        }
                        heating_timer = HEATING_TIME;
                    }
                    if (hot_temp_heating_long_timer == 0) {
                        hot_temp_heating_time_err = 1;
                    }
                } else {
                    heating_timer = HEATING_TIME;
                    hot_temp_heating_long_timer = HEATING_LONG_TIME;
                    //                heating_ck_count = HEATING_CK;
                    heating_temp = Hot_Temp;
                }

            } else { // if (ck_AC_Hot_flag)
                HOT_SW_MCU_SetLow();
                Hot_SW_ON_OFF_flag = 0;
                Reheat_flag = 0;
                hot_start_time = HOT_START_TIMER;
                hot_start_ck_time = HOT_START_CK_TIMER;
                heating_timer = HEATING_TIME;
                hot_temp_heating_long_timer = HEATING_LONG_TIME;
                //            heating_ck_count = HEATING_CK;
                heating_temp = Hot_Temp;
            }
        } // if (HOT_SET)
        /* HOT TEMP Control END */

        /* Show TMEP LED */
        if (HOT_SET) {
            CLRWDT();
            switch (SET_Mode) {
                case SET_NO_MODE:
                    if (ck_AC_Hot_flag) {
                        if (!hot_temp_err_flag) {
                            if (HOT_SW_MCU_LAT) {
                                if (Reheat_flag) {
                                    eco_run_flag = 0;
                                    eco_on_time = ECO_ON_RH_TIMER;
                                }
                                if (eco_run_flag) {
                                    T100_LED_OFF();
                                    T90_LED_OFF();
                                    T80_LED_OFF();
                                } else {

                                    if ((mTMP_MAX < 94) && (Set_Hot_TEMP == SET_TEMP_100)) {
                                        if (Hot_Temp < SET_TEMP_80) {
                                            heating_led_show_count = 1;
                                        } else if (Hot_Temp > SET_TEMP_80 && Hot_Temp < SET_TEMP_90 - 4) {
                                            heating_led_show_count = 2;
                                        } else if (Hot_Temp > SET_TEMP_90 - 4) {
                                            heating_led_show_count = 3;
                                        }
                                    } else {
                                        if (Hot_Temp < SET_TEMP_80) {
                                            heating_led_show_count = 1;
                                        } else if (Hot_Temp > SET_TEMP_80 && Hot_Temp < SET_TEMP_90) {
                                            heating_led_show_count = 2;
                                        } else if (Hot_Temp > SET_TEMP_90) {
                                            heating_led_show_count = 3;
                                        }
                                    }
                                    if (TCSADeviceID == 0x03) {

                                        if (Set_Hot_TEMP == SET_TEMP_80) {
                                            T100_LED_OFF();
                                        } else if (Set_Hot_TEMP == SET_TEMP_90) {
                                            if (heating_led_show_count <= 1) {
                                                T100_LED_ON();
                                            }
                                        } else if (Set_Hot_TEMP == SET_TEMP_100) {
                                            if (heating_led_show_count <= 2) {
                                                T100_LED_ON();
                                            }
                                        }

                                    } else if (TCSADeviceID == 0x02) {
                                        if (heating_led_show_count == 1) {
                                            T100_LED_OFF();
                                            T90_LED_OFF();
                                            T80_LED_SET(LED_SYS_ON_OFF_FLAG);

                                        } else if (heating_led_show_count == 2) {
                                            T100_LED_OFF();
                                            T90_LED_SET(LED_SYS_ON_OFF_FLAG);
                                            T80_LED_ON();

                                        } else if (heating_led_show_count == 3) {
                                            T100_LED_SET(LED_SYS_ON_OFF_FLAG);
                                            T90_LED_ON();
                                            T80_LED_ON();
                                        }
                                    }
                                }
                            } else {
                                if (eco_run_flag) {
                                    T100_LED_OFF();
                                    T90_LED_OFF();
                                    T80_LED_OFF();
                                } else {

                                    if ((mTMP_MAX < 94) && (Set_Hot_TEMP == SET_TEMP_100)) {
                                        if (Hot_Temp < 83) {
                                            show_Hot_Temp = 1;
                                        } else if (Hot_Temp > 83 && Hot_Temp < 86) {
                                            show_Hot_Temp = 2;
                                        } else if (Hot_Temp >= mTMP_MAX - 4) {
                                            show_Hot_Temp = 3;
                                        }
                                    } else {
                                        if (Hot_Temp < 85) {
                                            show_Hot_Temp = 1;
                                        } else if (Hot_Temp > 85 && Hot_Temp < 93) {
                                            show_Hot_Temp = 2;
                                        } else if (Hot_Temp > 93) {
                                            show_Hot_Temp = 3;
                                        }
                                    }

                                    if (TCSADeviceID == 0x03) {
                                        T100_LED_OFF();
                                    } else if (TCSADeviceID == 0x02) {
                                        if (show_Hot_Temp == 1) {
                                            T100_LED_OFF();
                                            T90_LED_OFF();
                                            T80_LED_ON();
                                        } else if (show_Hot_Temp == 2) {
                                            T100_LED_OFF();
                                            T90_LED_ON();
                                            T80_LED_ON();
                                        } else if (show_Hot_Temp == 3) {
                                            T100_LED_ON();
                                            T90_LED_ON();
                                            T80_LED_ON();
                                        }
                                    }
                                }
                            }
                        } else {

                            if (hot_temp_open_err | hot_temp_short_err) {
                                T100_LED_SET(LED_SYS_ON_OFF_FLAG);
                                T90_LED_SET(!LED_SYS_ON_OFF_FLAG);
                                T80_LED_SET(LED_SYS_ON_OFF_FLAG);
                            } else if (hot_temp_to_hi_err) {
                                T100_LED_SET(!LED_SYS_ON_OFF_FLAG);
                                T90_LED_OFF();
                                T80_LED_OFF();
                            } else if (hot_temp_no_water_err) {
                                T100_LED_SET(LED_SYS_ON_OFF_FLAG);
                                T90_LED_OFF();
                                T80_LED_SET(!LED_SYS_ON_OFF_FLAG);
                            } else if (hot_temp_heating_time_err) {
                                T100_LED_SET(LED_SYS_ON_OFF_FLAG);
                                T90_LED_SET(LED_SYS_ON_OFF_FLAG);
                                T80_LED_SET(LED_SYS_ON_OFF_FLAG);
                            }
                        }
                    } else {
                        T100_LED_OFF();
                        T90_LED_OFF();
                        T80_LED_OFF();
                    }

                    if (eco_on_off_flag) {
                        if (pwr_mode == SHUT_DOWN_MODE) {
                            ECO_LED_OFF();
                        } else {
                            ECO_LED_ON();
                        }

                    } else {
                        ECO_LED_OFF();
                    }
                    break;
                case SET_HOT_80_MODE:
                    ECO_LED_OFF();
                    T100_LED_OFF();
                    T90_LED_OFF();
                    T80_LED_SET(LED_SYS_ON_OFF_FLAG);
                    break;
                case SET_HOT_90_MODE:
                    ECO_LED_OFF();
                    T100_LED_OFF();
                    T90_LED_SET(LED_SYS_ON_OFF_FLAG);
                    T80_LED_OFF();
                    break;
                case SET_HOT_100_MODE:
                    ECO_LED_OFF();
                    T100_LED_SET(LED_SYS_ON_OFF_FLAG);
                    T90_LED_OFF();
                    T80_LED_OFF();
                    break;
                case SET_ECO_ON_MODE:
                    ECO_LED_SET(LED_SYS_ON_OFF_FLAG);
                    T100_LED_OFF();
                    T90_LED_OFF();
                    T80_LED_OFF();
                    break;
                case SET_ECO_OFF_MODE:
                    ECO_LED_OFF();
                    T100_LED_OFF();
                    T90_LED_OFF();
                    T80_LED_OFF();
                    break;
                default:
                    break;
            }
        } // if (HOT_SET)
        /* Show TMEP LED END */


        /* ECO Control */
        if (HOT_SET) {
            if (eco_on_off_flag) {
                //                if (LS_ck_delay_time == 0) {
                ls_val = i2c_LS_ck();
                if (ls_val_tmep < ls_val) {
                    ls_val_tmep++;
                } else if (ls_val_tmep > ls_val) {
                    ls_val_tmep--;
                }
                if (eco_run_flag) {
                    if (ls_val_tmep > 15) {
                        if (eco_off_time == 0) {
                            eco_run_flag = 0;
                            if (test_mode_timer != 0) {
                                eco_on_time = ECO_ON_TEST_TIMER;
                            } else {
                                eco_on_time = ECO_ON_TIMER;
                            }
                        }
                    } else {
                        if (test_mode_timer != 0) {
                            eco_off_time = ECO_OFF_TEST_TIMER;
                        } else {
                            eco_off_time = ECO_OFF_TIMER;
                        }
                    }

                } else {
                    if (ls_val_tmep < 10) {
                        if (eco_on_time == 0) {
                            eco_run_flag = 1;
                            if (test_mode_timer != 0) {
                                eco_off_time = ECO_OFF_TEST_TIMER;
                            } else {
                                eco_off_time = ECO_OFF_TIMER;
                            }
                        }
                    } else {
                        if (test_mode_timer != 0) {
                            eco_on_time = ECO_ON_TEST_TIMER;
                        } else {
                            eco_on_time = ECO_ON_TIMER;
                        }
                    }
                }

                if (BGLED()) {
                }//if (BGLED()) 
                else {
                    LS_ck_delay_time = 2;
                } //if (BGLED()) END
            } else { // if (eco_on_off_flag) 
                eco_run_flag = 0;
                eco_on_time = ECO_ON_TIMER;
                LS_ck_delay_time = 2;
            } // if (eco_on_off_flag)  END
        } // if (HOT_SET)
        /* ECO Control END */

        /* FAN Control */
        if (ck_AC_chilling_flag) {
            PWM5_ON();
            fan_out_delay = FAN_OUT_DELAY_TIME;
            Fan_control();
        } else {
            if (fan_out_delay != 0) {
                Fan_control();
            } else {
                PWM5_OFF();
            }
        }
        /* FAN Control END */

        /* BUTTON CK */
        CLRWDT();

        if (COMMUNICATION_SET) {
            TCSADeviceID = TCSA_Device_ID();
            if (TCSADeviceID == 0x02 || TCSADeviceID == 0x03) {
                has_TCSA_ck_count = HAS_TCSA_CK;
                err_TCSA_flag = 0;
            } else {
                if (has_TCSA_ck_count != 0) {
                    has_TCSA_ck_count--;
                } else {
                    err_TCSA_flag = 1;
                    RE_LOCK_BUTTON();
                    RE_HOT_BUTTON();
                    RE_COLD_BUTTON();
                    RE_WARM_BUTTON();
                    RE_SET_BUTTON();
                    RE_ALL_BUTTON();
                    RE_K2_BUTTON();
                    RE_K2_A_BUTTON();
                    warm_water_on_off_flag = 0;
                    hot_water_on_off_flag = 0;
                    cold_water_on_off_flag = 0;
                }
            }
        }

        TCSA_Service_Mainloop();

        if (pwr_mode == SHUT_DOWN_MODE) {
            HOT_TC_LED_OFF();
            COLD_TC_LED_OFF();
            WARM_TC_LED_OFF();
            RE_HOT_BUTTON();
            RE_COLD_BUTTON();
            RE_WARM_BUTTON();
            hot_water_on_off_flag = 0;
            warm_water_on_off_flag = 0;
            cold_water_on_off_flag = 0;

        } else if (SET_Mode == SET_NO_MODE) {
            if (LOCK_BUTTON()) {
                lock_release_time = 1000;
            } else {
                if (lock_release_time != 0) {
                    lock_release_time--;
                }
            }
            if (lock_release_time != 0) {
                if (HOT_BUTTON() | WARM_BUTTON() | COLD_BUTTON()) {
                    m_key_sleep_time = 10;
                }
            }
            if (m_key_sleep_time != 0) {

                if (KEY_OUT_LOCK_SET) {

                    BGLED_G();

                    if (hot_water_on_off_flag) {
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        HOT_TC_LED_ON();
                    } else {
                        HOT_TC_LED_OFF();
                    }
                    if (HOT_SET) {
                        if (HOT_BUTTON()) {
                            if (hot_water_on_off_flag | warm_water_on_off_flag | cold_water_on_off_flag) {
                                hot_water_on_off_flag = 0;
                                warm_water_on_off_flag = 0;
                                cold_water_on_off_flag = 0;
                                BZ_user_pushKey(100);
                                RE_HOT_BUTTON();
                            } else {
                                if (m_hot_lock_flag) {
                                    if (!m_hot_lock_press_flag) {
                                        m_hot_lock_press_flag = 1;
                                        m_hot_lock_time = HOT_LOCK_TIME;
                                        BZ_user_pushKey(100);
                                    }
                                    if (m_hot_lock_press_flag) {
                                        if (m_hot_lock_time == 0) {
                                            m_hot_lock_flag = 0;
                                            BZ_RunSet(2, 2);
                                        }
                                    }
                                } else {
                                    hot_water_on_off_flag = 1;
                                    HOT_TC_LED_ON();
                                    BZ_RunSet(1, 1);
                                    RE_HOT_BUTTON();
                                }

                            }

                            m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        } else {
                            m_hot_lock_press_flag = 0;
                        }
                        // if (HOT_SET)
                    } else {

                        if (hot_water_on_off_flag) {
                            m_key_sleep_time = BUTTON_SLEEP_TIMER;
                            HOT_TC_LED_ON();
                        } else {
                            HOT_TC_LED_OFF();
                        }
                        if (HOT_BUTTON()) {
                            if (hot_water_on_off_flag | warm_water_on_off_flag | cold_water_on_off_flag) {
                                hot_water_on_off_flag = 0;
                                warm_water_on_off_flag = 0;
                                cold_water_on_off_flag = 0;
                            } else {
                                hot_water_on_off_flag = 1;
                                HOT_TC_LED_ON();
                            }
                            BZ_user_pushKey(100);
                            RE_HOT_BUTTON();
                            m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        }
                    }

                    // warm water out
                    if (warm_water_on_off_flag) {
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        WARM_TC_LED_ON();
                    } else {
                        WARM_TC_LED_OFF();
                    }
                    if (WARM_BUTTON()) {
                        if (hot_water_on_off_flag | warm_water_on_off_flag | cold_water_on_off_flag) {
                            hot_water_on_off_flag = 0;
                            warm_water_on_off_flag = 0;
                            cold_water_on_off_flag = 0;
                        } else {
                            warm_water_on_off_flag = 1;
                            WARM_TC_LED_ON();
                        }
                        BZ_user_pushKey(100);
                        RE_WARM_BUTTON();
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                    }

                    if (cold_water_on_off_flag) {
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        COLD_TC_LED_ON();
                    } else {
                        COLD_TC_LED_OFF();
                    }
                    if (COLD_BUTTON()) {
                        if (hot_water_on_off_flag | warm_water_on_off_flag | cold_water_on_off_flag) {
                            hot_water_on_off_flag = 0;
                            warm_water_on_off_flag = 0;
                            cold_water_on_off_flag = 0;
                        } else {
                            cold_water_on_off_flag = 1;
                            COLD_TC_LED_ON();
                        }
                        BZ_user_pushKey(100);
                        RE_COLD_BUTTON();
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                    }

                } else { //if (KEY_OUT_LOCK_SET)

                    HOT_TC_LED_OFF();
                    WARM_TC_LED_OFF();
                    COLD_TC_LED_OFF();
                    BGLED_G();

                    if (HOT_BUTTON()) {
                        if (HOT_SET) {
                            if (!hot_water_on_off_flag) {
                                if (m_hot_lock_flag) {
                                    if (!m_hot_lock_press_flag) {
                                        m_hot_lock_press_flag = 1;
                                        m_hot_lock_time = HOT_LOCK_TIME;
                                        BZ_user_pushKey(100);
                                    }
                                    if (m_hot_lock_press_flag) {
                                        if (m_hot_lock_time == 0) {
                                            m_hot_lock_flag = 0;
                                            BZ_RunSet(2, 2);
                                        }
                                    }
                                } else {
                                    hot_water_on_off_flag = 1;
                                    BZ_RunSet(1, 1);
                                }
                            }
                            m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        } else {// if (HOT_SET)
                            if (!hot_water_on_off_flag) {
                                hot_water_on_off_flag = 1;
                                BZ_user_pushKey(100);
                            }
                            m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        }
                    }//warm 
                    else if (WARM_BUTTON()) {
                        if (!warm_water_on_off_flag) {
                            warm_water_on_off_flag = 1;
                            BZ_user_pushKey(100);
                        }
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                    }// cold 
                    else if (COLD_BUTTON()) {
                        if (!cold_water_on_off_flag) {
                            cold_water_on_off_flag = 1;
                            BZ_user_pushKey(100);
                        }
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                    } else {
                        hot_water_on_off_flag = 0;
                        warm_water_on_off_flag = 0;
                        cold_water_on_off_flag = 0;
                        m_hot_lock_press_flag = 0;
                    }
                } //if (KEY_OUT_LOCK_SET) END

            } else { // if (m_key_sleep_time != 0) 

                HOT_TC_LED_ON();
                WARM_TC_LED_ON();
                COLD_TC_LED_ON();
                BGLED_B();

                if (HOT_BUTTON() | WARM_BUTTON() | COLD_BUTTON()) {
                    if (PUH_SET) {
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        m_hot_lock_time = HOT_LOCK_TIME;
                        m_hot_lock_flag = 1;
                        COM_MCU_SetHigh();
                    } else {
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        m_hot_lock_time = HOT_LOCK_TIME;
                        m_hot_lock_flag = 1;
                        COM_MCU_SetHigh();
                        RE_HOT_BUTTON();
                        RE_WARM_BUTTON();
                        RE_COLD_BUTTON();
                        RE_SET_BUTTON();
                        BZ_user_pushKey(100);
                        delay_1ms(200);
                        BZ_user_pushKey(100);
                    }
                }
            } // if (m_key_sleep_time != 0) END

            if (SET_BUTTON()) {
                if (!SET_Butter_LCK_flag) {
                    BZ_user_pushKey(100);
                    SET_Butter_LCK_flag = 1;
                }
                if (SET_Butter_Pull_Time == 0) {
                    BZ = 1;
                    delay_1ms(500);
                    BZ = 0;
                    delay_1ms(300);
                    BZ = 1;
                    delay_1ms(500);
                    BZ = 0;
                    if (Set_Hot_TEMP == SET_TEMP_80) {
                        SET_Mode = SET_HOT_80_MODE;
                    } else if (Set_Hot_TEMP == SET_TEMP_90) {
                        SET_Mode = SET_HOT_90_MODE;
                    } else if (Set_Hot_TEMP == SET_TEMP_100) {
                        SET_Mode = SET_HOT_100_MODE;
                    }
                    HOT_TC_LED_OFF();
                    WARM_TC_LED_OFF();
                    COLD_TC_LED_OFF();
                    BGLED_G();
                    m_key_sleep_time = BUTTON_SLEEP_TIMER;
                    Set_time = SET_TIMER;
                    SET_Butter_LCK_flag = 0;
                    RE_SET_BUTTON();
                    Set_Hot_flag = 0;
                    Reheat_flag = 0;
                    //                    set_led_sys_flash_time(SET_FLASH_300ms);
                }
            } else {
                if (SET_Butter_LCK_flag) {
                    if (ck_AC_Hot_flag) {
                        BZ = 1;
                        delay_1ms(800);
                        BZ = 0;
                        eco_run_flag = 0;
                        eco_on_time = ECO_ON_RH_TIMER;
                        test_mode_timer = 0;
                        Reheat_flag = 1;
                    }
                    SET_Butter_LCK_flag = 0;
                }
                SET_Butter_Pull_Time = SET_BUTTER_PULL_TIMER;
            }

            if (ALL_BUTTON()) {
                if (test_mode_timer == 0) {
                    All_Butter_Pull_time++;
                    BZ_user_pushKey(100);
                    delay_1ms(600);
                    if (All_Butter_Pull_time > 3) {
                        test_mode_timer = TEST_MODE_TIME;
                        eco_on_time = ECO_ON_TEST_TIMER;
                        eco_off_time = ECO_OFF_TEST_TIMER;
                        eco_on_off_flag = 1;
                        RE_ALL_BUTTON();
                    }
                } else {
                    RE_ALL_BUTTON();
                }
            } else {
                RE_ALL_BUTTON();
                All_Butter_Pull_time = 0;
            }

            if (K2_A_BUTTON()) {
                if (MODE_TEST_TIME == 0) {
                    K2_A_Butter_Pull_time++;
                    BZ_user_pushKey(100);
                    delay_1ms(600);
                    if (K2_A_Butter_Pull_time > 3) {
                        BZ = 1;
                        delay_1ms(1000);
                        BZ = 0;
                        MODE_TEST_TIME = 10;
                        SET_Mode = TEST_Mode;
                        mTest_Mode();
                        RE_K2_A_BUTTON();
                    }
                } else {
                    RE_K2_A_BUTTON();
                }
            } else {
                RE_K2_A_BUTTON();
                K2_A_Butter_Pull_time = 0;
            }
        } else {
            if (HOT_BUTTON()) {
                Set_Hot_flag = 1;
                RE_HOT_BUTTON();
                m_key_sleep_time = BUTTON_SLEEP_TIMER;
            } else if (WARM_BUTTON()) {
                Set_Hot_flag = 1;
                RE_WARM_BUTTON();
                m_key_sleep_time = BUTTON_SLEEP_TIMER;
            } else if (COLD_BUTTON()) {
                Set_Hot_flag = 1;
                RE_COLD_BUTTON();
                m_key_sleep_time = BUTTON_SLEEP_TIMER;
            } else if (SET_BUTTON()) {
                switch (SET_Mode) {
                    case SET_HOT_80_MODE:
                        BZ_user_pushKey(100);
                        Set_time = SET_TIMER;
                        SET_Mode = SET_HOT_90_MODE;
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        break;
                    case SET_HOT_90_MODE:
                        BZ_user_pushKey(100);
                        Set_time = SET_TIMER;
                        SET_Mode = SET_HOT_100_MODE;
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        break;
                    case SET_HOT_100_MODE:
                        BZ_user_pushKey(100);
                        Set_time = SET_TIMER;
                        SET_Mode = SET_ECO_ON_MODE;
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        break;
                    case SET_ECO_ON_MODE:
                        BZ_user_pushKey(100);
                        Set_time = SET_TIMER;
                        SET_Mode = SET_ECO_OFF_MODE;
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        break;
                    case SET_ECO_OFF_MODE:
                        BZ_user_pushKey(100);
                        Set_time = SET_TIMER;
                        SET_Mode = SET_HOT_80_MODE;
                        m_key_sleep_time = BUTTON_SLEEP_TIMER;
                        break;
                    default:
                        break;
                }
                RE_SET_BUTTON();
            }

            if (Set_Hot_flag) {
                switch (SET_Mode) {
                    case SET_HOT_80_MODE:
                        Set_Hot_TEMP = SET_TEMP_80;
                        break;
                    case SET_HOT_90_MODE:
                        Set_Hot_TEMP = SET_TEMP_90;
                        break;
                    case SET_HOT_100_MODE:
                        Set_Hot_TEMP = SET_TEMP_100;
                        break;
                    case SET_ECO_ON_MODE:
                        eco_on_off_flag = 1;
                        //                        FLASH_WriteWord(0x3FFE, wdata, eco_on_off_flag);
                        break;
                    case SET_ECO_OFF_MODE:
                        eco_on_off_flag = 0;
                        //                        FLASH_WriteWord(0x3FFE, wdata, eco_on_off_flag);
                        break;
                    default:
                        break;
                }
                //                FLASH_WriteWord(0x3FFF, wdata, Set_Hot_TEMP);
                RE_SET_BUTTON();
                Set_time = 0;
                Set_Hot_flag = 0;
            } else {
                if (Set_time == 0) {
                    switch (Set_Hot_TEMP) {
                        case SET_TEMP_80:
                            T80_LED_ON();
                            break;
                        case SET_TEMP_90:
                            T90_LED_ON();
                            break;
                        case HOT_TMP_MAX:
                            T100_LED_ON();
                            break;
                        case HOT_TMP_DW_MAX:
                            T100_LED_ON();
                            break;
                        default:
                            break;
                    }
                    ECO_LED_SET(eco_on_off_flag);
                    //                    set_led_sys_flash_time(SET_FLASH_1S);
                    TCSA_LED_Updata();
                    BZ = 1;
                    delay_1ms(800);
                    BZ = 0;
                    delay_1ms(300);
                    BZ = 1;
                    delay_1ms(800);
                    BZ = 0;
                    SET_Mode = SET_NO_MODE;
                    RE_SET_BUTTON();
                }
            }
        }
        /* BUTTON CK END */

        /* Water OUT */
        CLRWDT();
        // Water out protection
        if (HotWaterOut_LAT | WarmWaterOut_LAT | ColdWaterOut_LAT) {

            if (Water_out_protection_time == 0) {
                warm_water_on_off_flag = 0;
                hot_water_on_off_flag = 0;
                cold_water_on_off_flag = 0;
                RE_HOT_BUTTON();
                RE_WARM_BUTTON();
                RE_COLD_BUTTON();
                HotWaterOut_LAT = 0;
                WarmWaterOut_LAT = 0;
                ColdWaterOut_LAT = 0;
                BZ = 1;
                delay_1ms(300);
                BZ = 0;
                delay_1ms(300);
                BZ = 1;
                delay_1ms(300);
                BZ = 0;
            }
        } else {
            Water_out_protection_time = WATER_OUT_PROTECTION_TIMER;
        }

        if (hot_water_on_off_flag) {
            HotWaterOut_LAT = 1;
        } else {
            if (HOT_SET) {
                if (HotWaterOut_LAT) {
                    hot_key_delay = HOT_KEY_DELAY_TIMER;
                }
            }
            HotWaterOut_LAT = 0;
        }

        if (warm_water_on_off_flag) {
            if (hot_key_delay != 0) {
                WarmWaterOut_LAT = 0;
            } else {
                WarmWaterOut_LAT = 1;
            }
        } else {
            WarmWaterOut_LAT = 0;
        }
        if (cold_water_on_off_flag) {
            if (hot_key_delay != 0) {
                ColdWaterOut_LAT = 0;
            } else {
                ColdWaterOut_LAT = 1;
            }
        } else {
            //            if (SYNC_SET) {
            //                if (ColdWaterOut_LAT) {
            //                    SyncWaterOut_LAT = 0;
            //                    delay_1ms(300);
            //                    ColdWaterOut_LAT = 0;
            //                }
            //            } else {
            ColdWaterOut_LAT = 0;
            //            }
        }

        // SODA Water Clean
        if (MLK_SET) {
            if (ck_AC_SODA_flag) {
                if (WarmWaterOut_LAT) {
                    if (soda_water_clean_time == 0) {
                        soda_water_clean_flag = 1;
                    }
                } else {
                    if (soda_water_clean_flag) {
                        //                        if (SYNC_SET) {
                        //                            soda_water_clean_flag = 0;
                        //                            MDWaterOut_LAT = 0;
                        //                            ColdWaterOut_LAT = 1;
                        //                            delay_1ms(1500);
                        //                            SyncWaterOut_LAT = 0;
                        //                            delay_1ms(300);
                        //                            ColdWaterOut_LAT = 0;
                        //
                        //                        } else {
                        soda_water_clean_flag = 0;
                        MDWaterOut_LAT = 0;
                        ColdWaterOut_LAT = 1;
                        delay_1ms(1500);
                        ColdWaterOut_LAT = 0;
                        //                        }
                    }
                    soda_water_clean_time = SODA_WATER_CLEAN_TIMER;
                }
            }
        }

        if (SYNC_SET) {
            if (MDWaterOut_LAT | ColdWaterOut_LAT | WarmWaterOut_LAT | HotWaterOut_LAT) {
                SyncWaterOut_LAT = 1;
                SyncWaterOutDelayTimer = 4;
            } else {
                if (SyncWaterOutDelayTimer == 0) {
                    SyncWaterOut_LAT = 0;
                }
            }

            if (WaterSDIsInject == INJECT_WATER) {
                MDWaterOut_flag = 1;
            } else {
                MDWaterOut_flag = 0;
            }
            if (MDWaterOut_flag) {
                if (!MDWaterOut_LAT) {
                    if (HotWaterOut_LAT) {
                        hot_water_in_delay_uesr_timer = HOT_WATER_IN_DELAY_UESR_TIME;
                    } else {
                        if (S20_SET) {
                            hot_water_in_delay_timer = HOT_WATER_IN_DELAY_20S_TIME;
                        } else {
                            hot_water_in_delay_timer = HOT_WATER_IN_DELAY_8S_TIME;
                        }
                    }
                    if (hot_water_in_delay_uesr_timer == 0 || hot_water_in_delay_timer == 0) {
                        MDWaterOut_LAT = 1;
                    } else {
                        MDWaterOut_LAT = 0;
                    }
                }
            } else {
                MDWaterOut_LAT = 0;
                hot_water_in_delay_uesr_timer = HOT_WATER_IN_DELAY_UESR_TIME;
                if (S20_SET) {
                    hot_water_in_delay_timer = HOT_WATER_IN_DELAY_20S_TIME;
                } else {
                    hot_water_in_delay_timer = HOT_WATER_IN_DELAY_8S_TIME;
                }
            }
        } else { // if (SYNC_SET)

            if (WaterSDIsInject == INJECT_WATER) {
                MDWaterOut_flag = 1;
                if (MLK_SET) {
                    if (MDWaterOut_LAT == 0) {
                        WaterLeveManager_ResetProtectTimer_B();
                    }
                }

            } else {
                MDWaterOut_flag = 0;
            }

            if (MDWaterOut_flag) {
                if (SyncWaterOut_LAT | ColdWaterOut_LAT | HotWaterOut_LAT | WarmWaterOut_LAT) {
                    MDWaterOut_LAT = 0;
                } else {
                    if (MLK_SET) {
                        if (ck_AC_SODA_flag) {
                            MDWaterOut_LAT = 1;
                        } else {
                            MDWaterOut_LAT = 0;
                        }
                    } else {
                        MDWaterOut_LAT = 1;
                    }
                }
            } else {
                MDWaterOut_LAT = 0;
            }

            if (WaterIsInject == INJECT_WATER) {
                SyncWaterOut_flag = 1;
            } else {
                SyncWaterOut_flag = 0;
            }
            if (SyncWaterOut_flag) {
                if (!SyncWaterOut_LAT) {
                    if (HotWaterOut_LAT) {
                        hot_water_in_delay_uesr_timer = HOT_WATER_IN_DELAY_UESR_TIME;
                    } else {
                        if (S20_SET) {
                            hot_water_in_delay_timer = HOT_WATER_IN_DELAY_20S_TIME;
                        } else {
                            hot_water_in_delay_timer = HOT_WATER_IN_DELAY_8S_TIME;
                        }
                    }
                    if (hot_water_in_delay_uesr_timer == 0 || hot_water_in_delay_timer == 0) {
                        SyncWaterOut_LAT = 1;
                    } else {
                        SyncWaterOut_LAT = 0;
                    }
                }
                
                if (HotWaterOut_LAT) {
                    WaterLeveManager_ResetProtectTimer_A();
                }

            } else {
                SyncWaterOut_LAT = 0;
                hot_water_in_delay_uesr_timer = HOT_WATER_IN_DELAY_UESR_TIME;
                if (S20_SET) {
                    hot_water_in_delay_timer = HOT_WATER_IN_DELAY_20S_TIME;
                } else {
                    hot_water_in_delay_timer = HOT_WATER_IN_DELAY_8S_TIME;
                }
            }
        }
        /* Water OUT END */

        /* UV CK */
        CLRWDT();
        if (UV_SET) {
            mUV_Loop();
        }
        /* UV CK END */

        /* Water Level CK */
        CLRWDT();

        if (SYNC_SET) {
            if (m_key_sleep_time != 0) {
                WaterLeveManager_Enable();
            } else {
                if (WaterSDIsInject == DO_NOT_INJECT_WATER) {
                    WaterLeveManager_Disenable();
                }
            }
            WaterSDIsInject = WaterLeveManager_IsInject_B();
            WaterLeveManager_Sync_MainLoop();
        } else {

            if (m_key_sleep_time != 0) {
                WaterLeveManager_Enable();
                CK_SODA_Timer = 10;
            } else {

                if (WaterIsInject == DO_NOT_INJECT_WATER && WaterSDIsInject == DO_NOT_INJECT_WATER) {
                    if (CK_SODA_Timer == 0) {
                        WaterLeveManager_Disenable();
                    }

                } else {
                    CK_SODA_Timer = 10;
                }
            }
            WaterIsInject = WaterLeveManager_IsInject_A();
            WaterSDIsInject = WaterLeveManager_IsInject_B();
            WaterLeveManager_MainLoop();
        }
        /* Water Level CK END */

        /* ALL ON OFF CK */
        if (MDWaterOut_LAT | SyncWaterOut_LAT | ColdWaterOut_LAT | WarmWaterOut_LAT | HotWaterOut_LAT) {
            AllOnOff_SetHigh();
        } else {
            AllOnOff_SetLow();
        }
        /* ALL ON OFF CK END*/

        /* AC CK */
        CLRWDT();
        ACSenserManager_MainLoop();
        ck_AC_HEATING_flag = ACSenserManager_GetPortState(AC_HEATING);
        ck_AC_SODA_flag = ACSenserManager_GetPortState(AC_SODA);
        ck_AC_COOL_flag = ACSenserManager_GetPortState(AC_COOL);
        ck_AC_chilling_flag = ACSenserManager_GetPortState(AC_CHILLING);
        ck_AC_Hot_flag = ACSenserManager_GetPortState(AC_HOT);
        /* AC CK END*/

        /* LED */
        if (((eco_run_flag == 1) && (Reheat_flag == 0)) || (pwr_mode == SHUT_DOWN_MODE)) {
            LED_1_OFF();
            LED_2_OFF();
            LED_3_OFF();
            LED_4_OFF();
            LED_12V_OFF();

        } else {

            LED_1_ON();

            if (MLK_SET) {
                if (ck_AC_SODA_flag) {
                    LED_2_ON();
                } else {
                    LED_2_OFF();
                }
            } else {
                if (ck_AC_COOL_flag) {
                    LED_2_ON();
                } else {
                    LED_2_OFF();
                }
            }

            if (HOT_SET) {
                if (ck_AC_Hot_flag) {
                    LED_3_ON();
                } else {
                    LED_3_OFF();
                }
            } else {
                if (ck_AC_COOL_flag) {
                    LED_3_ON();
                } else {
                    LED_3_OFF();
                }
            }

            if (UV_SET) {
                if (UV_ERROR_FLAG) {
                    LED_4_FLASH();
                } else {
                    if (UV_CK_MCU_PORT) {
                        LED_4_OFF();
                    } else {
                        LED_4_ON();
                    }
                }
            } else {
                if (HOT_SET) {
                    if (ck_AC_HEATING_flag) {
                        LED_4_ON();
                    } else {
                        LED_4_OFF();
                    }
                } else {
                    if (ck_AC_chilling_flag) {
                        LED_4_ON();
                    } else {
                        LED_4_OFF();
                    }
                }
            }
            if (UV_ERROR_FLAG | hot_temp_err_flag) {
                LED_12V_FLASH();
            } else {
                LED_12V_ON();
            }
        }
        /* LED END */

        /* ERRER CK */
        if (UV_ERROR_FLAG) {
            if (!UV_ERR_BZ_flag) {
                UV_ERR_BZ_flag = 1;
                BZ_RunSet(2, 10);
            }
        } else if (hot_temp_err_flag) {
            if (!Hot_ERR_BZ_flag) {
                Hot_ERR_BZ_flag = 1;
                BZ_RunSet(4, 10);
            }
        } else {
            UV_ERR_BZ_flag = 0;
            Hot_ERR_BZ_flag = 0;
        }
        /* ERRER CK END */

        /* FULL Water CK */
        CLRWDT();
        if (!FULL_MCU_PORT) {
            if (Full_ck_time == 0) {
                BZ_RunSet(8, 10);
                Full_flag = 1;
                RE_HOT_BUTTON();
                RE_WARM_BUTTON();
                RE_COLD_BUTTON();
                RE_SET_BUTTON();
                HotWaterOut_LAT = 0;
                WarmWaterOut_LAT = 0;
                ColdWaterOut_LAT = 0;
                SyncWaterOut_LAT = 0;
                MDWaterOut_LAT = 0;
                HOT_SW_MCU_LAT = 0;
                while (Full_flag) {
                    CLRWDT();
                    /* AC CK */
                    ACSenserManager_MainLoop();
                    ck_AC_HEATING_flag = ACSenserManager_GetPortState(AC_HEATING);
                    ck_AC_SODA_flag = ACSenserManager_GetPortState(AC_SODA);
                    ck_AC_COOL_flag = ACSenserManager_GetPortState(AC_COOL);
                    ck_AC_chilling_flag = ACSenserManager_GetPortState(AC_CHILLING);
                    ck_AC_Hot_flag = ACSenserManager_GetPortState(AC_HOT);
                    /* AC CK END*/
                    /* FAN Control */
                    if (ck_AC_chilling_flag) {
                        PWM5_ON();
                        fan_out_delay = FAN_OUT_DELAY_TIME;
                        Fan_control();
                    } else {
                        if (fan_out_delay != 0) {
                            Fan_control();
                        } else {
                            PWM5_OFF();
                        }
                    }
                    /* FAN Control END */
                    LED_12V_FLASH();
                    TCSA_Service_Mainloop();
                    if (HOT_BUTTON() | WARM_BUTTON() | COLD_BUTTON() | SET_BUTTON()) {
                        BZ_RunSet(4, 10);
                        RE_HOT_BUTTON();
                        RE_WARM_BUTTON();
                        RE_COLD_BUTTON();
                        RE_SET_BUTTON();
                    }
                    if (FULL_MCU_PORT) {
                        Full_flag = 0;
                        BZ_release();
                    }
                }
            }
        } else {
            Full_ck_time = FULL_CK_TIMER;
            Full_flag = 0;
        }

        /* FULL Water CK END */

        /* LSS Water CK */
        CLRWDT();
        if (!LSS_MCU_PORT) {
            if (LSS_ck_time == 0) {
                //                set_led_1_flash_time(SET_FLASH_300ms);
                //                set_led_2_flash_time(SET_FLASH_300ms);
                //                set_led_3_flash_time(SET_FLASH_300ms);
                //                set_led_4_flash_time(SET_FLASH_300ms);
                //                set_led_5_flash_time(SET_FLASH_300ms);
                BZ_RunSet(12, 3);
                RE_HOT_BUTTON();
                RE_WARM_BUTTON();
                RE_COLD_BUTTON();
                RE_SET_BUTTON();
                HotWaterOut_LAT = 0;
                WarmWaterOut_LAT = 0;
                ColdWaterOut_LAT = 0;
                SyncWaterOut_LAT = 0;
                MDWaterOut_LAT = 0;
                HOT_SW_MCU_LAT = 0;
                while (1) {
                    CLRWDT();
                    /* AC CK */
                    ACSenserManager_MainLoop();
                    ck_AC_HEATING_flag = ACSenserManager_GetPortState(AC_HEATING);
                    ck_AC_SODA_flag = ACSenserManager_GetPortState(AC_SODA);
                    ck_AC_COOL_flag = ACSenserManager_GetPortState(AC_COOL);
                    ck_AC_chilling_flag = ACSenserManager_GetPortState(AC_CHILLING);
                    ck_AC_Hot_flag = ACSenserManager_GetPortState(AC_HOT);
                    /* AC CK END*/
                    /* FAN Control */
                    if (ck_AC_chilling_flag) {
                        PWM5_ON();
                        fan_out_delay = FAN_OUT_DELAY_TIME;
                        Fan_control();
                    } else {
                        if (fan_out_delay != 0) {
                            Fan_control();
                        } else {
                            PWM5_OFF();
                        }
                    }
                    /* FAN Control END */
                    LED_12V_FLASH();
                    LED_1_FLASH();
                    LED_2_FLASH();
                    LED_3_FLASH();
                    LED_4_FLASH();

                    if (COMMUNICATION_SET) {
                        if (has_ledi2c_flag) {

                            LEDI2C_Device_ID = LEDI2C_ID_READ();

                            if (LEDI2C_Device_ID == LEDI2C_DEVICE_ID) {

                                LEDI2C_LED.bits.p0 = LED12V_LAT;
                                LEDI2C_LED.bits.p1 = LED12V_LAT;
                                LEDI2C_LED.bits.p2 = LED12V_LAT;
                                LEDI2C_LED.bits.p3 = LED12V_LAT;
                                LEDI2C_LED.bits.p4 = LED12V_LAT;
                                LEDI2C_LED.bits.p5 = LED12V_LAT;
                                LEDI2C_LED.bits.p6 = LED12V_LAT;
                                LEDI2C_LED.bits.p7 = LED12V_LAT;

                                LEDI2C_LED_Updata();
                            } else {
                                if (has_TCSA_time == 0) {
                                    TS_5V_SetHigh();
                                    delay_1ms(500);
                                    TS_5V_SetLow();
                                    delay_1ms(100);
                                    has_TCSA_time = 5;
                                }
                            }
                        }

                        TCSADeviceID = TCSA_Device_ID();
                        if (TCSADeviceID == 0x02 || TCSADeviceID == 0x03) {

                        } else {
                            if (has_TCSA_time == 0) {
                                TS_5V_SetHigh();
                                delay_1ms(500);
                                TS_5V_SetLow();
                                delay_1ms(100);
                                has_TCSA_time = 5;
                            }
                        }
                    }

                    HOT_TC_LED_SET(LED12V_LAT);
                    WARM_TC_LED_SET(LED12V_LAT);
                    COLD_TC_LED_SET(LED12V_LAT);

                    TCSA_Service_Mainloop();

                    if (HOT_BUTTON() | WARM_BUTTON() | COLD_BUTTON() | SET_BUTTON()) {
                        BZ_RunSet(6, 3);
                        RE_HOT_BUTTON();
                        RE_WARM_BUTTON();
                        RE_COLD_BUTTON();
                        RE_SET_BUTTON();
                    }
                    //delay_1ms(200);
                }
            }
        } else {
            LSS_ck_time = LSS_CK_TIMER;
        }

        /* LSS Water CK END */
    }
}

void Fan_control(void) {
    FAN_adc_v = adc_get(FAN_ADC);
    if (FAN_adc_v > 220) {
        if (FANdutyValue > 5) {
            FANdutyValue--;
        }
    } else {
        if (FANdutyValue < 600) {
            FANdutyValue++;
        }
    }
    PWM5_LoadDutyValue(FANdutyValue);
}

void mTest_Mode(void) {

    CLRWDT();

    HOT_SW_MCU_SetLow();

    while (SET_Mode == TEST_Mode) {

        HOT_TC_LED_SET(!HotWaterOut_LAT);
        WARM_TC_LED_SET(!WarmWaterOut_LAT);
        COLD_TC_LED_SET(!ColdWaterOut_LAT);

        ls_val = i2c_LS_ck();
        if (ls_val > 15) {
            ECO_LED_OFF();
        } else {
            ECO_LED_ON();
        }

        // Factory TEST
        //        if (FL_SET) {
        //            if (!SET_L8_GetValue()) {
        //                if (WarmWaterOut_LAT) {
        //                    LED_12V_FLASH();
        //                }
        //            } else {
        //                if (ColdWaterOut_LAT) {
        //                    LED_12V_FLASH();
        //                }
        //            }
        //        }

        TCSA_Service_Mainloop();

        AllOnOff_SetHigh();

        CLRWDT();

        if (HOT_BUTTON()) {
            if (HotWaterOut_LAT | WarmWaterOut_LAT | ColdWaterOut_LAT) {
                HotWaterOut_LAT = WarmWaterOut_LAT = ColdWaterOut_LAT = 0;
                MODE_TEST_TIME = 0;
                BZ_user_pushKey(100);
            } else {
                MODE_TEST_TIME = 240;
                BZ_user_pushKey(100);
                HotWaterOut_LAT = 1;
            }

            RE_HOT_BUTTON();

        } else if (WARM_BUTTON()) {
            if (HotWaterOut_LAT | WarmWaterOut_LAT | ColdWaterOut_LAT) {
                HotWaterOut_LAT = WarmWaterOut_LAT = ColdWaterOut_LAT = 0;
                MODE_TEST_TIME = 0;
                BZ_user_pushKey(100);
            } else {
                MODE_TEST_TIME = 240;
                BZ_user_pushKey(100);
                WarmWaterOut_LAT = 1;
            }

            RE_WARM_BUTTON();

        } else if (COLD_BUTTON()) {
            if (HotWaterOut_LAT | WarmWaterOut_LAT | ColdWaterOut_LAT) {
                HotWaterOut_LAT = WarmWaterOut_LAT = ColdWaterOut_LAT = 0;
                MODE_TEST_TIME = 0;
                BZ_user_pushKey(100);
            } else {
                MODE_TEST_TIME = 240;
                BZ_user_pushKey(100);
                ColdWaterOut_LAT = 1;
            }

            RE_COLD_BUTTON();
        }

        // SODA
        ACSenserManager_MainLoop();
        ck_AC_SODA_flag = ACSenserManager_GetPortState(AC_SODA);

        if (MODE_TEST_TIME == 0) {

            HotWaterOut_LAT = 0;
            MDWaterOut_LAT = 0;
            WarmWaterOut_LAT = 0;
            ColdWaterOut_LAT = 0;
            SyncWaterOut_LAT = 0;

            RE_HOT_BUTTON();
            RE_WARM_BUTTON();
            RE_COLD_BUTTON();

            //            LED_CHILLING = 0;
            //            LED_COOL = 0;
            //            LED_HEATING = 0;
            //            LED_UV = 0;
            //            LED_HOT = 0;
            //            LED_SODA = 0;


            m_key_sleep_time = 0;
            m_ck_level_time = 0;

            soda_water_clean_time = SODA_WATER_CLEAN_TIMER;

            BZ_user_pushKey(500);
            delay_1ms(300);
            BZ_user_pushKey(500);
            SET_Mode = SET_NO_MODE;

        } else {

            WaterLeveManager_Enable();
            WaterLeveManager_MainLoop();
            WaterIsInject = WaterLeveManager_IsInject_A();
            WaterSDIsInject = WaterLeveManager_IsInject_B();

            if (SYNC_SET) {
                if (HotWaterOut_LAT | WarmWaterOut_LAT | ColdWaterOut_LAT | MDWaterOut_LAT) {
                    SyncWaterOut_LAT = 1;
                } else {
                    SyncWaterOut_LAT = 0;
                }
            } else {
                if (MDWaterOut_LAT == 0) {
                    if (WaterIsInject == INJECT_WATER) {
                        SyncWaterOut_LAT = 1;
                    } else {
                        SyncWaterOut_LAT = 0;
                    }
                }
            }
            // SODA Water
            if (ck_AC_SODA_flag) {
                if (WaterSDIsInject == INJECT_WATER) {
                    if (SYNC_SET) {
                        MDWaterOut_LAT = 1;
                    } else {
                        if (SyncWaterOut_LAT == 0) {
                            MDWaterOut_LAT = 1;
                        } else {
                            MDWaterOut_LAT = 0;
                        }
                    }
                } else {
                    MDWaterOut_LAT = 0;
                }
            } else {
                MDWaterOut_LAT = 0;
            }
        }
    }
}



/**
 End of File
 */