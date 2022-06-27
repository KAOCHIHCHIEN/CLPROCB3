/* 
 * File:   tcsastm.h
 * Author: KaoChihChien
 *
 * Created on 2021?4?6?, ?? 10:13
 */

#ifndef TCSASTM_H
#define	TCSASTM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TOUCH_RESET_START_ADDR 0x00
#define TOUCH_BUTTON_ADDR       0x01
#define TOUCH_LED_ADDR          0x02
#define TOUCH_LS_ADDR          0x03
    
#define DEVICEADDRESS 1
#define DEVICEADDRESSMASK 127
   

#define BUTTON_I2C_MODE 0
#define BUTTON_IO_MODE 1


    
void TCSA_Service_Initialize(unsigned char mode);
    
void TCSA_Service_Mainloop(void);

void TCSA_LED_Updata(void);

uint8_t TCSA_Device_ID(void);

//void i2c_Button_irq(void);
uint8_t i2c_button_ck(void);
void i2c_led_ck(uint8_t led);
uint8_t i2c_LS_ck(void);
//uint8_t i2c_ID_ck(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TCSASTM_H */

