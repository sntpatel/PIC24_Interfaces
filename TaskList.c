/*****************************************************************************
 *
 * Timer 
 *
 *****************************************************************************
 * FileName:        Tasklist.c
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
extern void ProceesBuzzer_Task(void);
extern void SystemProcess_Task(void);
extern void RTCCProcessEvents(void);
extern void PSWDExpiration(void); 
static unsigned  long Tick, Delayms;

void List_Task1ms(void)
{
 
   Delayms = GetDelayms();
   if(Delayms)
   {   
      if(Tick < Delayms)
      Tick++;
      else
      {Tick = 0; Delayms = 0;}
   }
   ReadADCZone();
} 
void List_Task10ms(void)
{

   Keypad_Task();
}
void List_Task20ms(void)
{
   ProceesBuzzer_Task();
   SystemProcess_Task();
   if(IsAlphaNumEnable())
    AlphaNumKeypad();  
   SetZoneState_Task();
}
void List_Task80ms(void)
{
//  ProcessRelay_Task();
}
void List_Task100ms(void)
{
    CheckSystemFaults();
//   AlarmBlink_Task(); 
}
void List_Task200ms(void)
{

}
void List_Task500ms(void)
{
 PopupHandler_Task();
}
void List_Task1s(void)
{
   PSWDExpiration();
   RTCCProcessEvents();
}
void List_Task1min(void)
{
   //PSWDExpiration();
}
/*********************************************************************
 * Function:        TaskScheduler
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        execute task  functions as per the task rate in which it is called.
 *
 ********************************************************************/


void TaskScheduler(void)
{
   if(GetFlag_Task1ms())
   {
      List_Task1ms();       
      SetFlag_Task1ms(0);
   }
   if(GetFlag_Task10ms())
   {
      List_Task10ms();       
      SetFlag_Task10ms(0);
   }
   if(GetFlag_Task20ms())
   {
      List_Task20ms();       
      SetFlag_Task20ms(0);
   }
   if(GetFlag_Task80ms())
   {
      List_Task80ms();       
      SetFlag_Task80ms(0);
   }
   if(GetFlag_Task100ms())
   {
      List_Task100ms();       
      SetFlag_Task100ms(0);
   }
   if(GetFlag_Task200ms())
   {
      List_Task200ms();       
      SetFlag_Task200ms(0);
   }
   if(GetFlag_Task500ms())
   {
      List_Task500ms();       
      SetFlag_Task500ms(0);
   }
   if(GetFlag_Task1s())
   {
      List_Task1s();       
      SetFlag_Task1s(0);
   }  
   if(GetFlag_Task1min())
   {
      List_Task1min();       
      SetFlag_Task1min(0);
   }  

}

