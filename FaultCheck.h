/*****************************************************************************
 *
 * FaultCheck 
 *
 *****************************************************************************
 * FileName:        FaultCheck.h
 * Dependencies:    
 * Processor:
 * Compiler:
 * Linker:  
 * Company:         Embetron
 *
 * Software License Agreement
 *
 * The software supplied herewith by EMBETRON
 * (the "Company") is intended and supplied to you, the Company's
 * customer, for use solely and exclusively with products manufactured
 * by the Company. 
 *
 * The software is owned by the Company and/or its supplier, and is 
 * protected under applicable copyright laws. All rights are reserved. 
 * Any use in violation of the foregoing restrictions may subject the 
 * user to criminal sanctions under applicable laws, as well as to 
 * civil liability for the breach of the terms and conditions of this 
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES, 
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * This is a simple timer function used to provide quant for state machines
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sanat Patel			26/12/13	...	
 * 
 *****************************************************************************/
#ifndef FAULTCHECK_H
#define FAULTCHECK_H

#include "system.h"
/**********************************************************************
              Fault Bitmask          
**********************************************************************/
#define AC_FAULT_BITMASK 0x01
#define BATT_FAULT_BITMASK 0x02
#define HOOTER_FAULT_BITMASK 0x03
#define ZONE_FAULT_BITMASK 0x04
#define ZONEISO_FAULT_BITMASK 0x05

/**********************************************************************
              Flag Bitmask          
**********************************************************************/
#define ALARM_LED_ON 0x01
#define ALARM_LED_BLINK 0x02
#define EVACUATE_ON 0x03
#define SILENCE_ON 0x04
#define COMMON_FAULT_ON 0x05


typedef enum 
{
  NO_FAULT =0,
  AC_FAULT,
  BATT_FAULT,
  HOOTER_FAULT,
  ZONE_1_FAULT, 
  ZONE_2_FAULT, 
  ZONE_3_FAULT, 
  ZONE_4_FAULT, 
  ZONE_5_FAULT, 
  ZONE_6_FAULT, 
  ZONE_7_FAULT, 
  ZONE_8_FAULT,
  ZONE_9_FAULT, 
  ZONE_10_FAULT, 
  ZONE_11_FAULT,
  ZONE_12_FAULT,
  ZONE_13_FAULT,
  ZONE_14_FAULT,
  ZONE_15_FAULT,
  ZONE_16_FAULT,
  ZONE_17_FAULT,
  ZONE_18_FAULT,
  ZONE_19_FAULT,
  ZONE_20_FAULT,
  ZONE_21_FAULT,
  ZONE_22_FAULT,
  ZONE_23_FAULT,
  ZONE_24_FAULT,
  ZONE_1_ISOLATE,
  ZONE_2_ISOLATE,
  ZONE_3_ISOLATE,
  ZONE_4_ISOLATE,
  ZONE_5_ISOLATE,
  ZONE_6_ISOLATE,
  ZONE_7_ISOLATE,
  ZONE_8_ISOLATE,
  ZONE_9_ISOLATE,
  ZONE_10_ISOLATE,
  ZONE_11_ISOLATE,
  ZONE_12_ISOLATE,
  ZONE_13_ISOLATE,
  ZONE_14_ISOLATE,
  ZONE_15_ISOLATE,
  ZONE_16_ISOLATE,
  ZONE_17_ISOLATE,
  ZONE_18_ISOLATE,
  ZONE_19_ISOLATE,
  ZONE_20_ISOLATE,
  ZONE_21_ISOLATE,
  ZONE_22_ISOLATE,
  ZONE_23_ISOLATE,
  ZONE_24_ISOLATE,
  NO_OF_FAULTS
}Faulttype_t;

void SetFaultFlag(Faulttype_t);
unsigned char GetFaultFlag(Faulttype_t);
unsigned char IsFault(void);
void CheckSystemFaults(void);
void CheckACFault(void);
void CheckZoneFault(void);
void CheckZoneIsolateFault(void);
unsigned char GetFaultBits(void);
unsigned char GetFlagBits(void);
//------------------------------

/*********************************************************************
 * EOF
 ********************************************************************/
#endif

