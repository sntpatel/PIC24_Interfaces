/*****************************************************************************
 *
 * LCD 
 *
 *****************************************************************************
 * FileName:        Lcd.h
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
 * Sanat Patel			26/12/13	...	
 * 
 *****************************************************************************/

#ifndef _LCD_H_
#define _LCD_H_

//---------------------------------------------------------------------------
//									Macro Definition
//---------------------------------------------------------------------------

#define LCD_EN         0x10
#define LCD_RS         0x20
#define LCD_BL         0x40
#define LCD_PORT       PORTE 

#define LINE1()        lcd_cmd(0x80) 
#define LINE2()        lcd_cmd(0xC0)
#define LCD_CLEAR()    lcd_cmd(0x01)
#define CURSOR_BLINK() lcd_cmd(0x0F)
#define CURSOR_OFF()   lcd_cmd(0x0C)
#define CURSOR_LEFT()  lcd_cmd(0x10)
#define CURSOR_RIGHT() lcd_cmd(0x14)

#define SETPOS_R1C1   lcd_cmd(0x80)
#define SETPOS_R1C2   lcd_cmd(0x81)
#define SETPOS_R1C3   lcd_cmd(0x82)
#define SETPOS_R1C4   lcd_cmd(0x83)
#define SETPOS_R1C5   lcd_cmd(0x84)
#define SETPOS_R1C6   lcd_cmd(0x85)
#define SETPOS_R1C7   lcd_cmd(0x86)
#define SETPOS_R1C8   lcd_cmd(0x87)
#define SETPOS_R1C9   lcd_cmd(0x88)
#define SETPOS_R1C10  lcd_cmd(0x89)
#define SETPOS_R1C11  lcd_cmd(0x8a)
#define SETPOS_R1C12  lcd_cmd(0x8b)
#define SETPOS_R1C13  lcd_cmd(0x8c)
#define SETPOS_R1C14  lcd_cmd(0x8d)
#define SETPOS_R1C15  lcd_cmd(0x8e)
#define SETPOS_R1C16  lcd_cmd(0x8f)

#define SETPOS_R2C1   lcd_cmd(0xc0)
#define SETPOS_R2C2   lcd_cmd(0xc1)
#define SETPOS_R2C3   lcd_cmd(0xc2)
#define SETPOS_R2C4   lcd_cmd(0xc3)
#define SETPOS_R2C5   lcd_cmd(0xc4)
#define SETPOS_R2C6   lcd_cmd(0xc5)
#define SETPOS_R2C7   lcd_cmd(0xc6)
#define SETPOS_R2C8   lcd_cmd(0xc7)
#define SETPOS_R2C9   lcd_cmd(0xc8)
#define SETPOS_R2C10  lcd_cmd(0xc9)
#define SETPOS_R2C11  lcd_cmd(0xca)
#define SETPOS_R2C12  lcd_cmd(0xcb)
#define SETPOS_R2C13  lcd_cmd(0xcc)
#define SETPOS_R2C14  lcd_cmd(0xcd)
#define SETPOS_R2C15  lcd_cmd(0xce)
#define SETPOS_R2C16  lcd_cmd(0xcf)
//---------------------------------------------------------------------------
// 								Enum Definition
//---------------------------------------------------------------------------

void lcd_data(unsigned char dat);
void lcd_cmd(char cmd);
void LCD_PrintChar(unsigned char);
void LCD_PrintString(const char *strPtr);
void LCD_PrintText(unsigned int strenum);


typedef enum TEXT_S
{
   STR_SPENCER,
   STR_ENTER_PASSWORD,
   STR_PASSWORD_OK,
   STR_INVALID_PASSWORD,
//MAIN MENU
   STR_ISOLATION_MODE,
   STR_TEST_MODE,
   STR_SETTING,
   STR_HISTORY,

//ISOLATION MODE MENU
   STR_ZONE_ISOLATION,
   STR_HOOTER_ISOLATION,
   STR_ENTER_ZONE_NO,
   STR_YES_NO,
   STR_ISOLATED,
   STR_ACTIVATED,
   STR_COMMON_HOOTER,

//TEST MODE
   STR_WALK_TEST,

   STR_MODEL_SET,
   STR_MODEL_1,
   STR_MODEL_2,

//SETTING MENU
   STR_DATE_AND_TIME,
   STR_LOCATION_NAME,
   STR_PASSWORD_LOGO,
   STR_DATE,
   STR_TIME,
//PASSWORD & LOGO MENU
   STR_CHANGE_PASSWORD,
   STR_CHANGE_LOGONAME,
   STR_OLD_PASSWORD,
   STR_NEW_PASSWORD,
   STR_UPDATED,
   STR_LOGO_NAME_CHANGED,

//HISTORY MENU
   STR_VIEW_ALL_EVENTS,
   STR_DELETE_ALL_EVENTS,
   STR_ALARMS,
   STR_ZONE_FAULTS,
   STR_POWER_FAULTS,

//ALARMS
   STR_ZONE_FIRE_ALARM,
   STR_EVACUATE,
   STR_COM_HOOTER_ON,
   STR_PANEL_RESET,
//ZONE FAULTS
   STR_ZONE_OPEN,
   STR_ZONE_SHORT,
   STR_ZONE,
   STR_COM_HOOTER_FAULT,
//POWER FAULTS
   STR_MAINS_FAIL,
   STR_BATTERY_FAIL,
   STR_BATTERY_LOW,
   STR_ZONE_NO,
   STR_DATE_00,
   STR_TIME_00,
   STR_LOCATION_SET,
// Default Zone/Location names
   STR_ZONE_NO_1, 
   STR_ZONE_NO_2, 
   STR_ZONE_NO_3, 
   STR_ZONE_NO_4, 
   STR_ZONE_NO_5, 
   STR_ZONE_NO_6, 
   STR_ZONE_NO_7, 
   STR_ZONE_NO_8, 
   STR_ZONE_NO_9, 
   STR_ZONE_NO_10,
   STR_ZONE_NO_11,
   STR_ZONE_NO_12,
   STR_ZONE_NO_13,
   STR_ZONE_NO_14,
   STR_ZONE_NO_15,
   STR_ZONE_NO_16,
   STR_ZONE_NO_17,
   STR_ZONE_NO_18,
   STR_ZONE_NO_19,
   STR_ZONE_NO_20,
   STR_ZONE_NO_21,
   STR_ZONE_NO_22,
   STR_ZONE_NO_23,
   STR_ZONE_NO_24,
   STR_CHANGE_LOGO_NAME,
   STR_LOGO_CHANGED,
}TEXT_T;

#endif // _LCD_H_

