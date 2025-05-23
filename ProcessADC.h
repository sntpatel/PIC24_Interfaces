/*****************************************************************************
 *
 * ADC 
 *
 *****************************************************************************
 * FileName:        ProcessADC.h
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
#ifndef PROCESSADC_H
#define PROCESSADC_H

#include "system.h"

/*** ADC Channel Definitions *****************************************/
#define ADC_CHANNEL_ZONE1 ADC_CHANNEL_0
#define ADC_CHANNEL_ZONE2 ADC_CHANNEL_1
#define ADC_CHANNEL_ZONE3 ADC_CHANNEL_2
#define ADC_CHANNEL_ZONE4 ADC_CHANNEL_3
#define ADC_CHANNEL_ZONE5 ADC_CHANNEL_4
#define ADC_CHANNEL_ZONE6 ADC_CHANNEL_5
#define ADC_CHANNEL_ZONE7 ADC_CHANNEL_6
#define ADC_CHANNEL_ZONE8 ADC_CHANNEL_7

#define ADC_CHANNEL_HOOTER_1 ADC_CHANNEL_8
/*#define ADC_CHANNEL_HOOTER_2 ADC_CHANNEL_9
#define ADC_CHANNEL_HOOTER_3 ADC_CHANNEL_10
#define ADC_CHANNEL_HOOTER_4 ADC_CHANNEL_11
#define ADC_CHANNEL_HOOTER_5 ADC_CHANNEL_12
#define ADC_CHANNEL_HOOTER_6 ADC_CHANNEL_13
#define ADC_CHANNEL_HOOTER_7 ADC_CHANNEL_14
#define ADC_CHANNEL_HOOTER_8 ADC_CHANNEL_15
*/
#define  END_OF_HOOTER_ADC_CHANNEL 10

#define ADC_CHANNEL_BATTERY ADC_CHANNEL_9

typedef enum
{
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1 = 1,
    ADC_CHANNEL_2 = 2,
    ADC_CHANNEL_3 = 3,
    ADC_CHANNEL_4 = 4,
    ADC_CHANNEL_5 = 5,
    ADC_CHANNEL_6 = 6,
    ADC_CHANNEL_7 = 7,
    MAX_ADC_ZONE_CHANNEL, 
    ADC_CHANNEL_8 = 8,
    ADC_CHANNEL_9 = 9,
    ADC_CHANNEL_10 = 10,
    ADC_CHANNEL_11 = 11,
    MAX_ADC_CHANNEL
} ADC_CHANNEL;

typedef enum
{
    ADC_CONFIGURATION_DEFAULT,
    ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT
} ADC_CONFIGURATION;


void ADCInit(void);
/*********************************************************************
* Function: ADC_ReadPercentage(ADC_CHANNEL channel);
*
* Overview: Reads the requested ADC channel and returns the percentage
*            of that conversions result (0-100%).
*
* PreCondition: channel is enabled via ADC_ChannelEnable()
*
* Input: ADC_CHANNEL channel - enumeration of the ADC channels
*        available in this demo.  They should be meaningful names and
*        not the names of the ADC pins on the device (as the demo code
*        may be ported to other boards).
*         i.e. ADC_ReadPercentage(ADC_CHANNEL_POTENTIOMETER);
*
* Output: uint8_t indicating the percentage of the result 0-100% or
*         0xFF for an error
*
********************************************************************/
uint8_t ADC_ReadPercentage(ADC_CHANNEL channel);


/*********************************************************************
* Function: ADC_Read10bit(ADC_CHANNEL channel);
*
* Overview: Reads the requested ADC channel and returns the 10-bit
*           representation of this data.
*
* PreCondition: channel is enabled via ADC_ChannelEnable()
*
* Input: ADC_CHANNEL channel - enumeration of the ADC channels
*        available in this demo.  They should be meaningful names and
*        not the names of the ADC pins on the device (as the demo code
*        may be ported to other boards).
*         i.e. - ADCReadPercentage(ADC_CHANNEL_POTENTIOMETER);
*
* Output: uint16_t the right adjusted 10-bit representation of the ADC
*         channel conversion or 0xFFFF for an error.
*
********************************************************************/
uint16_t ADC_Read10bit(ADC_CHANNEL channel);

/*********************************************************************
* Function: bool ADC_ChannelEnable(ADC_CHANNEL channel, ADC_CONFIGURATION configuration);
*
* Overview: Enables specified channel
*
* PreCondition: none
*
* Input: ADC_CHANNEL channel - the channel to enable
*
* Output: bool - true if successfully configured.  false otherwise.
*
********************************************************************/
bool ADC_ChannelEnable(ADC_CHANNEL channel);

/*********************************************************************
* Function: bool ADC_SetConfiguration(ADC_CONFIGURATION configuration)
*
* Overview: Configures the ADC module to specified setting
*
* PreCondition: none
*
* Input: ADC_CONFIGURATION configuration - the mode in which to run the ADC
*
* Output: bool - true if successfully configured.  false otherwise.
*
********************************************************************/
bool ADC_SetConfiguration(ADC_CONFIGURATION configuration);

/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif

