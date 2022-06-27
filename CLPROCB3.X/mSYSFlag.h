/* 
 * File:   mSYSFlag.h
 * Author: KaoChihChien
 *
 * Created on May 21, 2021, 8:13 AM
 */

#ifndef MSYSFLAG_H
#define	MSYSFLAG_H

#ifdef	__cplusplus
extern "C" {
#endif

// SET flag
uint8_t SET1_flag;
uint8_t SET2_flag;
uint8_t SET3_flag;
uint8_t SET4_flag;
uint8_t SET5_flag;
uint8_t SET6_flag;
uint8_t SET7_flag;
uint8_t SET8_flag;
uint8_t SET9_flag;

#define TMP_DW_SET SET9_flag 
#define SYNC_SET SET8_flag 
//#define TDON_SET SET7_flag 
#define COMMUNICATION_SET SET7_flag
#define KEY_OUT_LOCK_SET SET6_flag 
#define UV_SET SET5_flag 
#define PUH_SET SET4_flag 
#define MLK_SET SET3_flag
#define HOT_SET SET2_flag
#define S20_SET SET1_flag
//#define FL_SET SET1_flag

// Error flag
uint8_t UV_err_flag;
#define UV_ERROR_FLAG UV_err_flag

// LED Flag
uint8_t LED_SYS_flag;
#define LED_SYS_ON_OFF_FLAG LED_SYS_flag
uint8_t LED2_SYS_flag;
#define LED2_SYS_ON_OFF_FLAG LED2_SYS_flag


// BUTTON Flag
unsigned char lock_button_flag;
unsigned char hot_button_flag;
unsigned char cool_button_flag;
unsigned char soda_button_flag;
unsigned char set_button_flag;
unsigned char all_on_button_flag;
unsigned char k2_button_flag;
unsigned char k2_A_button_flag;

#define LOCK_BUTTON() lock_button_flag
#define HOT_BUTTON() hot_button_flag
#define COLD_BUTTON() cool_button_flag
#define WARM_BUTTON() soda_button_flag
#define SET_BUTTON() set_button_flag
#define ALL_BUTTON() all_on_button_flag
#define K2_BUTTON() k2_button_flag
#define K2_A_BUTTON() k2_A_button_flag

#define RE_LOCK_BUTTON() do { lock_button_flag = 0; } while(0)
#define RE_HOT_BUTTON() do { hot_button_flag = 0; } while(0)
#define RE_COLD_BUTTON() do { cool_button_flag = 0; } while(0)
#define RE_WARM_BUTTON() do { soda_button_flag = 0; } while(0)
#define RE_SET_BUTTON() do { set_button_flag = 0; } while(0)
#define RE_ALL_BUTTON() do { all_on_button_flag = 0; } while(0)
#define RE_K2_BUTTON() do { k2_button_flag = 0; } while(0)
#define RE_K2_A_BUTTON() do { k2_A_button_flag = 0; } while(0)

typedef unsigned char sfr_byte;
    
typedef struct { // ?????
    unsigned char p0 : 1;
    unsigned char p1 : 1;
    unsigned char p2 : 1;
    unsigned char p3 : 1;
    unsigned char p4 : 1;
    unsigned char p5 : 1;
    unsigned char p6 : 1;
    unsigned char p7 : 1;
} p_bits;

typedef union { // ?????
    p_bits bits; // ??????
    sfr_byte byte;
} button_type;

button_type LED;

#define COLD_TC_LED()           LED.bits.p4
#define COLD_TC_LED_SET(x)     do { LED.bits.p4 = x; } while(0)
#define COLD_TC_LED_OFF()     do { LED.bits.p4 = 1; } while(0)
#define COLD_TC_LED_ON()     do { LED.bits.p4 = 0; } while(0)

#define WARM_TC_LED()           LED.bits.p5
#define WARM_TC_LED_SET(x)     do { LED.bits.p5 = x; } while(0)
#define WARM_TC_LED_OFF()     do { LED.bits.p5 = 1; } while(0)
#define WARM_TC_LED_ON()     do { LED.bits.p5 = 0; } while(0)

#define HOT_TC_LED()            LED.bits.p6
#define HOT_TC_LED_SET(x)     do { LED.bits.p6 = x; } while(0)
#define HOT_TC_LED_OFF()     do { LED.bits.p6 = 1; } while(0)
#define HOT_TC_LED_ON()     do { LED.bits.p6 = 0; } while(0)

#define T100_LED_SET(x) do { LED.bits.p1 = x; } while(0)
#define T100_LED_OFF()     do { LED.bits.p1 = 0; } while(0)
#define T100_LED_ON()     do { LED.bits.p1 = 1; } while(0)

#define T90_LED_SET(x) do { LED.bits.p2 = x; } while(0)
#define T90_LED_OFF()     do { LED.bits.p2 = 0; } while(0)
#define T90_LED_ON()     do { LED.bits.p2 = 1; } while(0)

#define T80_LED_SET(x) do { LED.bits.p3 = x; } while(0)
#define T80_LED_OFF()     do { LED.bits.p3 = 0; } while(0)
#define T80_LED_ON()     do { LED.bits.p3 = 1; } while(0)

#define ECO_LED_SET(x) do { LED.bits.p0 = x; } while(0)
#define ECO_LED_OFF()     do { LED.bits.p0 = 0; } while(0)
#define ECO_LED_ON()     do { LED.bits.p0 = 1; } while(0)

#define BGLED_SET(x) do { LED.bits.p7 = x; } while(0)
#define BGLED_G()     do { LED.bits.p7 = 0; } while(0)
#define BGLED_B()     do { LED.bits.p7 = 1; } while(0)
#define BGLED() LED.bits.p7

#ifdef	__cplusplus
}
#endif

#endif	/* MSYSFLAG_H */

