#include "mcc_generated_files/pin_manager.h"
#include "mSYSFlag.h"
#include "UVManager.h"

#define UV_CK_TIMER 2

uint8_t uv_error_count;
uint8_t uv_ck_flag;

void mUV_Initialize(void) {
    UVS_MCU_LAT = 0;
    UV_ERROR_FLAG = 0;
    uv_error_count = 0;
    uv_ck_flag = 0;
    UV_CK_time = UV_CK_TIMER;
}

void mUV_Loop(void) {

    if (HOT_SET) {
        if (ColdWaterOut_LAT | WarmWaterOut_LAT | MDWaterOut_LAT) {

            UVS_MCU_LAT = 1;

            if (UV_CK_time == 0) {
                if (UV_CK_MCU_PORT) {
                    if (!uv_ck_flag) {
                        uv_ck_flag = 1;
                        uv_error_count++;
                        if (uv_error_count > 5) {
                            if (!UV_ERROR_FLAG) {
                                UV_ERROR_FLAG = 1;
                            }
                        }
                    }
                } else {
                    uv_error_count = 0;
                    UV_ERROR_FLAG = 0;
                }
            }
        } else {
            uv_ck_flag = 0;
            UVS_MCU_LAT = 0;
            UV_CK_time = UV_CK_TIMER;
        }
    } else {

        if (ColdWaterOut_LAT | WarmWaterOut_LAT | HotWaterOut_LAT | MDWaterOut_LAT) {

            UVS_MCU_LAT = 1;

            if (UV_CK_time == 0) {
                if (UV_CK_MCU_PORT) {
                    if (!uv_ck_flag) {
                        uv_ck_flag = 1;
                        uv_error_count++;
                        if (uv_error_count > 5) {
                            if (!UV_ERROR_FLAG) {
                                UV_ERROR_FLAG = 1;
                            }
                        }
                    }
                } else {
                    uv_error_count = 0;
                    UV_ERROR_FLAG = 0;
                }
            }
        } else {
            uv_ck_flag = 0;
            UVS_MCU_LAT = 0;
            UV_CK_time = UV_CK_TIMER;
        }
    }

    if (UV_ERROR_FLAG) {
        if (!UV_CK_MCU_PORT) {
            uv_error_count = 0;
            UV_ERROR_FLAG = 0;
        }
    }

}