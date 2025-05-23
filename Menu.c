/*****************************************************************************
 *
 * MENU
 *
 *****************************************************************************
 * FileName:        Menu.c
 * Dependencies:    system.h , Menu.h
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
#include "system.h"
#include "Menu.h"
#include "ZoneProcess.h"
#include "SystemProcess.h"


#define  BUZZER _LATG2

#define INITIAL_STATE    1
#define ENTER_STATE      2
#define INTER_1_STATE    3
#define INTER_2_STATE    4
#define INTER_3_STATE    5
#define INTER_4_STATE    6
#define INVALID_STATE    7
#define EXIT_STATE       8



extern Zone_t ZoneArr[24];

static unsigned char MenuState;
//static KeyState_t *pKeyarr;
static unsigned char selected=0, KeyChar=0, KeyFlag=0;
unsigned static char  PswdChar[4];
unsigned char ZoneChar[2] = {0,0};
unsigned char TempBuf[10] = {0,0,0,0,0,0,0,0,0,0};
unsigned char ZoneLocation[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char LogoName[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char ZoneNo;
unsigned char FnState = 0;
unsigned char i;
unsigned char DgtCount =0;
static unsigned char ItemCount=0;
static unsigned char PSWDExpired=0;
static MenuState_t Menuid;

static void InitMenuFunc(void);
static void PswdEnterFunc(void);
//static void MainMenuFunc(void);
static void GeneralMenuFunc(void);
static void TestModeFunc(void);
static void IsolateZoneFunc(void);
static void IsolateHooterFunc(void);
static void DateTimeSetFunc(void);    //DATENTIME
static void LocationSetFunc(void);    //LOCATION
static void GeneralMenuFunc(void);    //PSWDNLOGO
static void ChangePasswordFunc(void);  //CHNG_PASSWORD
static void ChangeLogoFunc(void);       //CHNG_LOGONAME

void SWDelayms(unsigned int cnt);
extern void SetNoofBeep(unsigned char );; 
void Init_Menu(void)
{
   MenuState = INIT;//PASSWORD;               
}

typedef void (*lcdMenuFunc)(void);

const lcdMenuFunc lcdMenuFuncTable[] = 
{
   InitMenuFunc,
   PswdEnterFunc,
   GeneralMenuFunc,    //MAIN
   GeneralMenuFunc,    //ISOLATE
   TestModeFunc,       //TESTMODE
   GeneralMenuFunc,    //SETTING
   GeneralMenuFunc,    //HISTORY
   IsolateZoneFunc,    //ZONE_ISO
   IsolateHooterFunc,  //HOOTER_ISO
   DateTimeSetFunc,    //DATENTIME
   LocationSetFunc,    //LOCATION
   GeneralMenuFunc,    //PSWDNLOGO
   ChangePasswordFunc,  //CHNG_PASSWORD
   ChangeLogoFunc,       //CHNG_LOGONAME
   
/*#ifdef USER_UART_INTERFACE_ENABLE
  UserInterface,
#endif // USER_UART_INTERFACE_ENABLE  
 */
};
void ProcessMenuState(void)
{
   lcdMenuFuncTable[MenuState]();
   return;
}


/**********************************************************************
 *                     MenuFunctions                                  *
 **********************************************************************/


void PSWDExpiration(void)
{
   static unsigned int CheckExpiration;
   static unsigned long int PSWDExpiredCounter;

   if(MenuState == MAIN)
   {
      if(CheckExpiration == 0)    
      {
         CheckExpiration = TRUE; PSWDExpiredCounter =0;
      } 
   }
   if(CheckExpiration)
   {
      if((PSWDExpiredCounter < 10)&&(PSWDExpired == FALSE)) //Password is valid for 5 min after entering menu
      {
         PSWDExpiredCounter++;SetNoofBeep(1); 
      }
      else
      {
         PSWDExpired = TRUE; SetNoofBeep(1); LINE2();  LCD_PrintString(" PASSWORD EXPIRED..!");
         PSWDExpiredCounter =0;CheckExpiration =0;
      }       
   }
}

unsigned char IsPSWDExpired(void)
{
   return PSWDExpired;
}

void ClearPSWDExpired(void)
{
   PSWDExpired = TRUE;
}


static void InitMenuFunc(void)
{
   LINE1();LCD_PrintString(DateTimeStr); 
 //TODO :  Add initialization sequence
   if((GetKeyChar() == 'M')&& ISKeyFlag())
   {
      if((PSWD_ENABLE == TRUE)&&(IsPSWDExpired() == TRUE)) 
      {
         MenuState = PASSWORD;LINE2(); 
      }
      else
      {
         LINE2();
         MenuState = MAIN;
      }
   } 
}

static void PswdEnterFunc(void)
{
   static unsigned char ItemCount=0; 
   static unsigned int ExitCounter;
   static unsigned char j;

   KeyFlag = ISKeyFlag(); 
   
   switch(FnState)
   {
      case INITIAL_STATE:
      {
         LINE1();LCD_PrintText(STR_ENTER_PASSWORD);
         SETPOS_R2C6;FnState = ENTER_STATE;DgtCount =0;
         break;
      }   
      case ENTER_STATE:
      {
         if(ExitCounter < 100)
         {ExitCounter++;}
         else
         {
           ExitCounter =0;LCD_CLEAR();ItemCount=0;FnState =INITIAL_STATE;
           MenuState = INIT; SetSystemState( IDLE_STATE);
         } 
         CURSOR_BLINK(); 
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if((KeyChar >= '0') && (KeyChar <= '9')) 
            {
               if(DgtCount< 4)
               {
                  TempBuf[DgtCount] = KeyChar;
                  lcd_data(KeyChar);
               }                  
               if(DgtCount >= 3)
               {
                 // Read Pswd from eeprom ADDR_PSWD
                  for(j=0;j<4;j++)
                  {  
                     PswdChar[j] = EEPROMReadByte(ADDR_PSWD+j);
                     lcd_data(PswdChar[j]);
                  }
                  if((TempBuf[0] == PswdChar[0]) && (TempBuf[1] == PswdChar[1]) && (TempBuf[2] == PswdChar[2]) && (TempBuf[3] == PswdChar[3]))
                  {
                     CURSOR_OFF();LCD_CLEAR();FnState = EXIT_STATE;
                  }   
                  else
                  {
                     CURSOR_OFF();FnState = INVALID_STATE;DgtCount =0;LCD_CLEAR();
                  }
               }
               DgtCount++;                
            }   
            ExitCounter =0 ;
            ClearKeyFlag(); 
         }
         break;
      }   
      case EXIT_STATE:
      {
         //Enable MENU state and Run Menu
        MenuState = MAIN; DgtCount =0;LCD_CLEAR();SWDelayms(50);ExitCounter =0;
        break;
      }
      case INTER_3_STATE:
      {
         SWDelayms(300);BUZZER = 0;SWDelayms(1000);
         LCD_CLEAR();FnState = INITIAL_STATE;MenuState = PASSWORD;
         // Keep in same state for 10 secconds
         break;
      }
      case INVALID_STATE:
      {
         LCD_PrintString("INVALID PASSWORD");    // Invalid Old Pasword
         FnState = INTER_3_STATE;
         break;
      }

      default: break;
   }
}

static void GeneralMenuFunc(void)
{
   unsigned char Esc = 0;
   CURSOR_OFF();
   KeyFlag = ISKeyFlag();
   Menuid = MenuState;
   selected = FALSE;
  
   if(KeyFlag == TRUE)
   {
      KeyChar = GetKeyChar();
      switch(KeyChar)
      {
        //TODO case 'M': LCD_CLEAR();//MenuReset()
        //    break;
         case 'D': // DOWN KEY
            (ItemCount<MenuArr[Menuid].TotalMenuItems - 1)?  (ItemCount++): (ItemCount = 0);
           
            LCD_CLEAR();  
            break;
         case 'U': //UP KEY
            (ItemCount>0)? (ItemCount--) :(ItemCount = (MenuArr[Menuid].TotalMenuItems-1));
             LCD_CLEAR();
            break;
         case 'E': // ENTER KEY
             selected = TRUE;
             if(MenuArr[Menuid].MenuState != NULL) 
             {
                LCD_CLEAR();MenuState = MenuArr[Menuid].MenuState[ItemCount];
                ItemCount=0; FnState =INITIAL_STATE;
             }             
            break;
         case 'C':  //ESC key for menu back (Previous Menu)
             if(((int)MenuArr[Menuid].MenuState != MAIN) && (MenuArr[Menuid].PrevState != NULL))
             {
                LCD_CLEAR();MenuState = MenuArr[Menuid].PrevState;
                Esc = 1;
             }
             else             
             {
                LCD_CLEAR();//MenuReset() Come out of Menu
                ItemCount=0; Esc = 1;MenuState = INIT; SetSystemState( IDLE_STATE);
             }              
            break;
         default: break;
      }   
       KeyChar ='X';
      
        KeyFlag = FALSE;ClearKeyFlag(); 
   }
   if((selected == FALSE) && (Esc == 0 ))
   {
      LINE1();lcd_data('>');LCD_PrintText(MenuArr[Menuid].MenuItems[ItemCount]);
      if((ItemCount+1) == (MenuArr[Menuid].TotalMenuItems))   
        {LINE2();lcd_data(' ');LCD_PrintText(MenuArr[Menuid].MenuItems[0]);}
      else
      {
         LINE2();lcd_data(' ');LCD_PrintText(MenuArr[Menuid].MenuItems[ItemCount+1]);
      }
   }      
}

static void IsolateZoneFunc(void)
{
   KeyFlag = ISKeyFlag(); 
   switch(FnState)
   {
      case INITIAL_STATE :
      {
         //Enter zone no... 
         LINE1();LCD_PrintText(STR_ZONE_ISOLATION);
         LINE2();LCD_PrintText(STR_ENTER_ZONE_NO);
         FnState = ENTER_STATE;
         break;
      }   
      case ENTER_STATE:
      {
         CURSOR_BLINK(); 
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if( ((KeyChar >= '0') && (KeyChar <= '9')) ||
                 (KeyChar == 'E') || (KeyChar == 'C') )
            {
               if(i< 2)
               {
                  if((KeyChar >= '0') && (KeyChar <= '9')) 
                  {
                     ZoneChar[i] = KeyChar;
                     lcd_data( KeyChar);
                  }
                  else
                  {
                     CURSOR_OFF();FnState = INVALID_STATE;i =0;LCD_CLEAR();
                  }                        
               } 
               if(KeyChar == 'E')
               {
                  if(i< 2)
                  {
                     CURSOR_OFF();FnState = INVALID_STATE;i =0;LCD_CLEAR();
                  }
                  else
                  {
                     ZoneNo = ((ZoneChar[0]- 0x30)*10  + (ZoneChar[1]- 0x30));
                     if( ZoneNo > NO_OF_ZONES)
                     { CURSOR_OFF();FnState = INVALID_STATE;i =0;LCD_CLEAR(); }
                     else
                     {CURSOR_OFF();LCD_CLEAR();FnState = INTER_1_STATE;}
                  }   
               }
               else if(KeyChar == 'C')
               {   
                  CURSOR_OFF();FnState = INITIAL_STATE ;i =0;LCD_CLEAR();MenuState = ISOLATE;
               }
               i++;                
            }
            else
            {
                CURSOR_OFF();FnState = INVALID_STATE;i =0;LCD_CLEAR();
            }
            ClearKeyFlag(); 
         }
         break;
      }   
      case INTER_1_STATE:
      {
         if(ZoneArr[ZoneNo].isolate_flg == TRUE)
         {
            ZoneArr[ZoneNo].isolate_flg = FALSE;
            EEPROMWriteByte('A', (ADDR_ZONE_ISOLATE_START+ZoneNo));
            LINE1();LCD_PrintText(STR_ZONE_NO); 
            lcd_data(ZoneChar[0]); 
            lcd_data(ZoneChar[1]); 
            LINE2();LCD_PrintText(STR_ACTIVATED); 
            i = 0;
            FnState = INTER_3_STATE;
         }
         else
         {
            ZoneArr[ZoneNo].isolate_flg = TRUE;
            EEPROMWriteByte('I', (ADDR_ZONE_ISOLATE_START+ZoneNo));
            LINE1();LCD_PrintText(STR_ZONE_NO); 
            lcd_data(ZoneChar[0]); 
            lcd_data(ZoneChar[1]); 
            LINE2();LCD_PrintText(STR_ISOLATED); 
            i = 0;
            FnState = INTER_3_STATE;
         } 
         break;
      }  
      case INTER_3_STATE:
      {
         SWDelayms(300);
         BUZZER = 0;
         SWDelayms(1500);
         LCD_CLEAR();
         i = 0;
         FnState = INITIAL_STATE ;
         break;
      }
      case INVALID_STATE:
      {
         LCD_PrintString("INVALID INPUT");   
         FnState = INTER_3_STATE;
         break;
      } 
      default: break;
   }
}


static void IsolateHooterFunc(void)
{
  static unsigned char flag=0; 
  KeyFlag = ISKeyFlag(); 
 
   switch(FnState)
   {
      case INITIAL_STATE:
      {
         LINE1();LCD_PrintText(STR_HOOTER_ISOLATION);
         LINE2();LCD_PrintText(STR_YES_NO);
         SETPOS_R2C5;lcd_data('[');
         SETPOS_R2C9;lcd_data(']');
         flag = 1;                       // Deault is YES
         FnState = ENTER_STATE;
         break;
      }   
      case ENTER_STATE:
      {
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if( ((KeyChar == 'L') || (KeyChar <= 'R')) ||
                 (KeyChar == 'E') || (KeyChar == 'C') )
            {
               if(KeyChar == 'L') 
               {
                  lcd_cmd(0xca);lcd_data(' ');
                  lcd_cmd(0xcd);lcd_data(' ');
                  lcd_cmd(0xc4);lcd_data('[');
                  lcd_cmd(0xc8);lcd_data(']');
                  flag = 1;
               }
               else if(KeyChar == 'R') 
               {
                  lcd_cmd(0xc4);lcd_data(' ');
                  lcd_cmd(0xc8);lcd_data(' ');
                  lcd_cmd(0xca);lcd_data('[');
                  lcd_cmd(0xcd);lcd_data(']');
                  flag = 2;
               }
               if(KeyChar == 'E')
               {                     
                  LCD_CLEAR();FnState = INTER_1_STATE;
               }
               else if(KeyChar == 'C')
               {   
                  FnState = INITIAL_STATE;LCD_CLEAR();MenuState = ISOLATE;
               }
            }
            else
            {
                CURSOR_OFF();FnState = INVALID_STATE;LCD_CLEAR();
            }
            ClearKeyFlag(); 
         }
         break;
      }   
      case INTER_1_STATE:
      {
         if(flag == 2)
         {
            Event.HooterIsolate_flg = FALSE;
            EEPROMWriteByte('A', ADDR_HOOTER_ISOLATE);
            LINE1();LCD_PrintText(STR_COMMON_HOOTER); 
            LINE2();LCD_PrintText(STR_ACTIVATED); 
            FnState = INTER_3_STATE;
         }
         else if(flag == 1)
         {
            Event.HooterIsolate_flg = TRUE;
            EEPROMWriteByte('I', ADDR_HOOTER_ISOLATE);
            LINE1();LCD_PrintText(STR_COMMON_HOOTER); 
            LINE2();LCD_PrintText(STR_ISOLATED); 
            FnState = INTER_3_STATE;
         } 
         else { }
         break;
      }  
      case INTER_3_STATE:
      {
         SWDelayms(300);
         BUZZER = 0;
         SWDelayms(1500);
         LCD_CLEAR();
         FnState = INITIAL_STATE;
         MenuState = MAIN; 
         break;
      }
      case INVALID_STATE:
      {
         LCD_PrintString("INVALID INPUT");   
         FnState = INTER_3_STATE;
         break;
      } 
      default: break;
   }

}


static void DateTimeSetFunc(void)    //DATENTIME
{
  
   static unsigned char dt,mn,yr,hr,min;
   KeyFlag = ISKeyFlag(); 

   if(KeyFlag == TRUE)
   {
      KeyChar = GetKeyChar(); 
      if(KeyChar == 'C')
      {   
         CURSOR_OFF();FnState = INITIAL_STATE;DgtCount =0;LCD_CLEAR();MenuState = SETTING;
      }
   }
   switch(FnState)
   {
      case INITIAL_STATE:
      {
         //Enter zone no... 
         LINE1();LCD_PrintText(STR_DATE_00);
         LINE2();LCD_PrintText(STR_TIME_00);
         FnState = ENTER_STATE;
         SETPOS_R1C7;
         DgtCount =0;
         break;
      }   
      case ENTER_STATE:
      {      
         CURSOR_BLINK(); 
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if( (KeyChar >= '0') && (KeyChar <= '9') ) 
            {
               if(DgtCount< 10)
               {
                  TempBuf[DgtCount] = KeyChar - 0x30;
                  lcd_data( KeyChar);
                  if((DgtCount == 1)||(DgtCount == 3)||(DgtCount == 7))
                  {
                     CURSOR_RIGHT();                     
                  }
                  if(DgtCount == 5)
                  {
                     SETPOS_R2C7;
                  }
               } 
               if(DgtCount >= 9)
               {
                  dt = (TempBuf[0])*10  + TempBuf[1];
                  mn = (TempBuf[2])*10  + TempBuf[3];
                  yr = (TempBuf[4])*10  + TempBuf[5];
                  hr = (TempBuf[6])*10  + TempBuf[7];
                  min = (TempBuf[8])*10  + TempBuf[9];

                  if((dt == 0 || dt > 31) || (mn == 0 || mn > 12) || 
                      ( hr > 23) || ( min > 59) )
                  {
                     CURSOR_OFF();FnState = INVALID_STATE;DgtCount =0;LCD_CLEAR();
                  }
                   else
                  {
                     CURSOR_OFF();LCD_CLEAR();FnState = INTER_1_STATE;
                  }   
               }
               DgtCount++;                
            }
            else
            {
                CURSOR_OFF();FnState = INVALID_STATE;DgtCount =0;LCD_CLEAR();
            }
            ClearKeyFlag(); 
         }
         break;
      }   
      case INTER_1_STATE:
      {
         // Unlock sequence must take place for RTCEN to be written
	     _RCFGCAL	= 0x0000;			
         mRTCCUnlock();
         _RTCEN = 1;
	     mRTCCOn();
       
	     mRTCCSetDay(mRTCCBin2Dec(dt));
         mRTCCSetMonth(mRTCCBin2Dec(mn));
	     mRTCCSetYear( mRTCCBin2Dec(yr));
         mRTCCSetHour(mRTCCBin2Dec(hr));
         mRTCCSetMin(mRTCCBin2Dec(min));
         
         mRTCCSetSec(0x00);
	     mRTCCSetWkDay(0x01);
	     mRTCCSet();
         mRTCCLock();
         _rtcc_flag = 0;
         LCD_PrintString("DATE TIME SET"); 
         SWDelayms(1500);
         DgtCount = 0;
         FnState = INTER_3_STATE;
         RTCCProcessEvents();
         SWDelayms(1500);
         break;
      }  
      case INTER_3_STATE:
      {
         LINE1();LCD_PrintString(DateTimeStr); 
         SWDelayms(300);
         BUZZER = 0;
         SWDelayms(1500);
         LCD_CLEAR();
         DgtCount = 0;
         FnState = INITIAL_STATE;
         CURSOR_OFF();
         MenuState = SETTING;
         break;
      }
      case INVALID_STATE:
      {
         LCD_PrintString("INVALID INPUT");   
         FnState = INTER_2_STATE;
         break;
      } 
      case INTER_2_STATE:
      {
         BUZZER = 0;
         SWDelayms(1500);
         LCD_CLEAR();
         DgtCount = 0;
         FnState = INITIAL_STATE;
         CURSOR_OFF();
         break;
      }
      default: break;
   }
}
//------------------------------------------------------------------------------------------------
static void LocationSetFunc(void)    //LOCATION
{ 
  static unsigned char Zonno,i,j;

  KeyFlag = ISKeyFlag(); 
  if(KeyFlag == TRUE)
   {
      KeyChar = GetKeyChar(); 
      if(KeyChar == 'C')
      {   
         LCD_CLEAR();CURSOR_OFF();FnState = INITIAL_STATE;DgtCount =0;ItemCount =1; MenuState = SETTING;
         ClearKeyFlag();LCD_CLEAR();CURSOR_OFF();
      }
   }
   switch(FnState)
   {
      case INITIAL_STATE:
      {
           for(i=0;i<16;i++)
           {  
              ZoneLocation[i] = ' ';
           }
         LINE1();LCD_PrintText(STR_ENTER_ZONE_NO);
         FnState = ENTER_STATE;
         DgtCount =0;Zonno =0;
         break;
      }   
      case ENTER_STATE:
      {
         CURSOR_BLINK(); 
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if((KeyChar >= '0') && (KeyChar <= '9')) 
            {
               if(DgtCount< 2)
               {
                  TempBuf[DgtCount] = KeyChar - 0x30;
                  lcd_data( KeyChar);
               }                  
               if(DgtCount >= 1)
               {
                  Zonno = TempBuf[0]*10 + TempBuf[1];
                  if((Zonno == 0) || (Zonno > NO_OF_ZONES ))
                  {
                     CURSOR_OFF();FnState = INVALID_STATE;DgtCount =0;LCD_CLEAR(); //INVALID INPUT
                  }
                  else
                  {
                     for(i=0;i<16;i++)
                     {  
                        ZoneLocation[i] = ' ';
                     }
                     CURSOR_OFF();LINE2();FnState = INTER_1_STATE;SETPOS_R2C1;SWDelayms(300);//Proceed for location display
                  }   
               }
               DgtCount++;                
            }
            else if(KeyChar == 'C')
            {   
               LCD_CLEAR();CURSOR_OFF();FnState = INITIAL_STATE;DgtCount =0;ItemCount =1;MenuState = SETTING;
               ClearKeyFlag();LCD_CLEAR();CURSOR_OFF();
            }
            else
            {
                CURSOR_OFF();FnState = INVALID_STATE;LCD_CLEAR();
            }
            ClearKeyFlag(); 
         }
         break;
      }   
      case INTER_1_STATE:
      {     //read name(location) of zoneno from eeprom and display it.          
           
           for(j=0;j<16;j++)
           {  
              ZoneLocation[j] = EEPROMReadByte( (ADDR_ZONE1_LOCATION -16 + (Zonno*16) +j));
              lcd_data(ZoneLocation[j]);
           }
           SETPOS_R2C1;CURSOR_BLINK(); //Set cursor at the start to edit
           SWDelayms(50);
           FnState = INTER_2_STATE;
         break;
      }  
      case INTER_2_STATE:
      { 
         SETPOS_R2C1;CURSOR_BLINK(); //Set cursor at the start to edit
         AlphaNumEnable();// enable alphanumeric keypad
         FnState = INTER_4_STATE;
         for(i=0;i<16;i++)
         {   
            StringBuf[i] = ZoneLocation[i];
         }
         SWDelayms(500);
         break;
      }
      case INTER_4_STATE:
      {   
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if(KeyChar == 'E')
            {
         //      LINE1();LCD_PrintString(StringBuf);   
               for(i=0;i<16;i++)
               {  
                  ZoneLocation[i] = StringBuf[i];
               }
               // take stringbuf and store it in location name of zonno 
               for(i=0;i<16;i++)
               {  
                  EEPROMWriteByte(ZoneLocation[i], (ADDR_ZONE1_LOCATION -16 + (Zonno*16) +i));
               }
               ClearKeyFlag();
               LCD_CLEAR(); 
               FnState = EXIT_STATE;
            }
            else if(KeyChar == 'C')
            {
               CURSOR_OFF();FnState = INVALID_STATE;DgtCount =0;LCD_CLEAR(); 
            }
         }
         break;
      } 
      case EXIT_STATE:
      {  AlphaNumDisable();
         LINE1();LCD_PrintText(STR_LOCATION_SET);   
         FnState = INTER_3_STATE;
         for(i=0;i<16;i++)
         {  
            ZoneLocation[i] = ' ';
         }
         break;
      } 

      case INTER_3_STATE:
      {
         SWDelayms(300);
         BUZZER = 0;
         SWDelayms(500);
         LCD_CLEAR();
         FnState = INITIAL_STATE;
         CURSOR_OFF();FnState = INITIAL_STATE;DgtCount =0;LCD_CLEAR(); 
         MenuState = LOCATION; 
         break;
      }
      case INVALID_STATE:
      {
         LCD_PrintString("INVALID INPUT");   
         FnState = INTER_3_STATE;
         break;
      } 
      default: break;
   }
}
//---------------------------------------------------------------------------------------------
static void ChangePasswordFunc(void)  //CHNG_PASSWORD
{
   static unsigned char j;

   KeyFlag = ISKeyFlag(); 
   if(KeyFlag == TRUE)
   {
      KeyChar = GetKeyChar(); 
      if(KeyChar == 'C')
      {   
         CURSOR_OFF();FnState = INITIAL_STATE;DgtCount =0;LCD_CLEAR();MenuState = PSWDNLOGO;
      }
   }
   switch(FnState)
   {
      case INITIAL_STATE :
      {
         LINE1();LCD_PrintText(STR_OLD_PASSWORD);
         SETPOS_R2C6;
         FnState = ENTER_STATE;
         DgtCount =0;
         break;
      }   
      case ENTER_STATE:
      {
         CURSOR_BLINK(); 
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if((KeyChar >= '0') && (KeyChar <= '9')) 
            {
               if(DgtCount< 4)
               {TempBuf[DgtCount] = KeyChar;lcd_data(KeyChar);}                  
               if(DgtCount >= 3)
               {
                 // Read Pswd from eeprom ADDR_PSWD
                  for(j=0;j<4;j++)
                  {  
                     PswdChar[j] = EEPROMReadByte(ADDR_PSWD+j);lcd_data(PswdChar[j]);
                  }
                  if((TempBuf[0] == PswdChar[0]) && (TempBuf[1] == PswdChar[1]) && (TempBuf[2] == PswdChar[2]) && (TempBuf[3] == PswdChar[3]))
                  {
                     CURSOR_OFF();LCD_CLEAR();FnState = INTER_1_STATE;
                  }   
                  else
                  {
                     CURSOR_OFF();FnState = INVALID_STATE;DgtCount =0;LCD_CLEAR();
                  }
               }
               DgtCount++;                
            }   
            ClearKeyFlag(); 
         }
         break;
      }   
      case INTER_1_STATE:
      {
         LINE1();LCD_PrintText(STR_NEW_PASSWORD);
         SETPOS_R2C6;
         FnState = INTER_2_STATE;
         DgtCount =0;
         break;
      }  
      case INTER_2_STATE:
      {
         CURSOR_BLINK(); 
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if((KeyChar >= '0') && (KeyChar <= '9')) 
            {
               if(DgtCount< 4)
               {TempBuf[DgtCount] = KeyChar;lcd_data(KeyChar);}                  
               if(DgtCount >= 3)
               {               
                  for(j=0;j<4;j++)
                  {  EEPROMWriteByte(TempBuf[j],(ADDR_PSWD+j)); }
                  CURSOR_OFF();FnState = INTER_3_STATE;DgtCount =0;LCD_CLEAR();
               }
               DgtCount++;                
            }   
            ClearKeyFlag(); 
         }
         break;
      }     
      case INTER_3_STATE:
      {
         //Write Tempuf[] to eeprom
         LINE1();LCD_PrintText(STR_NEW_PASSWORD);
         SETPOS_R2C5; LCD_PrintText(STR_UPDATED);
         FnState = INTER_4_STATE;
         break;
      }
      case INVALID_STATE:
      {
         LCD_PrintString("INVALID PASSWORD");    // Invalid Old Pasword
         FnState = INTER_4_STATE;
         break;
      }
      case INTER_4_STATE:
      {
         SWDelayms(300);
         BUZZER = 0;
         SWDelayms(1500);
         LCD_CLEAR();
         FnState = INITIAL_STATE ;
         MenuState = PSWDNLOGO; 
         break;
      }
  /*  case 7:
      {
         LCD_PrintString("INVALID PASSWORD");   // Invalid new Password
         FnState = INTER_1_STATE;
         SWDelayms(300);
         BUZZER = 0;
         SWDelayms(1500);
         LCD_CLEAR();
         break;
      }  
*/
      default: break;
   }
}
static void ChangeLogoFunc(void)       //CHNG_LOGONAME
{ 
  static unsigned char i,j;

  KeyFlag = ISKeyFlag(); 
  if(KeyFlag == TRUE)
   {
      KeyChar = GetKeyChar(); 
      if(KeyChar == 'C')
      {   
         LCD_CLEAR();CURSOR_OFF();FnState = INITIAL_STATE;ItemCount =1; MenuState = PSWDNLOGO;
         ClearKeyFlag();LCD_CLEAR();CURSOR_OFF();
      }
   }
   switch(FnState)
   {
      case INITIAL_STATE:
      {
         for(i=0;i<16;i++)
         {  
            LogoName[i] = ' ';
         }
         LINE1();LCD_PrintText(STR_CHANGE_LOGO_NAME);
         FnState = ENTER_STATE;LINE2();SETPOS_R2C1;SWDelayms(300);
         break;
      }   
     
      case ENTER_STATE:
      {     //read Logo from eeprom and display it.                  
         for(j=0;j<16;j++)
         {  
            LogoName[j] = EEPROMReadByte( (ADDR_LOGONAME +j));
            lcd_data(LogoName[j]);
         }
         SETPOS_R2C1;CURSOR_BLINK(); //Set cursor at the start to edit
         SWDelayms(50);
         FnState = INTER_1_STATE;
         break;
      }  
      case INTER_1_STATE:
      { 
         SETPOS_R2C1;CURSOR_BLINK(); //Set cursor at the start to edit
         AlphaNumEnable();// enable alphanumeric keypad
         FnState = INTER_2_STATE;
         for(i=0;i<16;i++)
         { 
           StringBuf[i] = LogoName[i]; 
         }
         SWDelayms(500);
         break;
      }
      case INTER_2_STATE:
      {   
         if(KeyFlag == TRUE)
         {
            KeyChar = GetKeyChar(); 
            if(KeyChar == 'E')
            {
         //      LINE1();LCD_PrintString(StringBuf);   
               for(i=0;i<16;i++)
               {  
                  LogoName[i] = StringBuf[i];
               }
               // take stringbuf and store it in logo 
               for(i=0;i<16;i++)
               {  
                  EEPROMWriteByte(LogoName[i], (ADDR_LOGONAME +i));
               }
               ClearKeyFlag();
               LCD_CLEAR(); 
               FnState = INTER_3_STATE;
            }
            else if(KeyChar == 'C')
            {
               for(i=0;i<16;i++)
               {  
                  LogoName[i] = StringBuf[i];
               }
               // take stringbuf and store it in logo 
               for(i=0;i<16;i++)
               {  
                  EEPROMWriteByte(LogoName[i], (ADDR_LOGONAME +i));
               }
               ClearKeyFlag();
               LCD_CLEAR(); 
               FnState = INTER_4_STATE;
            }
         }
         break;
      } 
      case INTER_3_STATE:
      {  
         AlphaNumDisable();
         LINE1();LCD_PrintText(STR_LOGO_CHANGED);   
         FnState = INTER_4_STATE;
         for(i=0;i<16;i++)
         {  
            ZoneLocation[i] = ' ';
         }
         break;
      } 

      case INTER_4_STATE:
      {
         SWDelayms(300);
         BUZZER = 0;
         SWDelayms(500);
         LCD_CLEAR();
         CURSOR_OFF();FnState = INITIAL_STATE;LCD_CLEAR(); 
         MenuState = CHNG_LOGONAME; 
         break;
      }
      case INVALID_STATE:
      {
         LCD_PrintString("INVALID INPUT");   
         FnState = INTER_4_STATE;
         break;
      } 
      default: break;
   }
}

static void TestModeFunc(void)
{
 // Implentation of Testmode
 // WALK TEST
 // ENTER ZONE NO:
 // ENTER key will start testmode

}


void SWDelayms(unsigned int cnt)
{
   unsigned int i,j;
   for (j = 0; j< 50; j++)
   {  
      for(i = 0;i< cnt*3;i++)
      {
         ;
      }
   }
}
