/*****************************************************************************
 *
 * HOOTER PROCESS 
 *
 *****************************************************************************
 * FileName:        HooterProcess.h
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
 * Sanat Patel			25/01/17	...	
 * 
 *****************************************************************************/
#ifndef HOOTERPROCESS_H
#define HOOTERPROCESS_H


typedef enum Hooter_s
{
  NOHOOTER =0,
  HOOTER1,
 // HOOTER2, 
  NO_OF_HOOTERS
}Hooters_t;

typedef struct Hooter
{
   unsigned open_flg:1;
   unsigned short_flg:1;
   unsigned normal_flg:1;
   unsigned fault_flg:1;
   unsigned alarm_flg:1;
   unsigned isolate_flg:1;
}Hooter_t; 


void ReadADCHooter(void);

/*********************************************************************
 * EOF
 ********************************************************************/
#endif

