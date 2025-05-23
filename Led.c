/*****************************************************************************
 *
 * LED 
 *
 *****************************************************************************
 * FileName:        Led.c
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
 * Sanat Patel			21/12/13	...	
 * 
 *****************************************************************************/
#include "system.h"
#include "Led.h"
//global Definition

//Locals
static void LED_LogicHandler(void);
/*********************************************************************
 * Function:       AlarmBlink_Task
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Used when Alarm condion occur and Alarm LED blinking required 
 *
 ********************************************************************/
void AlarmBlink_Task(void)
{
   static unsigned char LedStateCount;

   LED_LogicHandler();
  // if(Get_AlarmLedBlinkFlag())
   {
      if(LedStateCount< (BLINK_ON_COUNT + BLINK_OFF_COUNT))
      {
         LedStateCount++; 
      }
      else
      {
         LedStateCount = 0; 
      }

      if(LedStateCount<BLINK_ON_COUNT)
      {
         FIREALARM_LED = LED_ON;  
      }
      else if((LedStateCount>=BLINK_ON_COUNT) && (LedStateCount<(BLINK_ON_COUNT + BLINK_OFF_COUNT)))
      {
         FIREALARM_LED = LED_OFF;  
      }
   }
//   else
   {
      ;//Do nothing for now
   }
}

/*********************************************************************
 * Function:       LED_LogicHandler
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Used for handling the logical scenario  to decide which 
 *                  State the Led should be in specific Condition 
 *
 ********************************************************************/
static void LED_LogicHandler(void)
{
  
   // if Fire and Fault co exists
   // if silenced and fault created
   // if Fire sileced and fault 
}


