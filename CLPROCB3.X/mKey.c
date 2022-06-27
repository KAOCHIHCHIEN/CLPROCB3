#include "mcc_generated_files/mcc.h"
#include "mKey.h"

button_type Button;

#define PULL_DELAY_TIME 2
#define P_DELAY_TIME 300

unsigned int other_delay_time;

unsigned char hot_delay_time;
unsigned char hotLock_delay_time;
unsigned char cool_delay_time;
unsigned char sod_delay_time;
unsigned char all_delay_time;
unsigned char button_push_flag;

unsigned char hot_button_flag;
unsigned char cool_button_flag;
unsigned char sod_button_flag;
unsigned char HotLock_button_flag;
unsigned char all_on_button_flag;

unsigned char hot_led_flag;
unsigned char cool_led_flag;
unsigned char sod_led_flag;
unsigned char HotLock_led_flag;

void CK_Buttons_key4(void) {

    HotLock_Touch_SetDigitalInput();
    Hot_Touch_SetDigitalInput();
    Warm_Touch_SetDigitalInput();
    Cold_Touch_SetDigitalInput();
    
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    
    Button.bits.p0 = HotLock_Touch_GetValue();
    Button.bits.p1 = Hot_Touch_GetValue();
    Button.bits.p2 = Warm_Touch_GetValue();
    Button.bits.p3 = Cold_Touch_GetValue();

    Button.bits.p4 = 1;
    Button.bits.p5 = 1;
    Button.bits.p6 = 1;
    Button.bits.p7 = 1;
    
    if (hot_led_flag) {
        Hot_Touch_SetDigitalOutput();
        Hot_Touch_SetLow();
    }
    if (cool_led_flag) {
        Cold_Touch_SetDigitalOutput();
        Cold_Touch_SetLow();
    }
    if (sod_led_flag) {
        Warm_Touch_SetDigitalOutput();
        Warm_Touch_SetLow();
    }
    if (HotLock_led_flag) {
        HotLock_Touch_SetDigitalOutput();
        HotLock_Touch_SetLow();
    }
    
    // HOT LOCK
    if (Button.byte == 0xFE) {
        if (hotLock_delay_time != 0) {
            hotLock_delay_time--;
        } else {
            if (!button_push_flag) {
                button_push_flag = 1;
                HotLock_button_flag = 1;
            }
        }

    }// Hot
    else if (Button.byte == 0xFD) {
        if (hot_delay_time != 0) {
            hot_delay_time--;
        } else {
            if (!button_push_flag) {
                button_push_flag = 1;
                hot_button_flag = 1;

            }
        }

    }// sod
    else if (Button.byte == 0xFB) {
        if (sod_delay_time != 0) {
            sod_delay_time--;
        } else {
            if (!button_push_flag) {
                button_push_flag = 1;
                sod_button_flag = 1;
            }
        }
    }// cool
    else if (Button.byte == 0xF7) {
        if (cool_delay_time != 0) {
            cool_delay_time--;
        } else {
            if (!button_push_flag) {
                cool_button_flag = 1;
                button_push_flag = 1;
            }
        }
    }// ALL ON 
    else if (Button.byte == 0xF8) {
    	if (all_delay_time != 0) {
            all_delay_time--;
        } else {
        	if (!button_push_flag) {
        		all_on_button_flag = 1;
        		button_push_flag = 1;
        	}
        }
    }// ALL OFF
    else if (Button.byte == 0xFF) {
        hot_delay_time = PULL_DELAY_TIME;
    	cool_delay_time = PULL_DELAY_TIME;
    	sod_delay_time = PULL_DELAY_TIME;
    	hotLock_delay_time = PULL_DELAY_TIME;
    	all_delay_time = PULL_DELAY_TIME;
    	other_delay_time = P_DELAY_TIME;
    	hot_button_flag = 0;
    	cool_button_flag = 0;
    	sod_button_flag = 0;
    	HotLock_button_flag = 0;
    	all_on_button_flag = 0;
    	button_push_flag = 0;
    } else {
        if (other_delay_time != 0) {
            other_delay_time--;
        } else {
	        button_push_flag = 1;
	        hot_delay_time = PULL_DELAY_TIME;
	    	cool_delay_time = PULL_DELAY_TIME;
	    	sod_delay_time = PULL_DELAY_TIME;
	    	hotLock_delay_time = PULL_DELAY_TIME;
	    	all_delay_time = PULL_DELAY_TIME;
    	}
    }
}

unsigned char all_on_key(void) {
    return all_on_button_flag;
}

unsigned char hot_key(void) {
    return hot_button_flag;
}

unsigned char warm_key(void) {
    return sod_button_flag;
}

unsigned char cold_key(void) {
    return cool_button_flag;
}

unsigned char hotLock_key(void) {
    return HotLock_button_flag;
}

void re_all_on_key(void) {
     all_on_button_flag = 0;
}

void re_hot_key(void) {
     hot_button_flag = 0;
}

void re_warm_key(void) {
     sod_button_flag = 0;
}

void re_cold_key(void) {
     cool_button_flag = 0;
}

void re_hotLock_key(void) {
     HotLock_button_flag = 0;
}

void set_hot_led(unsigned char on_off) {
    hot_led_flag = on_off;
}

void set_warm_led(unsigned char on_off) {
    sod_led_flag = on_off;
}

void set_cold_led(unsigned char on_off) {
    cool_led_flag = on_off;
}

 void set_hotLock_led(unsigned char on_off) {
     HotLock_led_flag = on_off;
}
 
 