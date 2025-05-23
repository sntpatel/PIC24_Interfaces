/*****************************************************************************
 *
 * SYSTEM_PROCESS 
 *
 *****************************************************************************
 * FileName:        SystemProcess.h
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
#ifndef SYSTEM_PROCESS_H
#define SYSTEM_PROCESS_H


#define IDLE_STATE           0
#define MENU_STATE           1
#define FAULT_STATE          2
#define SILENCE_STATE        3
#define FIRE_STATE           4
#define EVAC_STATE           5
#define TESTMODE_STATE       6
#define RESET_STATE          7

/**************  EVENTS Flag****************/
typedef struct EventFlag_s
{
   unsigned char HooterIsolate_flg;

}EventFlags_t;

extern EventFlags_t Event;
void SystemInitialise(void);
void SystemProcess_Task(void);
void SetSystemState(unsigned char);
unsigned char GetSystemState(void);
/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif 

