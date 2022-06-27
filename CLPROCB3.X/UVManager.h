/* 
 * File:   mUV.h
 * Author: KaoChihChien
 *
 * Created on May 21, 2021, 11:25 AM
 */

#ifndef MUV_H
#define	MUV_H

#ifdef	__cplusplus
extern "C" {
#endif

    uint8_t UV_CK_time;

void mUV_Loop(void);
void mUV_Initialize(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MUV_H */

