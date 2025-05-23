/*****************************************************************************
 *
 * LED 
 *
 *****************************************************************************
 * FileName:        Led.h
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
 * Sanat Patel			21/12/03	...	
 * 
 *****************************************************************************/
#ifndef LED_H
#define LED_H

#define LED_ON 0
#define LED_OFF 1

#define SYSTEMON_LED     _LATF0 
#define ZONEISOLATED_LED _LATF0
#define HOOTERFLT_LED    _LATG0  
#define ZONECKTFLT_LED   _LATG1 
#define BATTFLT_LED      _LATA6 
#define ACFLT_LED        _LATA7 
#define FIREALARM_LED    _LATG12
#define SILENCE_LED      _LATG13
#define COMMFLT_LED      _LATG14
#define EVACUATE_LED     _LATG15

#define BLINK_ON_COUNT  2
#define BLINK_OFF_COUNT 2

void AlarmBlink_Task(void);

/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif 

