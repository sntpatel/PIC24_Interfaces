/*****************************************************************************
 *
 * Timer 
 *
 *****************************************************************************
 * FileName:        timer.c
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
 * Sanat Patel			26/1213	...	
 * 
 *****************************************************************************/
#include "system.h"


//Local
static unsigned char Flag_1msInt;
static unsigned char Flag_10msInt;
static unsigned char Flag_500msInt;

static unsigned long DelayMs;
/*********************************************************************
 * Function:        TimerInit
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Initializes Timer1 for use.
 *
 ********************************************************************/
void TimerInit(void)
{	
	PR1 = 0x2FF;
	
	IPC0bits.T1IP = 5;
	T1CON = 0b1000000000010000;
	IFS0bits.T1IF = 0;

}

/*********************************************************************
 * Function:        TimerIsOverflowEvent
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	Status.
 *
 * Overview:        Checks for an overflow event, returns TRUE if 
 *					an overflow occured.
 *
 * Note:            This function should be checked at least twice
 *					per overflow period.
 ********************************************************************/
unsigned char TimerIsOverflowEvent(void)
{
	if (IFS0bits.T1IF)
	{		
		IFS0bits.T1IF = 0;

		return(1);
	}
	return(0);
}

/*********************************************************************
 * Function:        TimerInit
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Initializes Timer2 for use.
 *
 ********************************************************************/
void Timer2Init(void)
{	
  T2CONbits.T32 = 0; //Set to 16 bit timer
  T2CONbits.TCKPS1 = 0; // prescale 1:1
  T2CONbits.TCKPS0 = 0; // prescale 1:1
  T2CONbits.TCS = 0; // internal clock Fosc/2
  T2CONbits.TGATE = 0;//Gated time accumulation disabled
  PR2 = 0xFA0;      // @ 1ms
  IPC1bits.T2IP = 1;//priority 1 (lowest)
  IEC0bits.T2IE = 1;//Interrupt Enabled
  T2CONbits.TON = 1;//Timer ON
}
void Timer3Init(void)
{	
  T3CONbits.TCKPS1 = 0; // prescale 1:1
  T3CONbits.TCKPS0 = 0; // prescale 1:1
  T3CONbits.TCS = 0; // internal clock Fosc/2
  T3CONbits.TGATE = 0;//Gated time accumulation disabled
  PR3 = 0x9C40;      // @ 10ms
  IPC2bits.T3IP = 6;//priority 6 
  IEC0bits.T3IE = 1;//Interrupt Enabled
  T3CONbits.TON = 1;//Timer ON
}
void Timer4Init(void)
{	
  T4CONbits.T32 = 0; //Set to 16 bit timer
  T4CONbits.TCKPS1 = 1; // prescale 1:64
  T4CONbits.TCKPS0 = 0; // prescale 1:64
  T4CONbits.TCS = 0; // internal clock Fosc/2
  T4CONbits.TGATE = 0;//Gated time accumulation disabled
  PR4 = 0x7A12;      // @ 500ms
  IPC6bits.T4IP = 2;//priority 2 
  IEC1bits.T4IE = 1;//Interrupt Enabled
  T4CONbits.TON = 1;//Timer ON
}

void __attribute__((interrupt,no_auto_psv)) _T2Interrupt(void)
{
	IFS0bits.T2IF =0;					//Clear interrupt status bit
   Flag_1msInt = TRUE;
   TaskRateCount1ms();
}
void __attribute__((interrupt,no_auto_psv)) _T3Interrupt(void)
{
	IFS0bits.T3IF =0;					//Clear interrupt status bit
    Flag_10msInt = TRUE;
    TaskRateCount10ms();
}
void __attribute__((interrupt,no_auto_psv)) _T4Interrupt(void)
{
	IFS1bits.T4IF =0;					//Clear interrupt status bit
    Flag_500msInt = TRUE;
    TaskRateCount500ms();
}
unsigned char GetFlag_1msInt(void)
{
   return Flag_1msInt;
}
unsigned char GetFlag_10msInt(void)
{
   return Flag_10msInt;
}
unsigned char GetFlag_500msInt(void)
{
   return Flag_500msInt;
}
void SetFlag_1msInt(unsigned char SetValue)
{
   Flag_1msInt = SetValue;
}
void SetFlag_10msInt(unsigned char SetValue)
{
   Flag_10msInt = SetValue;
}
void SetFlag_500msInt(unsigned char SetValue)
{
   Flag_500msInt = SetValue;
}

/**************************** Delay function*********************************/

unsigned long GetDelayms(void)
{
   return DelayMs;
}
void SetDelayms(unsigned int delay)
{
   DelayMs = delay;
}
/*********************************************************************
 * EOF
 ********************************************************************/
