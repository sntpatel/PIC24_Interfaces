/*****************************************************************************
 *
 * KEYPAD 
 *
 *****************************************************************************
 * FileName:        Keypad.h
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
#ifndef KEYPAD_H
#define KEYPAD_H

#define NORMAL_PRESSTIME_CNT    2  //100ms  -> 20ms x5
#define LONG_PRESSTIME_CNT      250  //5000ms  -> 20ms x5
#define IDLETIME_CNT            3  

typedef enum KeyId
{
   NO_KEY,
  /* Matrix Key */
   ESC_KEY,
   KEY_1,
   KEY_2,
   KEY_3,

   UP_KEY,
   KEY_4,
   KEY_5,
   KEY_6,

   DN_KEY,
   KEY_7,
   KEY_8,
   KEY_9,   

   LT_KEY,
   RT_KEY,
   KEY_0,
   EN_KEY,

 /* Direct Key */

   MENU_KEY,
   SILENCE_KEY,   
   EVAC_KEY,
   RESET_KEY,

   NO_OF_KEYIDS,
}KeyId_t;

typedef struct KeyState_S
{
   unsigned  short KeyFlag;
   unsigned  short Pressed;
   unsigned  short Released;
   unsigned  short ReleaseTimeCnt;
   unsigned  int   PressTimeCnt;
}KeyState_t;

void Keypad_Init(void);
void Keypad_Task(void);
unsigned char GetKey(void);
KeyState_t* KeyArr(void);
unsigned char ISKeyFlag(void);
void ClearKeyFlag(void);
unsigned char GetKeyChar(void);

//Alphanumeric Keypad functions
void AlphaNumKeypad_Init(void );
void AlphaNumKeypad(void);
void AlphaNumEnable(void);
void AlphaNumDisable(void);
unsigned char IsAlphaNumEnable(void);
/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif 

