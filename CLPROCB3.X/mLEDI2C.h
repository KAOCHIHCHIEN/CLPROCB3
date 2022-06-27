/* 
 * File:   mLEDI2C.h
 * Author: KaoChihChien
 *
 * Created on December 9, 2021, 6:31 PM
 */

#ifndef MLEDI2C_H
#define	MLEDI2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LEDI2C_DEVICE_ID 3

#define LEDI2C_RESET_START_ADDR 0x00
#define LEDI2C_BUTTON_ADDR       0x01
#define LEDI2C_LED_ADDR          0x02
#define LEDI2C_TEMP_OFFSET_ADDR          0x03
    
#define LEDI2C_DEVICEADDRESS 2
#define LEDI2C_DEVICEADDRESSMASK 127

unsigned char LEDI2C_Device_ID;

    typedef unsigned char m_byte;

    typedef struct { // ?????
        unsigned char p0 : 1;
        unsigned char p1 : 1;
        unsigned char p2 : 1;
        unsigned char p3 : 1;
        unsigned char p4 : 1;
        unsigned char p5 : 1;
        unsigned char p6 : 1;
        unsigned char p7 : 1;
    } m_bits;

    typedef union {
        m_bits bits;
        m_byte byte;
    } m_type;

    m_type LEDI2C_LED;
    m_type LEDI2C_BUTTON;

    unsigned char LEDI2C_button_flag;
    unsigned char LEDI2C_TEMP_OFFSET;
    
    void LEDI2C_Service_Initialize(void);
    void LEDI2C_LED_Updata(void);
    void LEDI2C_Button_Updata(void);
    unsigned char LEDI2C_TEMP_OFFSET_READ(void);
    void LEDI2C_SET_TEMP_OFFSET(unsigned char offset);
    unsigned char LEDI2C_ID_READ(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MLEDI2C_H */

