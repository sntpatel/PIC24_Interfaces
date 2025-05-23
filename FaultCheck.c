/*****************************************************************************
 *
 * Fault 
 *
 *****************************************************************************
 * FileName:        FaultCheck.c
 * Dependencies:    system.h
 * Processor:       PIC24
 * Compiler:        MPLAB C30
 * Linker:          MPLAB LINK30
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
 * Functions to setup timer and detect overflow
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sanat Patel			26/12/03	...	
 * 
 *****************************************************************************/
#include "system.h"
#include "Led.h"
#include "ProcessADC.h"




extern Zone_t ZoneArr[24];
 

Faulttype_t FaultArr[NO_OF_FAULTS];

uint8_t FaultBits;
uint8_t FlagBits;




//************************************************************************

void CheckSystemFaults(void)
{
   CheckACFault();
   CheckZoneFault();
   CheckZoneIsolateFault();

}

void SetFaultFlag(Faulttype_t SetVal)
{ 
    uint16_t faultCount;
    for ( faultCount = 0 ; faultCount < NO_OF_FAULTS; faultCount++)
    {
       if(faultCount == SetVal)
       {
           FaultArr[faultCount] = TRUE;
       }
    }   
}
unsigned char GetFaultFlag(Faulttype_t GetVal)
{ 
    uint16_t faultCount;
    for ( faultCount = 0 ; faultCount < NO_OF_FAULTS; faultCount++)
    {
       if(faultCount == GetVal)
       {
           return FaultArr[faultCount];
       }
    }
   return 0;   
}


void CheckACFault(void)
{
   static uint16_t AdcValue = 0;
//ACFLT_LED = 0;

  /* if(AC_FAIL == 1)
   { Flag.ACFault = TRUE; }
   else
   {Flag.ACFault = FALSE; }
*/
   AdcValue =ADC_Read10bit(11);//ADC_CHANNEL_ZONE1);
   
   if(AdcValue >1000)
   {
      ACFLT_LED = 0;
      FaultBits |= AC_FAULT_BITMASK;
   }
   else
   {
      ACFLT_LED = 1;
      FaultBits &= ~AC_FAULT_BITMASK;
   }
  
}
void CheckZoneFault(void)
{
   static uint8_t zno;

   for(zno =1; zno < NUM_OF_ZONES; zno++)
   {
      if( (ZoneArr[zno].fault_flg == FALSE)&&
          ((ZoneArr[zno].short_flg == TRUE) ||
          (ZoneArr[zno].open_flg == TRUE) ||
          (ZoneArr[zno].isolate_flg == TRUE)) )
      {
         ZoneArr[zno].fault_flg = TRUE; 
      }
      else if( (ZoneArr[zno].fault_flg == TRUE)&&
          (ZoneArr[zno].normal_flg == TRUE) &&
          (ZoneArr[zno].isolate_flg == FALSE) ) 
      {
         ZoneArr[zno].fault_flg = FALSE; 
      } 
   }
   for(zno =1; zno < NUM_OF_ZONES; zno++)
   {
      if(ZoneArr[zno].fault_flg == TRUE)
      {
         //Zone Ckt Fault LED = ON
         FaultBits |= ZONE_FAULT_BITMASK;
         break;
      } 
      else
      {
         FaultBits &= ~ZONE_FAULT_BITMASK;
      }
   }
}

void CheckZoneIsolateFault(void)
{
   static uint8_t zno;

   for(zno =1; zno < NUM_OF_ZONES; zno++)
   {
      if(ZoneArr[zno].isolate_flg == TRUE)
      {
         //Zone Isolate LED = ON
         FaultBits |= ZONEISO_FAULT_BITMASK;
         break;
      } 
      else
      {
         FaultBits &= ~ZONEISO_FAULT_BITMASK;
      }
   }
}
void CheckCommonFault(void)
{
   if(FaultBits&0xFF)
   {
      //Common Fult LED ON;
      FlagBits |= COMMON_FAULT_ON;
   }
   else
   {
     //Common Fult LED OFF;
      FlagBits &= ~COMMON_FAULT_ON;
   }

}


unsigned char GetFaultBits(void)
{
   return FaultBits;
}
unsigned char GetFlagBits(void)
{
   return FlagBits;
}
/*****************************************************************************/

unsigned char IsFault(void)
{
   unsigned char Flag=0x00;

   Flag |= FlagBits&COMMON_FAULT_ON;

   if(Flag == COMMON_FAULT_ON)
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}

/*****************************************************************************
 * EOF
 *****************************************************************************/

