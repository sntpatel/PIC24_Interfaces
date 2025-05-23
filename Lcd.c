/*****************************************************************************
 *
 * LCD 
 *
 *****************************************************************************
 * FileName:        Lcd.c
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
#include "Lcd.h"
static const char *temp = (char *)0;

const char  str1[] = "SPENCER";
const char  str2[] = "ENTER PASSWORD  ";
const char  str3[] = "PASSWORD OK";
const char  str4[] = "INVALID PASSWORD";
//MAIN MENU
const char  str5[] = "ISOLATION MODE";
const char  str6[] = "TEST MODE";
const char  str7[] = "SETTING";
const char  str8[] = "HISTORY";

//ISOLATION MODE MENU
const char  str9[] = "ZONE ISOLATION";
const char  str10[] = "HOOTER ISOLATION";

const char  str11[] = "ENTER ZONE NO:";
const char  str12[] = "     YES / NO   ";

const char  str13[] = "ISOLATED";
const char  str14[] = "ACTIVATED";
const char  str15[] = "COMMON HOOTER";

//TEST MODE
const char  str16[] = "WALK TEST";

const char  str17[] = "MODEL SET";
const char  str18[] = "MODEL 1";
const char  str19[] = "MODEL 2";

//SETTING MENU
const char  str20[] = "DATE AND TIME";
const char  str21[] = "LOCATION NAME";
const char  str22[] = "PASSWORD & LOGO";
const char  str23[] = "DATE";
const char  str24[] = "TIME";
//PASSWORD & LOGO MENU
const char  str25[] = "CHANGE PASSWORD";
const char  str26[] = "CHANGE LOGONAME";
const char  str27[] = "OLD PASSWORD";
const char  str28[] = "NEW PASSWORD";
const char  str29[] = "UPDATED";
const char  str30[] = "LOGO NAME CHANGED";

//HISTORY MENU
const char  str31[] = "VIEW ALL EVENTS";
const char  str32[] = "DELETE ALL EVENTS";
const char  str33[] = "ALARMS";
const char  str34[] = "ZONE FAULTS";
const char  str35[] = "POWER FAULTS";

//ALARMS
const char  str36[] = "ZONE FIRE/ALARM";
const char  str37[] = "EVACUATE";
const char  str38[] = "COM. HOOTER ON";
const char  str39[] = "PANEL RESET";
//ZONE FAULTS
const char  str40[] = "ZONE OPEN";
const char  str41[] = "ZONE SHORT";
const char  str42[] = "ZONE";
const char  str43[] = "COM.HOOTER FAULT";
//POWER FAULTS
const char  str44[] = "MAINS FAIL";
const char  str45[] = "BATTERY FAIL";
const char  str46[] = "BATTERY LOW";
const char  str47[] = "ZONE NO ";
const char  str48[] = "DATE: 00/00/00  ";
const char  str49[] = "TIME: 00/00     ";
const char  str50[] = "LOCATION SET    ";

// Default Zone/Location names
const char  str51[] = "ZONE NO 1       ";
const char  str52[] = "ZONE NO 2       ";
const char  str53[] = "ZONE NO 3       ";
const char  str54[] = "ZONE NO 4       ";
const char  str55[] = "ZONE NO 5       ";
const char  str56[] = "ZONE NO 6       ";
const char  str57[] = "ZONE NO 7       ";
const char  str58[] = "ZONE NO 8       ";
const char  str59[] = "ZONE NO 9       ";
const char  str60[] = "ZONE NO 10      ";
const char  str61[] = "ZONE NO 11      ";
const char  str62[] = "ZONE NO 12      ";
const char  str63[] = "ZONE NO 13      ";
const char  str64[] = "ZONE NO 14      ";
const char  str65[] = "ZONE NO 15      ";
const char  str66[] = "ZONE NO 16      ";
const char  str67[] = "ZONE NO 17      ";
const char  str68[] = "ZONE NO 18      ";
const char  str69[] = "ZONE NO 19      ";
const char  str70[] = "ZONE NO 20      ";
const char  str71[] = "ZONE NO 21      ";
const char  str72[] = "ZONE NO 22      ";
const char  str73[] = "ZONE NO 23      ";
const char  str74[] = "ZONE NO 24      ";

const char  str75[] = "CHANGE LOGO NAME";
const char  str76[] = "  LOGO CHANGED  ";
const char *arryofStr[] =
{
   str1,
   str2,
   str3,
   str4,
   str5,
   str6,
   str7,
   str8,
   str9,
   str10,
   str11,
   str12,
   str13,
   str14,
   str15,
   str16,
   str17,
   str18,
   str19,
   str20,
   str21,
   str22,
   str23,
   str24,
   str25,
   str26,
   str27,
   str28,
   str29,
   str30,
   str31,
   str32,
   str33,
   str34,
   str35,
   str36,
   str37,
   str38,
   str39,
   str40,
   str41,
   str42,
   str43,
   str44,
   str45,
   str46,
   str47,
   str48,
   str49,
   str50,
   str51,
   str52,
   str53,
   str54,
   str55,
   str56,
   str57,
   str58,
   str59,
   str60,
   str61,
   str62,
   str63,
   str64,
   str65,
   str66,
   str67,
   str68,
   str69,
   str70,
   str71,
   str72,
   str73,
   str74,
   str75,
   str76,
};

//---------------------------------------------------------------------------
//									Function Declaration
//---------------------------------------------------------------------------

// Resets LCD
//
static void lcd_reset(void);
static void Delayus(unsigned int);
//---------------------------------------------------------------------------
// 								Function Definition
//---------------------------------------------------------------------------

static void Delayus(unsigned int cnt)
{
 unsigned int i;
 for(i = 0;i< cnt*3;i++)
 {
  ;
 }
}

/******************************************************************************
Function Name: lcd_cmd
Purpose      : To send configuration commands to LCD 
******************************************************************************/	   
void lcd_cmd(char cmd)
{
   LCD_PORT = ((cmd >> 4) & 0x0F) | LCD_EN | LCD_BL;
   LCD_PORT = ((cmd >> 4) & 0x0F)| LCD_BL;
 
   LCD_PORT = (cmd & 0x0F) | LCD_EN | LCD_BL;
   LCD_PORT = (cmd & 0x0F) | LCD_BL;
 
   Delayus(20);

   return;
}
 
/******************************************************************************
Function Name: lcd_data
Purpose      : To send data on LCD (Same as sendcommand but RS is set, too)
******************************************************************************/
void lcd_data(unsigned char dat)
{
   LCD_PORT = (((dat >> 4) & 0x0F) | LCD_EN | LCD_RS  | LCD_BL);
   LCD_PORT = (((dat >> 4) & 0x0F) | LCD_RS | LCD_BL);
   LCD_PORT = ((dat & 0x0F) | LCD_EN | LCD_RS | LCD_BL);
   LCD_PORT = ((dat & 0x0F) | LCD_RS | LCD_BL);
 
   Delayus(20);

   return;
}

/******************************************************************************
Function Name: LCD_PrintChar
Purpose      : To send data on LCD (Same as sendcommand but RS is set, too)
******************************************************************************/
void LCD_PrintChar(unsigned char Character)
{
   lcd_data(Character);
   return;
}
/******************************************************************************
Function Name: LCD_PrintText
Purpose      : Prints predfined text strings on LCD
******************************************************************************/
void LCD_PrintText(unsigned int strenum)
{
   unsigned int i;

   temp = arryofStr[strenum]; 

   for(i = 0; i < 16; i++)
   {
      if(temp[i] == '\0')
      {
         break;
      }
      else
      { 
         lcd_data(temp[i]); 
      }
   }

   return;
}

/******************************************************************************
Function Name: LCD_PrintString
Purpose      : Sends the whole string to LCD
******************************************************************************/
void LCD_PrintString(const char *strPtr)
{
   while(*strPtr)
   {
      lcd_data(*strPtr++);
   }

   return;
}

/******************************************************************************
Function Name: lcd_reset
Purpose      : Resets LCD
******************************************************************************/	
static void lcd_reset(void)
{

   Delayus(100);
   LCD_PORT = 0xFF;
   SetDelayms(10);
   LCD_PORT = 0x03+LCD_EN+LCD_BL;
   LCD_PORT = 0x03;
   SetDelayms(10);
   LCD_PORT = 0x03+LCD_EN+LCD_BL;
   LCD_PORT = 0x03;
   SetDelayms(10);
   LCD_PORT = 0x03+LCD_EN+LCD_BL;
   LCD_PORT = 0x03;
   SetDelayms(10);
   LCD_PORT = 0x02+LCD_EN+LCD_BL;
   LCD_PORT = 0x02;
   SetDelayms(10);
   
   return;
}
     
/******************************************************************************
Function Name: LCDSetpos
Purpose      : Sets position on LCD (row = { 1, 2 }, column = {1, 2, 3, ...16}
******************************************************************************/
void LCDSetpos(char row, char column)
{
   switch (row) 
   {
      case 1: lcd_cmd(0x80 + column - 1); 
	           break;
      case 2: lcd_cmd(0xc0 + column - 1);
               break;
      default: break;
   }
   
   return;
}

/******************************************************************************
Function Name: LCD_Clear
Purpose      : Clears LCD screen
******************************************************************************/
void LCD_Clear(void)
{
   lcd_cmd(0x01);

   return;
}

/******************************************************************************
Function Name: LCD_init
Purpose      : Initializes LCD
******************************************************************************/	
void LCD_init(void)
{
   TRISE = 0x00;
   lcd_reset();
   lcd_cmd(0x28); // 4-bit mode - 2 line - 5x7 font.
   lcd_cmd(0x0C); // Display no cursor - no blink.
   lcd_cmd(0x06); // Automatic Increment - No Display shift.
   lcd_cmd(0x80); // Address DDRAM with 0 offset 80h.
   lcd_cmd(0x01);//Clear LCD
   return;
}

