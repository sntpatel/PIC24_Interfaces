/*****************************************************************************
 *
 * TaskRateCounter 
 *
 *****************************************************************************
 * FileName:        TaskRateCounter.h
 * Dependencies:    
 * Processor:
 * Compiler:
 * Linker:  
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
 *
 * This is a simple timer function used to provide quant for state machines
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sanat Patel			26/12/13	...	
 * 
 *****************************************************************************/
#ifndef TASKRATECOUNT_H
#define TASKRATECOUNT_H

extern void TaskRateCount1ms(void);
extern void TaskRateCount10ms(void);
extern void TaskRateCount500ms(void);
unsigned char GetFlag_Task1ms(void);  
unsigned char GetFlag_Task10ms(void);
unsigned char GetFlag_Task20ms(void);
unsigned char GetFlag_Task80ms(void);
unsigned char GetFlag_Task100ms(void);
unsigned char GetFlag_Task200ms(void);
unsigned char GetFlag_Task500ms(void);
unsigned char GetFlag_Task1s(void);
unsigned char GetFlag_Task1min(void);

void SetFlag_Task1ms(unsigned char);  
void SetFlag_Task10ms(unsigned char);
void SetFlag_Task20ms(unsigned char);
void SetFlag_Task80ms(unsigned char);
void SetFlag_Task100ms(unsigned char);
void SetFlag_Task200ms(unsigned char);
void SetFlag_Task500ms(unsigned char);
void SetFlag_Task1s(unsigned char);
void SetFlag_Task1min(unsigned char);



/*********************************************************************
 * EOF
 ********************************************************************/
#endif

