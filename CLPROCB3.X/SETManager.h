/* 
 * File:   SETManager.h
 * Author: KaoChihChien
 *
 * Created on February 17, 2022, 10:13 AM
 */

#ifndef SETMANAGER_H
#define	SETMANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif

uint8_t SET1_flag;
uint8_t SET2_flag;
uint8_t SET3_flag;
uint8_t SET4_flag;
uint8_t SET5_flag;
uint8_t SET6_flag;
uint8_t SET7_flag;
uint8_t SET8_flag;
uint8_t SET9_flag;

#define KEY4_SET SET9_flag
#define SYNC_SET SET8_flag
#define TDON_SET SET7_flag
#define CONTINUOUS_WATER_SET SET6_flag
//#define HOT_DELAY_SET SET6_flag
#define UV_SET SET5_flag
#define PUH_SET SET4_flag
#define MLK_SET SET3_flag
#define HOT_SET SET2_flag
#define HAETING_LED SET1_flag


#ifdef	__cplusplus
}
#endif

#endif	/* SETMANAGER_H */

