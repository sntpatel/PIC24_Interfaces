/*****************************************************************************
 *
 * RELAYS 
 *
 *****************************************************************************
 * FileName:        ProcessRelays.h
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
 * Sanat Patel			14/12/13	...	
 * 
 *****************************************************************************/
#ifndef PROCESSRELAYS_H
#define PROCESSRELAYS_H

typedef enum
{
   Z1 = 1,
   Z2,
   Z3,
   Z4,
   Z5,
   Z6,
   Z7,
   Z8,
   COMM_HOOTER,
   COMM_FIRE,
   COMM_FAULT,
   ZONE_RESET,
   BATT_CHECK,
   TOTAL_RELAYS
}Relays_t;


#define RLY_Z1            _LATA15
#define RLY_Z2            _LATA14
#define RLY_Z3            _LATA5
#define RLY_Z4            _LATA4
#define RLY_Z5            _LATF12
#define RLY_Z6            _LATF13
#define RLY_Z7            _LATA1
#define RLY_Z8            _LATA9
#define RLY_COMM_HOOTER   _LATG3
#define RLY_COMM_FIRE     _LATD11
#define RLY_COMM_FAULT    _LATD10
#define RLY_ZONE_RESET    _LATD9
#define RLY_BATT_CHECK    _LATD8

struct RelayFlag
{
   unsigned ON_Flag   : 1;
   unsigned ON_State  : 1;
};   
extern struct RelayFlag Relay[13];
void InitRelay(void);
void ProcessRelay_Task(void);

/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif 



