/*****************************************************************************
 *
 * ZONE PROCESS 
 *
 *****************************************************************************
 * FileName:        ZoneProcess.c
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
 * Sanat Patel			20/11/13	...	
 * 
 *****************************************************************************/
#include "system.h"
#include "ZoneProcess.h"
#include "ProcessADC.h"

#define DUMMY_BATT_LEVEL 250

static const char *ZoneString = (char *)0;
static unsigned char ZoneValueLevel;
extern unsigned int ZnADCValue[];
static unsigned int ADChannel;
static unsigned int BattVoltage;
extern const char *arryofStr[];

extern void SWDelayms(unsigned int cnt);

struct ZoneValue
{
  unsigned int BattLevelL;
  unsigned int BattLevelH;
  unsigned int ShortL;
  unsigned int ShortH;
  unsigned int OpenL;
  unsigned int OpenH;
  unsigned int FireL;
  unsigned int FireH;
  unsigned int NormalL;
  unsigned int NormalH;
};

struct ZoneValue  ZoneTable[NUM_OF_BATTVOLTAGE_LEVEL]=
{
// BattLevelL  BattLevelH      ShortL   ShortH	  OpenL  OpenH   FireL FireH   NormalL    NormalH
//26{   26.5,       25.5,         0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }
//25{   25.5,       24.5,         0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }
//24{   24.5,       23.5,         0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }
//23{   23.5,       22.5,         0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }
//22{   22.5,       21.5,         0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }
//21{   21.5,       20.5,         0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }
//20{   20.5,       19.5,         0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }
//19{   19.5,       19,           0,      0.5,      3,   3.5,    1,    1.5,       2,     2.5 }

  /* BATTERY Supply voltage range*/
   {   686,        800,         0,      100,      950,  1023,    260,  300,       750,    900 },
   {   656,        685,         0,      100,      900,  1000,    250,  285,       700,    850 },
   {   626,        655,         0,      100,      850,  950,     240,  270,       700,    800 },
   {   606,        625,         0,      100,      800,  950,     225,  280,       650,    750 },
   {   576,        605,         0,      100,      800,  900,     225,  270,       650,    750 },
   {   546,        575,         0,      100,      750,  850,     210,  245,       600,    700 },
   {   526,        545,         0,      100,      700,  810,     205,  225,       550,    650 },
   {   500,        525,         0,      100,      650,  730,     150,  205,       550,    600 },

  /* MAINS Supply voltage range: (note: BattLevelL and BattLevelH is dummy value. It must be 
     different from other valide ranges */
   {   200,        300,         0,      100,      860,  1023,     240,  300,       700,    850}

};

Zone_t ZoneArr[24];//NUM_OF_ZONES+1];


/*********************************************************************************
 *                     ADC zone values
**********************************************************************************/

unsigned int GetBattLevel(void)
{
   BattVoltage = ADC_Read10bit(ADChannel);
   return BattVoltage ;
}

void ReadADCZone(void)
{
   if (ADChannel < MAX_ADC_ZONE_CHANNEL )
   { 
      if(ZoneArr[ADChannel].isolate_flg == FALSE)
      {
         ZnADCValue[ADChannel] = ADC_Read10bit(ADChannel);
      }
      ADChannel++;
   }
   else
   {
      ADChannel =0;
   } 
}
void SetZoneState_Task(void)
{
   static unsigned char zno,Level,FaultBits;
   static unsigned int BatteryLevel;

   FaultBits = GetFaultBits();
  // if(GetACFaultFlag == FALSE)
   if(FaultBits & AC_FAULT_BITMASK)
   {
      BatteryLevel = GetBattLevel();
   }
   else
   {
      BatteryLevel =  DUMMY_BATT_LEVEL; //In case of Mains Power supply OK
   }

   for(Level =0; Level < NUM_OF_BATTVOLTAGE_LEVEL; Level++)
   {
      if((BatteryLevel <= ZoneTable[Level].BattLevelH) && 
         (BatteryLevel > ZoneTable[Level].BattLevelL))
      {
         ZoneValueLevel = Level;
         break;
      }    
   }
   for(zno =1; zno < NUM_OF_ZONES; zno++)
   {
      if(ZoneArr[zno].isolate_flg == FALSE)
      {
         continue; /* if zone number is isolated then continue from next zone number*/
      }
      if((ZnADCValue[zno]> ZoneTable[ZoneValueLevel].ShortL) &&
         (ZnADCValue[zno]<= ZoneTable[ZoneValueLevel].ShortH))
         {
            ZoneArr[zno].short_flg = TRUE;
            ZoneArr[zno].open_flg = FALSE;    
            ZoneArr[zno].fire_flg = FALSE;      
            ZoneArr[zno].normal_flg = FALSE;  
         }
     else if((ZnADCValue[zno]> ZoneTable[ZoneValueLevel].OpenL) &&
             (ZnADCValue[zno]<= ZoneTable[ZoneValueLevel].OpenH))
         {
            ZoneArr[zno].short_flg = FALSE;
            ZoneArr[zno].open_flg = TRUE;    
            ZoneArr[zno].fire_flg = FALSE;      
            ZoneArr[zno].normal_flg = FALSE;  
         }
     else if((ZnADCValue[zno]> ZoneTable[ZoneValueLevel].FireL) &&
             (ZnADCValue[zno]<= ZoneTable[ZoneValueLevel].FireH))
         {
            ZoneArr[zno].short_flg = FALSE;
            ZoneArr[zno].open_flg = FALSE;    
            ZoneArr[zno].fire_flg = TRUE;      
            ZoneArr[zno].normal_flg = FALSE;  
         }
     else
        {
            ZoneArr[zno].short_flg = FALSE;
            ZoneArr[zno].open_flg = FALSE;    
            ZoneArr[zno].fire_flg = FALSE;      
            ZoneArr[zno].normal_flg = TRUE;  
        }
    }
}


unsigned char IsFire(void)
{
   static unsigned char zno;
   unsigned char ReturnStatus = FALSE;

   for(zno =1; zno < NUM_OF_ZONES; zno++)
   {
      if(ZoneArr[zno].fire_flg == TRUE)
      {
         return TRUE;
      }
   }
   return ReturnStatus; 
}


void ZoneLocationDefaultSet(void)
{
   unsigned int i, count, LocationAdd;
LocationAdd = ADDR_ZONE1_LOCATION;
   ZoneString = arryofStr[STR_ZONE_NO_1]; 
   for(count =1; count<= NUM_OF_ZONES ; count++)
   {
      for(i = 0; i < 16; i++)
      {
         if(ZoneString[i] == '\0')
         {
            break;
         }
         else
         { 
            EEPROMWriteByte(ZoneString[i],LocationAdd +i);   
            SWDelayms(5);
         }
        
      }
      LocationAdd= LocationAdd+16;
      ZoneString = arryofStr[STR_ZONE_NO_1 + count];
   }
   
}
