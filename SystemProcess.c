/*****************************************************************************
 *
 * LED 
 *
 *****************************************************************************
 * FileName:        SystemProcess.c
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
 * Sanat Patel			21/12/13	...	
 * 
 *****************************************************************************/
#include "system.h"
#include "SystemProcess.h"
#include "ProcessADC.h"
#include "Led.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

extern void ProcessMenuState(void);
extern unsigned char IsFire(void);
char * pDateTimeStr;

extern void SWDelayms(unsigned int cnt);
//global Definition
typedef struct
{  
  
    volatile unsigned char adones ;
    volatile unsigned char adtens ;
    volatile unsigned char adhunds ;
    volatile unsigned char adthous ;
    volatile unsigned int  temp1 ;

} APP_DATA ;

static APP_DATA adcData ;



EventFlags_t Event;
static unsigned int SystemState;
KeyState_t *Keyarr;

static unsigned char char1,char2,char3,char4;
static unsigned int AdcValue = 0;

 void ConvertADCVoltage ( unsigned int adc_conv_data );

void SystemInitialise(void)
{
   SystemState = IDLE_STATE;
   //Keypad_Init();
}
void SystemProcess_Task(void)
{
//unsigned int AdcValue;
/*
 if((GetKeyChar() == 'M')&& ISKeyFlag())
 {
     //LINE1(); lcd_data('M');
    SystemState = MENU_STATE;
    ClearKeyFlag();
  }
*/
 //Check for Fault inputs
 //Check for Zone flags

   switch(SystemState)
   { 

      case IDLE_STATE:
      {     
        // Display Date and Time     
         LINE1();LCD_PrintString(DateTimeStr); 
         /*if((GetKeyChar() == 'M')&& ISKeyFlag())
         {
            SystemState = MENU_STATE;
            ClearKeyFlag(); 
         }
         */
       SystemState = MENU_STATE; 

      //DisplayFaults();

      }
      break;
      case MENU_STATE:

        LCD_CLEAR();
      //  ADC debug--------------------------
         AdcValue =ADC_Read10bit(11);//ADC_CHANNEL_ZONE1);
         //AdcValue = ADC_ReadPercentage(ADC_CHANNEL_ZONE1);
         adcData.temp1 = AdcValue;
         ConvertADCVoltage ( adcData.temp1 ) ;
         LINE2(); LCD_PrintString("V:"); 
         LCD_PrintChar( adcData.adones ) ;
         LCD_PrintChar( '.' ) ;
         LCD_PrintChar( adcData.adtens ) ;
         LCD_PrintChar( adcData.adhunds ) ;
         LCD_PrintChar( ' ' ) ;
         LCD_PrintChar( 'D' ) ;
         LCD_PrintChar( ':' ) ;
         char1 = (AdcValue/1000) + 0x30;
         char2 = ((AdcValue/100)%10) + 0x30;
         char3 = ((AdcValue%100)/10) + 0x30;
         char4 = ((AdcValue/100)%10) + 0x30;
         LCD_PrintChar(char1);
         LCD_PrintChar(char2);
         LCD_PrintChar(char3);
         LCD_PrintChar(char4);
          SWDelayms(1000);

if(AdcValue >1000)
ACFLT_LED = 0;
else
ACFLT_LED = 1;

/*         if(AdcValue == 0)
        { LCD_CLEAR(); LINE2(); LCD_PrintString("ADC < 100"); }
       else if((AdcValue > 100) && (AdcValue < 800))
        {LCD_CLEAR();  LINE2(); LCD_PrintString("ADC > 100  < 800"); }
     else if(AdcValue > 900)
        {LCD_CLEAR();  LINE2(); LCD_PrintString("ADC > 900"); }
     */
      /* 1024 - 3.3/ 3.3 x X
         X    ?   /  ------- 
                 /   1024
        */        

      //    ProcessMenuState();
      break;
      case FAULT_STATE:
      break;
      case SILENCE_STATE:
      {
         if(IsFire())
         {
            
          // Fire silence
            SystemState = IDLE_STATE;
         }
         else if(IsFault())
         {
            // Fault silence
            // buzzer OFF hooter off, fault flag clear etc.
            SystemState = IDLE_STATE;
         }
         else
         {   //Do nothing
             SystemState = IDLE_STATE;
         }
      } 
      break;
      case FIRE_STATE:
      break;
      case EVAC_STATE:
      break;
//      case TESTMODE_STATE:
//      break;
      case RESET_STATE:
      break;
      default:
      break;
       
   }
}

void SetSystemState(unsigned char SysState)
{
   SystemState = SysState;
}
unsigned char GsetSystemState(void)
{
  return SystemState;
}



/*******************************************************************************

  Function:
   void ConvertADCVoltage ( unsigned int )

  Summary:
    Function to convert ADC data into volts

  Description:
     This is the file for the Explorer 16 Dem that converts raw 10 bit ADC data
    to volts suitable for the LCD display

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void ConvertADCVoltage ( unsigned int adc_conv_data )
{
    /* reset values */
    adcData.adones = 0 ;
    adcData.adtens = 0 ;
    adcData.adhunds = 0 ;
    adcData.adthous = 0 ;

    while ( adc_conv_data > 0 )
    {
        /* test for 1 volt or greater */
        if ( adc_conv_data > ( ONE_VOLT - 1 ) )
        {
            /* increment 1 volt counter */
            adcData.adones++ ;

            /* subtract 1 volt */
            adc_conv_data -= ONE_VOLT ;
        }


            /* test for 0.1 volt */
        else if ( adc_conv_data > ( ONE_TENTH_VOLT - 1 ) )
        {
            /* increment tenths */
            if ( adcData.adtens < 9 )
            {
                adcData.adtens++ ;
            }
            else
            {
                /* tenths has rolled over */
                adcData.adones++ ;

                /* so increment ones and reset tenths */
                adcData.adtens = 0 ;
            }

            adc_conv_data -= ONE_TENTH_VOLT ;
        }

            /* test for 0.01 volt */
        else if ( adc_conv_data > ( ONE_HUNDREDTH_VOLT - 1 ) )
        {
            /* increment hundredths */
            if ( adcData.adhunds < 9 )
            {
                adcData.adhunds++ ;
            }
            else
            {
                /* hundredths has rolled over */
                adcData.adtens++ ;

                /* so increment tenths and reset hundredths */
                adcData.adhunds = 0 ;
            }

            adc_conv_data -= ONE_HUNDREDTH_VOLT ;
        }

        else if ( adc_conv_data <= ( ONE_HUNDREDTH_VOLT - 1 ) )
        {
            adcData.adthous++ ;
            adc_conv_data -- ;
        }
    }

    adcData.adones += 0x30 ;
    adcData.adtens += 0x30 ;
    adcData.adhunds += 0x30 ;
    adcData.adthous += 0x30 ;
}


