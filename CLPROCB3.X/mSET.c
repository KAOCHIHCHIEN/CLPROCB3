#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"
#include "mSET.h"
#include "mSYSFlag.h"
#include "delay.h"


void SET_ck(void) {
    /* SET CK */
    uint16_t ckSetCount;

    CSET1_SetLow();
    delay_1ms(10);
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET1_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET1_flag = 1;
    } else {
        SET1_flag = 0;
    }
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET2_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET4_flag = 1;
    } else {
        SET4_flag = 0;
    }
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET3_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET7_flag = 1;
    } else {
        SET7_flag = 0;
    }
    CSET1_SetHigh();

    CSET2_SetLow();
    delay_1ms(10);
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET1_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET2_flag = 1;
    } else {
        SET2_flag = 0;
    }
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET2_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET5_flag = 1;
    } else {
        SET5_flag = 0;
    }
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET3_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET8_flag = 1;
    } else {
        SET8_flag = 0;
    }
    CSET2_SetHigh();

    CSET3_SetLow();
    delay_1ms(10);
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET1_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET3_flag = 1;
    } else {
        SET3_flag = 0;
    }
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET2_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET6_flag = 1;
    } else {
        SET6_flag = 0;
    }
    ckSetCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (!RSET3_PORT) {
            ckSetCount++;
        }
    }
    if (ckSetCount > 900) {
        SET9_flag = 1;
    } else {
        SET9_flag = 0;
    }
    CSET3_SetHigh();
    /* SET CK END */
}