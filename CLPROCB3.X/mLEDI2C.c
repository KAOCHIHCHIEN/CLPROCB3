#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mLEDI2C.h"
#include "mSYSFlag.h"
#include "delay.h"

unsigned char push_flag;

extern uint8_t mTMP_max_offset_mode;

void LEDI2C_Service_Initialize(void) {

    LEDI2C_Device_ID = 0;
    
    for (int i = 0; i < 3; i++) {
        CLRWDT();
        delay_1ms(1000);
        LEDI2C_Device_ID = I2C1_Read1ByteRegister(LEDI2C_DEVICEADDRESS, LEDI2C_RESET_START_ADDR);
        if (LEDI2C_Device_ID == LEDI2C_DEVICE_ID) {
            mTMP_max_offset_mode = I2C1_Read1ByteRegister(LEDI2C_DEVICEADDRESS, LEDI2C_TEMP_OFFSET_ADDR);
            break;
        }
    }
}

unsigned char LEDI2C_ID_READ(void) {
    return I2C1_Read1ByteRegister(LEDI2C_DEVICEADDRESS, LEDI2C_RESET_START_ADDR);
}

unsigned char LEDI2C_TEMP_OFFSET_READ(void) {
    return I2C1_Read1ByteRegister(LEDI2C_DEVICEADDRESS, LEDI2C_TEMP_OFFSET_ADDR);
}

void LEDI2C_LED_Updata(void) {
    I2C1_Write1ByteRegister(LEDI2C_DEVICEADDRESS, LEDI2C_LED_ADDR, LEDI2C_LED.byte);
}

void LEDI2C_Button_Updata(void) {
        LEDI2C_BUTTON.byte = I2C1_Read1ByteRegister(LEDI2C_DEVICEADDRESS, LEDI2C_BUTTON_ADDR);
        LEDI2C_button_flag = LEDI2C_BUTTON.bits.p0;
}

void LEDI2C_SET_TEMP_OFFSET(unsigned char offset) {
    I2C1_Write1ByteRegister(LEDI2C_DEVICEADDRESS, LEDI2C_TEMP_OFFSET_ADDR, offset);
}