/* 
 * File:   mKey.h
 * Author: KaoChihChien
 *
 * Created on January 21, 2021, 11:43 AM
 */

#ifndef MKEY_H
#define	MKEY_H

#ifdef	__cplusplus
extern "C" {
#endif

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

void CK_Buttons_key4(void);

unsigned char hot_key (void);

unsigned char warm_key (void);

unsigned char cold_key (void);

unsigned char hotLock_key (void);

unsigned char all_on_key(void);

void re_hot_key(void);

void re_warm_key(void);

void re_cold_key(void);

void re_hotLock_key(void);

void re_all_on_key(void);

#define KEY_LED_ON 1
#define KEY_LED_OFF 0

void set_hot_led(unsigned char on_off);

void set_warm_led(unsigned char on_off);

void set_cold_led(unsigned char on_off);

void set_hotLock_led(unsigned char on_off);


#ifdef	__cplusplus
}
#endif

#endif	/* MKEY_H */

