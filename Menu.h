/*****************************************************************************
 *
 * MENU
 *
 *****************************************************************************
 * FileName:        Menu.h
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
 * Sanat Patel			27/7/16	...	
 * 
 *****************************************************************************/
#ifndef MENU_H
#define MENU_H

#include "Lcd.h"

/*
#define   INIT         0
#define   PASSWORD     1
#define   MAIN         2
#define   ISOLATE      3
#define   TESTMODE     4
#define   SETTING      5
#define   HISTORY      6
//ISOLATION MENU
#define   ZONE_ISO     7 
#define   HOOTER_ISO   8 
//SETTING MENU
#define   DATENTIME   9
#define   LOCATION   10
#define   PSWDNLOGO   11
// PSWDNLOGO MENU,
//   CHNG_PASSWORD,
//   LOCATION_NAME,
//   CHNG_LOGONAME,
//HISTORY MENU
//   VIEW_ALL,
//   DLT_ALL,
//   ALARMS,
//   ZONE_FAULT,
//   POWER_FAULT,
#define   NO_OF_MENUS   12
*/
typedef enum MenuState
{
   INIT =0,
   PASSWORD,
   MAIN,
   ISOLATE,
   TESTMODE,
   SETTING,
   HISTORY,
//ISOLATION MENU
   ZONE_ISO,
   HOOTER_ISO, 
//SETTING MENU
   DATENTIME,
   LOCATION,
   PSWDNLOGO,
// PSWDNLOGO MENU,
   CHNG_PASSWORD,
   CHNG_LOGONAME,
//HISTORY MENU
//   VIEW_ALL,
//   DLT_ALL,
//   ALARMS,
//   ZONE_FAULT,
//   POWER_FAULT,
   NO_OF_MENUS
}MenuState_t; 


//=================================================================================
typedef enum MainMenu
{
   ISOLATION_MENU = 0,
   TESTMODE_MENU,
   SETTING_MENU,
   HISTORY_MENU,
   TOTAL_MAIN_MENU,
}MainMenu_t;

MenuState_t MainMenu_States[TOTAL_MAIN_MENU] =
{
   ISOLATE,
   TESTMODE,
   SETTING,
   HISTORY 
};
TEXT_T Main_Menu_Items[]=
{
   STR_ISOLATION_MODE,
   STR_TEST_MODE,
   STR_SETTING,
   STR_HISTORY,
};
//----------------------------------------------------------------------------
typedef enum IsolateMenu
{
   ZONE_MENU,
   HOOTER_MENU,
   TOTAL_ISOLATE_MENU,
}IsolateMenu_t;

MenuState_t IsolateMenu_States[TOTAL_ISOLATE_MENU] =
{
   ZONE_ISO,
   HOOTER_ISO
};

TEXT_T Isolate_Menu_Items[]=
{
   STR_ZONE_ISOLATION,
   STR_HOOTER_ISOLATION,
};
//-----------------------------------------------------------------------------
typedef enum ModelMenu
{
   MODEL_1,
   MODEL_2,
   TOTAL_MODEL_MENU
}ModelMenu_t;

TEXT_T Model_Menu_Items[]=
{
   STR_MODEL_1,
   STR_MODEL_2,
};

//----------------------------------------------------------------------------
typedef enum SettingMenu
{
   DATENTIME_MENU,
   LOCATION_MENU,
   PSWDNLOGO_MENU,
   TOTAL_SETTING_MENU,
}SettingMenu_t;

MenuState_t SettingMenu_States[TOTAL_SETTING_MENU] =
{
   DATENTIME,
   LOCATION,
   PSWDNLOGO
};
TEXT_T Setting_Menu_Items[]=
{
   STR_DATE_AND_TIME,
   STR_LOCATION_NAME,
   STR_PASSWORD_LOGO,
};

//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
typedef enum PswdLogo
{
   CHNG_PSWD_MENU,
   //CHNG_LOCATION_MENU,
   CHNG_LOGONAME_MENU,
   TOTAL_PSWDLOGO_MENU,
}PswdLogoMenu_t;

MenuState_t PswdLogoMenu_States[TOTAL_PSWDLOGO_MENU] =
{
   CHNG_PASSWORD,
   //LOCATION_NAME,
   CHNG_LOGONAME
};

TEXT_T PswdLogo_Menu_Items[]=
{
   STR_CHANGE_PASSWORD,
   //STR_LOCATION_NAME,
   STR_CHANGE_LOGONAME,
};

//-----------------------------------------------------------------------------

typedef struct Menu_s
{
   MenuState_t   MenuId;
   unsigned char TotalMenuItems;
   TEXT_T * MenuItems;
   MenuState_t *MenuState;
   MenuState_t  PrevState;
}Menu_t;

Menu_t MenuArr[NO_OF_MENUS]=
{
   {0,0,0,0},
   {0,0,0,0},
//  MenuState      TotalNo of Items    Menu Items            Item's Menustates      Previous MenuState     //EnggMenuFlag
   { MAIN,      TOTAL_MAIN_MENU,       Main_Menu_Items,      MainMenu_States,         NULL                 },
   { ISOLATE,   TOTAL_ISOLATE_MENU,    Isolate_Menu_Items,   IsolateMenu_States,      MAIN                 },
   { TESTMODE,    0,    0,   0,                                                       MAIN              },
   { SETTING,   TOTAL_SETTING_MENU,   Setting_Menu_Items,     SettingMenu_States,      MAIN                 },
   { HISTORY,    0,    0,   0,                                                       MAIN              },
   //{ HISTORY, TOTAL_HISTORY_MENU,      History_Menu_Items, MAIN}
   { ZONE_ISO,    0,    0,   0,                                                       ISOLATE              },
   { HOOTER_ISO,  0,    0,   0,                                                       MAIN                 },
   { DATENTIME,  0,    0,   0,                                                         SETTING              },
   { LOCATION,   0,    0,   0,                                                         SETTING              },
   { PSWDNLOGO,  TOTAL_PSWDLOGO_MENU,    PswdLogo_Menu_Items,   PswdLogoMenu_States,   SETTING              },
   { CHNG_PASSWORD,  0,    0,   0,                                                     SETTING              },
   { CHNG_LOGONAME,  0,    0,   0,                                                     SETTING              },

 
};

void Init_Menu(void);
void ProcessMenu(void);
void PSWDExpiration(void);
unsigned char IsPSWDExpired(void);
void ClearPSWDExpired(void);
/*****************************************************************************
 * EOF
 *****************************************************************************/
#endif
