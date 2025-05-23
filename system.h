/*****************************************************************************
 *  System
 * 	Modified for PIC24FJ64GA004 family with PPS.
 *****************************************************************************
 * FileName:        system.h
 * Dependencies:    
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
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
 * The file assembles all header files and
 * contains shared information for all modules
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Anton Alkhimenok		10/21/05	...
 * Brant Ivey			 3/14/06	Modified for PIC24FJ64GA004 family with PPS.
 *****************************************************************************/
#ifndef SYSTEM_H
#define SYSTEM_H

// External oscillator frequency
#define SYSCLK          8000000

//Comment the line for 3rd board version 
#define BOARD_VERSION4

//Uncomment if PIC24F part is installed directly on board
//#define PIM_SWAP

///	#include "iomapping.h"

#ifndef AN_VOLT_PIN 
	#if defined(__PIC24F32KA304__) 
		#define AN_VOLT_PIN		ANSELAbits.ANSA0
		#define ADC_VOLT_CHAN	0
		#define AN_TEMP_PIN		ANSELAbits.ANSA1
		#define ADC_TEMP_CHAN	1
	#else
	#define AN_VOLT_PIN  	AD1PCFGbits.PCFG5			//voltage input on AN5
	#define ADC_VOLT_CHAN	5
	#define AN_TEMP_PIN	 	AD1PCFGbits.PCFG4			//temp input on AN4
	#define ADC_TEMP_CHAN	4
	#endif
#endif

#if defined(__PIC24F32KA304__)
	#include "LEDstart.h"
#endif
#include <p24fxxxx.h>
#include "timer.h"

#include "spimpol.h"
#include "eeprom.h"
#include "RTC.h"
/*#include "adc.h"
#include "lcd.h"

#include "buttons.h"
#include "uart2.h"
#include "vbanner.h"
#include "tbanner.h"
#include "banner.h"
*/


#if defined(__PIC24FJ256GB110__) || \
	defined(__PIC24FJ256GA110__)
    #define AD1PCFGbits AD1PCFGLbits
    #define AD1PCFG AD1PCFGL
#endif


//============================
#include "p24fxxxx.h"
#include "TaskRateCounter.h" 
#include "Tasklist.h"
#include "FaultCheck.h"
#include "Popup.h"
#include "ProcessRelays.h"
#include "Keypad.h"
#include "Lcd.h"
#include "spi2.h"
#include "EEPROM.h"
#include "RTC.h"
#include "ZoneProcess.h"
#include "FaultCheck.h"
#include "Led.h"


#define  AC_FAIL _LATB11 

#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0
#define NULL 0
#define SET_BIT(bitNumber)   (1U << bitNumber)
#define CLEAR_BIT(bitNumber) ~SET_BIT(bitNumber)


typedef unsigned char bool;
typedef unsigned short uint8_t;
typedef unsigned int uint16_t;
//#define SYSTEM_TIME_SET  /* Remove '//'  to enable System Timeset to RTC while power ON*/

/****************************************************************
                   PANEL CONFIGURATION 
****************************************************************/
#define NUM_OF_BATTVOLTAGE_LEVEL  9  /* 8 levels of batt voltage (from 26 to 19)*/
                                     /*+1 for MAINS supply voltage level */
#define PSWD_ENABLE   1     // 0 for disble the pawword

#define NUM_OF_ZONES     8    /*Number of Zone in Panel*/

/**********EEPROM ADDRESSES *********************/
#define ADDR_DEFWRITE 1 
#define ADDR_PSWD   2 //to 5
#define ADDR_LOGO 20 //to 36
#define ADDR_MODEL 37 //to 47
#define ADDR_ZONE_ISOLATE_START 100  //100 to 124
#define ADDR_HOOTER_ISOLATE          125
// 126 , 127, 128, 129, 130
#define ADDR_ZONE1_LOCATION         131
#define ADDR_ZONE2_LOCATION         147
#define ADDR_ZONE3_LOCATION         163
#define ADDR_ZONE4_LOCATION         179
#define ADDR_ZONE5_LOCATION         195
#define ADDR_ZONE6_LOCATION         211
#define ADDR_ZONE7_LOCATION         227
#define ADDR_ZONE8_LOCATION         243
#define ADDR_ZONE9_LOCATION         259
#define ADDR_ZONE10_LOCATION         275
#define ADDR_ZONE11_LOCATION         291
#define ADDR_ZONE12_LOCATION         307
#define ADDR_ZONE13_LOCATION         323
#define ADDR_ZONE14_LOCATION         339
#define ADDR_ZONE15_LOCATION         355
#define ADDR_ZONE16_LOCATION         371
#define ADDR_ZONE17_LOCATION         387
#define ADDR_ZONE18_LOCATION         403
#define ADDR_ZONE19_LOCATION         419
#define ADDR_ZONE20_LOCATION         435
#define ADDR_ZONE21_LOCATION         451
#define ADDR_ZONE22_LOCATION         467
#define ADDR_ZONE23_LOCATION         483
#define ADDR_ZONE24_LOCATION         499
#define ADDR_LOGONAME                516   // to 532

#define MAX_EEPROM_ADDRESS 32767


extern unsigned  char StringBuf[16];
/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif

