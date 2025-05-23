/*****************************************************************************
 *
 * HOOTER PROCESS 
 *
 *****************************************************************************
 * FileName:        HooterProcess.c
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
#include "system.h"
#include "HooterProcess.h"
#include "ProcessADC.h"

static unsigned char NumOfHooters;
static unsigned char HooterValueLevel;
static unsigned int HooterADCValue[8] = {0,0,0,0,0,0,0,0}; //TODO
static unsigned int ADChannel;
static unsigned int BattVoltage;
//extern const char *arryofStr[];


extern void SWDelayms(unsigned int cnt);

struct HooterValue
{
  unsigned char BattLevelL;
  unsigned char BattLevelH;
  unsigned char ShortL;
  unsigned char ShortH;
  unsigned char OpenL;
  unsigned char OpenH;
  unsigned char NormalL;
  unsigned char NormalH;
};

struct HooterValue  HooterTable[NUM_OF_BATTVOLTAGE_LEVEL]=
{
// BattLevelL  BattLevelH      ShortL   ShortH	  OpenL   OpenH    NormalL    NormalH
//26{   26.5,       25.5,         0,      0.5,      3,      3.5,     2,         2.5 }
//25{   25.5,       24.5,         0,      0.5,      3,      3.5,     2,         2.5 }
//24{   24.5,       23.5,         0,      0.5,      3,      3.5,     2,         2.5 }
//23{   23.5,       22.5,         0,      0.5,      3,      3.5,     2,         2.5 }
//22{   22.5,       21.5,         0,      0.5,      3,      3.5,     2,         2.5 }
//21{   21.5,       20.5,         0,      0.5,      3,      3.5,     2,         2.5 }
//20{   20.5,       19.5,         0,      0.5,      3,      3.5,     2,         2.5 }
//19{   19.5,       19,           0,      0.5,      3,      3.5,     2,         2.5 }

};

Hooter_t HooterArr[2];//NumOfZones+1];


/*********************************************************************************
 *                     ADC hooter values
**********************************************************************************/

void ReadADCHooter(void)
{
   BattVoltage = ADC_Read10bit(ADChannel);
   ADChannel = ADC_CHANNEL_HOOTER_1;  /*TODO: change */
   if (ADChannel < NO_OF_HOOTERS)
   { 
      if(HooterArr[ADChannel].isolate_flg  == FALSE)
      {
         HooterADCValue[ADChannel] = ADC_Read10bit(ADChannel);
      }
      ADChannel++;
   }
   else
   {
      ADChannel = ADC_CHANNEL_8;
   } 
}
void SetHooterState_Task(void)
{
   static unsigned char hno,Level;
   static unsigned int BatteryLevel;

   BatteryLevel = GetBattLevel();
   for(Level =0; Level < NUM_OF_BATTVOLTAGE_LEVEL; Level++)
   {
      if((BatteryLevel <= HooterTable[Level].BattLevelH) && 
         (BatteryLevel > HooterTable[Level].BattLevelL))
      {
         HooterValueLevel = Level;
         break;
      }    
   }
   for(hno = 1; hno < NO_OF_HOOTERS; hno++)
   {
      if((HooterADCValue[hno]> HooterTable[HooterValueLevel].ShortL) &&
         (HooterADCValue[hno]<= HooterTable[HooterValueLevel].ShortH))
         {
            HooterArr[hno].short_flg = TRUE;
            HooterArr[hno].open_flg = FALSE;    
            HooterArr[hno].normal_flg = FALSE;  
         }
     else if((HooterADCValue[hno]> HooterTable[HooterValueLevel].OpenL) &&
             (HooterADCValue[hno]<= HooterTable[HooterValueLevel].OpenH))
         {
            HooterArr[hno].short_flg = FALSE;
            HooterArr[hno].open_flg = TRUE;    
            HooterArr[hno].normal_flg = FALSE;  
         }
     else
        {
            HooterArr[hno].short_flg = FALSE;
            HooterArr[hno].open_flg = FALSE;    
            HooterArr[hno].normal_flg = TRUE;  
        }
   }
}

void SetNumOfHooter(unsigned char SetVal)
{
   NumOfHooters = SetVal;
}
unsigned char GetNumOfHooter(void)
{
   return NumOfHooters;
}

