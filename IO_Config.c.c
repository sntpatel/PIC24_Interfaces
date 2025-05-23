/*****************************************************************************
 *
 * Timer 
 *
 *****************************************************************************
 * FileName:        IO_Config.c
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
 * Sanat Patel			27/12/13	...	
 * 
 *****************************************************************************/
#include "system.h"

//global Definition

//Locals

/*********************************************************************
 * Function:        IO_DirectionSet
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Initializes IO Dirction for use.
 *
 ********************************************************************/
void IO_DirectionSet(void)
{
//Dirtect keys
   _TRISC1 = 1; //Menu Key
   _TRISC2 = 1; //Silence Key
   _TRISC3 = 1; //Evacuation Key
   _TRISC4 = 1; //Reset Key

//Zone Input Analoge 
   _TRISB0 = 1; //ZONE 1 
   _TRISB1 = 1; //ZONE 2 
   _TRISB2 = 1; //ZONE 3 
   _TRISB3 = 1; //ZONE 4 
   _TRISB4 = 1; //ZONE 5 
   _TRISB5 = 1; //ZONE 6 
   _TRISB6 = 1; //ZONE 7 
   _TRISB7 = 1; //ZONE 8

//Monitoring
   _TRISB8 = 1; //Comm Hooter
   _TRISB9 = 1; // Battery fault
   //_TRISB10 = 1; // AC Fault 
   _TRISB11 = 1; // AC Fault Currently RB11  (EX 2 )

//DIP SW
   _TRISE7 = 1; // SW_1
   _TRISG9 = 1; // SW_2
   _TRISA0 = 1; // SW_3
   _TRISE8 = 1; // SW_4

//Matrix Keypad
   _TRISD0 = 0; // ROW 1
   _TRISD1 = 0; // ROW 2
   _TRISD2 = 0; // ROW 3
   _TRISD3 = 0; // ROW 4
   _TRISD4 = 1; // COL 1
   _TRISD5 = 1; // COL 2
   _TRISD6 = 1; // COL 3
   _TRISD7 = 1; // COL 4

//LEDS
   _TRISF0  = 0; //SYSTEMON_LED
   _TRISF1  = 0; //ZONEISOLATED_LED
   _TRISG0  = 0; //HOOTERFLT_LED
   _TRISG1  = 0; //ZONECKTFLT_LED
   _TRISA6  = 0; //BATTFLT_LED
   _TRISA7  = 0; //ACFLT_LED
   _TRISG12 = 0; //FIREALARM_LED
   _TRISG13 = 0; //SILENCE_LED
   _TRISG14 = 0; //COMMFLT_LED
   _TRISG15 = 0; //EVACUATE_LED

//LCD
   _TRISE0 = 0; //
   _TRISE1 = 0; //
   _TRISE2 = 0; //
   _TRISE3 = 0; //
   _TRISE4 = 0; // LCD_EN
   _TRISE5 = 0; // LCD_RS
   _TRISE6 = 0; // BL

//RELAY
   _TRISG3  = 0; // R1
   _TRISD11 = 0; // R2
   _TRISD10 = 0; // R3
   _TRISD9  = 0; // R4
   _TRISD8  = 0; // R5

   _TRISA15  = 0; // RLY_Z1
   _TRISA14  = 0; // RLY_Z2
   _TRISA5   = 0; // RLY_Z3
   _TRISA4   = 0; // RLY_Z4
   _TRISF12  = 0; // RLY_Z5
   _TRISF13  = 0; // RLY_Z6
   _TRISA1   = 0; // RLY_Z7
   _TRISA9   = 0; // RLY_Z8

//Misc
   _TRISG2 = 0; // BUZZER

}

