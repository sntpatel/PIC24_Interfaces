/*****************************************************************************
 *
 * Buzzer 
 *
 *****************************************************************************
 * FileName:        Buzzer.c
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
#include "Buzzer.h"

#define BUZZER_ON  1
#define BUZZER_OFF 0 
#define BEEP_ON_TIME 5
#define BEEP_OFF_TIME 5
#define FAULTBEEP_ON_TIME 20
#define FAULTBEEP_OFF_TIME 20
#define FASTBEEP_ON_TIME 5
#define FASTBEEP_OFF_TIME 5

#define  BUZZER _LATG2 
//Locals

static unsigned char  FaultbeepEn;
static unsigned char  FastbeepEn;
static unsigned int  NoofBeep;
static unsigned int  BeepCnt;
static unsigned int  FaultBeepCnt;
static unsigned char  BuzzerOn;
static unsigned char  BuzzerState;


void ProceesBuzzer_Task(void)
{
   switch(BuzzerState)
   {
      case OFF:
      {
         BUZZER = BUZZER_OFF;
      }
      break;
      case ON:
      {
         BUZZER = BUZZER_ON;
      }
      break;
      case FAULT_BEEP:
      { 
         if(FaultBeepCnt < (FAULTBEEP_ON_TIME + FAULTBEEP_OFF_TIME))
         {
            FaultBeepCnt++;
         }
         else
         {
            FaultBeepCnt = 0;
         }  
         if(FaultBeepCnt < FAULTBEEP_ON_TIME)
         {
            BUZZER = BUZZER_ON;
         }
         else if((FaultBeepCnt >= FAULTBEEP_ON_TIME)&&
                 (FaultBeepCnt < (FAULTBEEP_ON_TIME+FAULTBEEP_OFF_TIME)))
         {
            BUZZER = BUZZER_OFF;
         }
      }
      break;
      case FAST_BEEP:
      {
         if(FaultBeepCnt < (FASTBEEP_ON_TIME + FASTBEEP_OFF_TIME))
         {
            FaultBeepCnt++;
         }
         else
         {
            FaultBeepCnt = 0;
         }  
         if(FaultBeepCnt < FASTBEEP_ON_TIME)
         {
            BUZZER = BUZZER_ON;
         }
         else if((FaultBeepCnt >= FASTBEEP_ON_TIME)&&
                 (FaultBeepCnt < (FASTBEEP_ON_TIME+FASTBEEP_OFF_TIME)))
         {
            BUZZER = BUZZER_OFF;
         }
      }
      break;
      case CHIME_BEEP:
      {
         if( BuzzerState == OFF)
         {
            BUZZER = BUZZER_OFF;
         }
         else
         {
         if((NoofBeep))
         {
            if(BeepCnt < (BEEP_ON_TIME+ BEEP_OFF_TIME))
            {
               BeepCnt++;
            }
            else
            {
               BeepCnt = 0;
            }  
            if(BeepCnt < BEEP_ON_TIME)
            {
               BUZZER = BUZZER_ON;
            }
            else if((BeepCnt >= BEEP_ON_TIME)&&(BeepCnt < (BEEP_ON_TIME+BEEP_OFF_TIME)))
            {
               BUZZER = BUZZER_OFF;
               
            }
            else if(BeepCnt >= (BEEP_ON_TIME+BEEP_OFF_TIME))
            {
                NoofBeep--;
            }     
         }
         }
      }
      default:
      break;
   }
}


void SetBuzzerState(unsigned char SetVal)
{
   BuzzerState = SetVal;
}
unsigned char GetBuzzerState(void)
{
   return BuzzerState;
}

void SetNoofBeep(unsigned char SetVal)
{
   NoofBeep = SetVal;
   BuzzerState = CHIME_BEEP;
}

void SartFaultBeep(void)
{
   FaultbeepEn = TRUE;
   if(BuzzerState != FAST_BEEP)
   {
      BuzzerState = FAULT_BEEP;
   }
}

void StopFaultBeep(void)
{
   FaultbeepEn = FALSE;
   BuzzerState = OFF;
}
void SartFastBeep(void)
{
   FastbeepEn = TRUE;
   BuzzerState = FAST_BEEP;
}
void BuzzerON(void)
{
   BuzzerOn = TRUE;
   BuzzerState = ON;
}
void BuzzerOFF(void)
{
   BuzzerOn = FALSE;
   BuzzerState = OFF;
//   BUZZER = BUZZER_OFF;
}

