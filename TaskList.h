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
#ifndef TASKLIST_H
#define TASKLIST_H

void TaskScheduler(void);

void List_Task1ms(void);  
void List_Task10ms(void);
void List_Task20ms(void);
void List_Task80ms(void);
void List_Task100ms(void);
void List_Task200ms(void);
void List_Task500ms(void);
void List_Task1s(void);
void List_Task1min(void);
/*********************************************************************
 * EOF
 ********************************************************************/
#endif
