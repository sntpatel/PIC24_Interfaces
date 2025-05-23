/*****************************************************************************
 *
 * KEYPAD
 *
 *****************************************************************************
 * FileName:        Keypad.c
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
#include "system.h"
//#include "Keypad.h"

extern void lcd_cmd(char);
extern void SetNoofBeep(unsigned char);

#define  MENU     PORTCbits.RC1 
#define  SILENCE  PORTCbits.RC2 
#define  EVAC     PORTCbits.RC3
#define  RESET    PORTCbits.RC4 

//Matrix Keypad
/*#define  R1     _LATD0 
#define  R2     _LATD1
#define  R3     _LATD2
#define  R4     _LATD3
#define  C1     _LATD4
#define  C2     _LATD5
#define  C3     _LATD6
#define  C4     _LATD7
*/

static KeyState_t Key[NO_OF_KEYIDS];
static unsigned  char KeyFlag;

static unsigned  char KeyChar;
static unsigned  char Row,KeyNumber;
static unsigned int PortValue;
static unsigned  char KeyFlagMat1, KeyFlagMat2,KeyFlagMat3,KeyFlagMat4;
static unsigned int IdleCount1, IdleCount2 , IdleCount3, IdleCount4;

unsigned int RowArr[4] = { 0xFD ,0xFB, 0xF7, 0xFE };
//unsigned int RowArr[4] = { 0xFE, 0xFB ,0xFE, 0xFD};

 static unsigned char KeyPadMatrix[18] = 
 { 
     0xFF,
     'C','1','2','3',
     'U','4','5','6',
     'D','7','8','9',
     'L','R','0','E',
     0xFF
 };
//----------------------Alpha numeric Key-----------------------------------------------------------
struct AlnumKeypad
{
  struct
  {
    char char1;
    char char2;
    char char3;
  };
}AalNumKey[9];
//Initialise array
unsigned char charStart = 'A';
unsigned  char StringBuf[16] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
static unsigned char AlphaNumFlag = 0;

static unsigned int BlinkCount=0;
static unsigned int PressCount=0;
static unsigned char CharCount;
static unsigned char CurrentChar=0;
static unsigned char FnState=0;
//------------------------------------------------------------------------------------------------


//static unsigned char MatrixKeypadScan(void);
//static void MatrixKeypadScan(void);

void Keypad_Init(void)
{
   _TRISC1 = 1; //Menu Key
   _TRISC2 = 1; //Silence Key
   _TRISC3 = 1; //Evacuation Key
   _TRISC4 = 1; //Reset Key
//Matrix Keypad
   _TRISD0 = 0; // ROW 1
   _TRISD1 = 0; // ROW 2
   _TRISD2 = 0; // ROW 3
   _TRISD3 = 0; // ROW 4
   _TRISD4 = 1; // COL 1
   _TRISD5 = 1; // COL 2
   _TRISD6 = 1; // COL 3
   _TRISD7 = 1; // COL 4
   unsigned int keycount;
   for(keycount = 0; keycount< NO_OF_KEYIDS; keycount++)
   {
      Key[keycount].KeyFlag          = FALSE;
      Key[keycount].Pressed          = FALSE;
      Key[keycount].Released         = FALSE;
      Key[keycount].ReleaseTimeCnt   = FALSE;
      Key[keycount].PressTimeCnt     = FALSE;
   }
}

void Keypad_Task(void)
{
   if(EVAC == HIGH)
   {
      Key[EVAC_KEY].PressTimeCnt = 0; //Cancel the press detected
   }
   if((EVAC == LOW) && (Key[EVAC_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
   {
      Key[EVAC_KEY].PressTimeCnt++;
   }
   else if((EVAC == LOW) && (Key[EVAC_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
   {
      Key[EVAC_KEY].PressTimeCnt = 0;
      Key[EVAC_KEY].KeyFlag = TRUE;
      KeyFlag = TRUE;
      KeyChar = 'V';
   //   LINE1(); lcd_data('V');
      SetNoofBeep(1);
   }

/*---------------------------------------------------------------------------------*/
   if(RESET == HIGH)
   {
      Key[RESET_KEY].PressTimeCnt = 0; //Cancel the press detected
   }
   if((RESET == LOW) && (Key[RESET_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
   {
      Key[RESET_KEY].PressTimeCnt++;
   }
   else if((RESET == LOW) && (Key[RESET_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
   {
      Key[RESET_KEY].PressTimeCnt = 0;
      Key[RESET_KEY].KeyFlag = TRUE;
      KeyFlag = TRUE;
      KeyChar = 'T';
      SetNoofBeep(1); LINE1();lcd_data('T');
   }

/*---------------------------------------------------------------------------------*/
   if(MENU == HIGH)
   {
      Key[MENU_KEY].PressTimeCnt = 0; //Cancel the press detected
   }
   if((MENU == LOW) && (Key[MENU_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
   {
      Key[MENU_KEY].PressTimeCnt++;
   }
   else if((MENU == LOW) && (Key[MENU_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
   {
      Key[MENU_KEY].PressTimeCnt = 0;
      Key[MENU_KEY].KeyFlag = TRUE;
      KeyFlag = TRUE;
      KeyChar = 'M';
      SetNoofBeep(1);// LINE1(); lcd_data('M');
   }
/*---------------------------------------------------------------------------------*/
   if(SILENCE == HIGH)
   {
      Key[SILENCE_KEY].PressTimeCnt = 0; //Cancel the press detected
   }
   if((SILENCE == LOW) && (Key[SILENCE_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
   {
      Key[SILENCE_KEY].PressTimeCnt++;
   }
   else if((SILENCE == LOW) && (Key[SILENCE_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
   {
      Key[SILENCE_KEY].PressTimeCnt = 0;
      Key[SILENCE_KEY].KeyFlag = TRUE;
      KeyFlag = TRUE;
      KeyChar = 'S';
      SetNoofBeep(1); LINE1();lcd_data('S');
   }

/*---------------------------------------------------------------------------------*/
//================ Matrix Scan ===================================
   //KeyNumber = 0;
  // Row = 0;
 switch(Row)
 {
    case 0:
          PORTD = RowArr[Row];//0xFD;
          PortValue = PORTD & 0xF0;

          if((PortValue ==  0xE0) && (Key[ESC_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
          {
             Key[ESC_KEY].PressTimeCnt++;
          }
          else if((PortValue ==  0xE0) && (Key[ESC_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
          {
             KeyNumber = 1;
             KeyFlagMat1= TRUE;
          }
          else
          {
             Key[ESC_KEY].PressTimeCnt = 0;
          }
/*********************  1  ************************/
         if((PortValue ==  0xD0) && (Key[KEY_1].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
          {
             Key[KEY_1].PressTimeCnt++;
          }
          else if((PortValue ==  0xD0) && (Key[KEY_1].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
          {
             KeyNumber = 2;
             KeyFlagMat1= TRUE;
          }
          else
          {
             Key[KEY_1].PressTimeCnt = 0;
          }
/*********************  2  ************************/
         if((PortValue ==  0xB0) && (Key[KEY_2].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
          {
             Key[KEY_2].PressTimeCnt++;
          }
          else if((PortValue ==  0xB0) && (Key[KEY_2].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
          {
             KeyNumber = 3;
             KeyFlagMat1= TRUE;
          }
          else
          {
             Key[KEY_2].PressTimeCnt = 0;
          }
/*********************  3  ************************/
         if((PortValue ==  0x70) && (Key[KEY_3].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
         {
            Key[KEY_3].PressTimeCnt++;
         }
         else if((PortValue ==  0x70) && (Key[KEY_3].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
         {
            KeyNumber = 4;
            KeyFlagMat1= TRUE;
         }
         else
         {
            Key[KEY_3].PressTimeCnt = 0;
         }
                   
    
 if((KeyFlagMat1 == TRUE) && (PortValue == 0xF0) && (IdleCount1 < IDLETIME_CNT))
       IdleCount1++;
     else if((KeyFlagMat1 == TRUE) && (PortValue == 0xF0) && (IdleCount1 >= IDLETIME_CNT))

        {  
           KeyFlag = TRUE;
          Key[KeyNumber].KeyFlag = TRUE;
          KeyChar = KeyPadMatrix[ KeyNumber ];
          KeyFlagMat1 = FALSE;
        //  LINE1();lcd_data(KeyChar);
          SetNoofBeep(1); 
          KeyNumber = 0;
          IdleCount1 = 0;
          break;
       }

      Row = 1;
      case 1:
            PORTD = RowArr[Row];//0xFB;
            PortValue = PORTD & 0xF0;
    /********************* UP  ************************/
        if((PortValue ==  0xE0) && (Key[UP_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
         {
            Key[UP_KEY].PressTimeCnt++;
         }
         else if((PortValue ==  0xE0) && (Key[UP_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
         {
            KeyNumber = 5;
            KeyFlagMat2= TRUE;
         }
         else
         {
            Key[UP_KEY].PressTimeCnt = 0;
         }
/*********************  4  ************************/
        if((PortValue ==  0xD0) && (Key[KEY_4].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
         {
            Key[KEY_4].PressTimeCnt++;
         }
         else if((PortValue ==  0xD0) && (Key[KEY_4].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
         {
            KeyNumber = 6;
            KeyFlagMat2= TRUE;
         }
         else
         {
            Key[KEY_4].PressTimeCnt = 0;
         }

/*********************  5  ************************/
        if((PortValue ==  0xB0) && (Key[KEY_5].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
         {
            Key[KEY_5].PressTimeCnt++;
         }
         else if((PortValue ==  0xB0) && (Key[KEY_5].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
         {
            KeyNumber = 7;
            KeyFlagMat2= TRUE;
         }
         else
         {
            Key[KEY_5].PressTimeCnt = 0;
         }

/*********************  6  ************************/
        if((PortValue ==  0x70) && (Key[KEY_6].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
         {
            Key[KEY_6].PressTimeCnt++;
         }
         else if((PortValue ==  0x70) && (Key[KEY_6].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
         {
            KeyNumber = 8;
            KeyFlagMat2= TRUE;
         }
         else
         {
            Key[KEY_6].PressTimeCnt = 0;
         }

      if((KeyFlagMat2 == TRUE) && (PortValue == 0xF0) && (IdleCount2 < IDLETIME_CNT))
       IdleCount2++;
     else if((KeyFlagMat2 == TRUE) && (PortValue == 0xF0) && (IdleCount2 >= IDLETIME_CNT))

        {  
           KeyFlag = TRUE;
          Key[KeyNumber].KeyFlag = TRUE;
          KeyChar = KeyPadMatrix[ KeyNumber ];
          KeyFlagMat2 = FALSE;
        //  LINE1();lcd_data(KeyChar);
          SetNoofBeep(1); 
          KeyNumber = 0;
          IdleCount2 = 0;
          break;
       }

  

            Row = 2;
      case 2:
            PORTD = RowArr[Row];//0xF7;
            PortValue = PORTD & 0xF0;
      
 /*********************  DN  ************************/
        if((PortValue ==  0xE0) && (Key[DN_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[DN_KEY].PressTimeCnt++;
        }
        else if((PortValue ==  0xE0) && (Key[DN_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 9;
           KeyFlagMat3= TRUE;
        }
        else
        {
           Key[DN_KEY].PressTimeCnt = 0;
        }
/*********************  7  ************************/
        if((PortValue ==  0xD0) && (Key[KEY_7].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[KEY_7].PressTimeCnt++;
        }
        else if((PortValue ==  0xD0) && (Key[KEY_7].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 10;
           KeyFlagMat3= TRUE;
        }
        else
        {
           Key[KEY_7].PressTimeCnt = 0;
        }

/*********************  8  ************************/
        if((PortValue ==  0xB0) && (Key[KEY_8].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[KEY_8].PressTimeCnt++;
        }
        else if((PortValue ==  0xB0) && (Key[KEY_8].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 11;
           KeyFlagMat3= TRUE;
        }
        else
        {
           Key[KEY_8].PressTimeCnt = 0;
        }

/*********************  9  ************************/
        if((PortValue ==  0x70) && (Key[KEY_9].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[KEY_9].PressTimeCnt++;
        }
        else if((PortValue ==  0x70) && (Key[KEY_9].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 12;
           KeyFlagMat3= TRUE;
        }
        else
        {
           Key[KEY_9].PressTimeCnt = 0;
        }  
  
     if((KeyFlagMat3 == TRUE) && (PortValue == 0xF0) && (IdleCount3 < IDLETIME_CNT))
       IdleCount3++;
     else if((KeyFlagMat3 == TRUE) && (PortValue == 0xF0) && (IdleCount3 >= IDLETIME_CNT))

        {  
           KeyFlag = TRUE;
          Key[KeyNumber].KeyFlag = TRUE;
          KeyChar = KeyPadMatrix[ KeyNumber ];
          KeyFlagMat3 = FALSE;
         // LINE1();lcd_data(KeyNumber+0x30);//KeyChar);
         SetNoofBeep(1); 
          KeyNumber = 0;
          IdleCount3 = 0;
          break;
       }

        Row = 3;
     case 3:
          PORTD = RowArr[Row];//0xFE;
          PortValue = PORTD & 0xF0;
      
  /*********************  LT  ************************/
        if((PortValue ==  0xE0) && (Key[LT_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[LT_KEY].PressTimeCnt++;
        }
        else if((PortValue ==  0xE0) && (Key[LT_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 13;
           KeyFlagMat4= TRUE;
        }
        else
        {
           Key[LT_KEY].PressTimeCnt = 0;
        }
/*********************  RT  ************************/
        if((PortValue ==  0xD0) && (Key[RT_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[RT_KEY].PressTimeCnt++;
        }
        else if((PortValue ==  0xD0) && (Key[RT_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 14;
           KeyFlagMat4= TRUE;
        }
        else
        {
           Key[RT_KEY].PressTimeCnt = 0;
        }

/*********************  0  ************************/
        if((PortValue ==  0xB0) && (Key[KEY_0].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[KEY_0].PressTimeCnt++;
        }
        else if((PortValue ==  0xB0) && (Key[KEY_0].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 15;
           KeyFlagMat4= TRUE;
        }
        else
        {
           Key[KEY_0].PressTimeCnt = 0;
        }

/*********************  EN  ************************/
        if((PortValue ==  0x70) && (Key[EN_KEY].PressTimeCnt <= NORMAL_PRESSTIME_CNT))
        {
           Key[EN_KEY].PressTimeCnt++;
        }
        else if((PortValue ==  0x70) && (Key[EN_KEY].PressTimeCnt > NORMAL_PRESSTIME_CNT))   
        {
           KeyNumber = 16;
           KeyFlagMat4= TRUE;
        }
        else
        {
           Key[EN_KEY].PressTimeCnt = 0;
        }
    if((KeyFlagMat4 == TRUE) && (PortValue == 0xF0) && (IdleCount4 < IDLETIME_CNT))
       IdleCount4++;
     else if((KeyFlagMat4 == TRUE) && (PortValue == 0xF0) && (IdleCount4 >= IDLETIME_CNT))

        {  
           KeyFlag = TRUE;
          Key[KeyNumber].KeyFlag = TRUE;
          KeyChar = KeyPadMatrix[ KeyNumber ];
          KeyFlagMat4 = FALSE;
          //LINE1();lcd_data(KeyChar);
          SetNoofBeep(1); 
          KeyNumber = 0;
          IdleCount4 = 0;
          break;
       }

        Row = 0;
    default: Row = 0;
            break;
    }

}

unsigned char GetKey(void)
{
   unsigned char keycnt;
   for(keycnt=1;keycnt<NO_OF_KEYIDS; keycnt++)
   {
      if(Key[keycnt].KeyFlag == TRUE)
      {
         return keycnt;
      }
      else
      {
        break;
      }
   }
   return 0; 
}

KeyState_t* KeyArr(void)
{
   return Key; 
}

unsigned char ISKeyFlag(void)
{
   return KeyFlag;
}

void ClearKeyFlag(void)
{
   KeyFlag = FALSE;
}

unsigned char GetKeyChar(void)
{
   return KeyChar;
}




/*
PORTD = PORTD & 0x7FFF;  //Row 1 = 0
PORTD = PORTD & 0xBFFF;  //Row 2 = 0
PORTD = PORTD & 0xDFFF;  //Row  3 = 0
PORTD = PORTD & 0xEFFF;  //Row  4 = 0
//------------------------------------------
PORTD = PORTD  0x77FF;  //Row 1 = 0  Col 1
PORTD = PORTD  0x7BFF;  //Row 1 = 0  Col 2
PORTD = PORTD  0x7DFF;  //Row 1 = 0  Col 3
PORTD = PORTD  0x7EFF;  //Row 1 = 0  Col 4

PORTD = PORTD  0xB7FF;  //Row 2 = 0  Col 1
PORTD = PORTD  0xBBFF;  //Row 2 = 0  Col 2
PORTD = PORTD  0xBDFF;  //Row 2 = 0  Col 3
PORTD = PORTD  0xBEFF;  //Row 2 = 0  Col 4

PORTD = PORTD  0xD7FF;  //Row 3 = 0  Col 1
PORTD = PORTD  0xDBFF;  //Row 3 = 0  Col 2
PORTD = PORTD  0xDDFF;  //Row 3 = 0  Col 3
PORTD = PORTD  0xDEFF;  //Row 3 = 0  Col 4

PORTD = PORTD  0xE7FF;  //Row 4 = 0  Col 1
PORTD = PORTD  0xEBFF;  //Row 4 = 0  Col 2
PORTD = PORTD  0xEDFF;  //Row 4 = 0  Col 3
PORTD = PORTD  0xEEFF;  //Row 4 = 0  Col 4


//static unsigned char MatrixKeypadScan(void)
static void MatrixKeypadScan(void)
{
   for (row =0 ; row < 4 ; row++)
   {
      PORTD = PORTD & RowArr[0];
      PortValue = PORTD & 0xFF00;
      if(PortValue ==  0x0700)   
      {
         break;
      }  
      key++;
      if(PortValue ==  0x0B00) 
      {
        break;
      }  
      key++;
      if(PortValue ==  0x0D00) 
      {
       break;
      }  
      key++;
      if(PortValue ==  0x0E00) 
      {
       break;
      }  
      key++;
   }
   Key[key].KeyFlag = TRUE;
   KeyChar = keyPadMatrix[ key ];
   SetNoofBeep(1); LINE1();lcd_data(KeyChar);

//   return keyPadMatrix[ key ]; 
}
 
*/






void AlphaNumKeypad_Init(void )
{
   unsigned int i;
   for (i=1; i<10 ; i++)
   {
      AalNumKey[i].char1 = charStart++;  
      AalNumKey[i].char2 = charStart++;  
      AalNumKey[i].char3 = charStart++;  
   }
   AalNumKey[0].char1 =  ' ';// space
   AalNumKey[0].char2 =  NULL;
   AalNumKey[0].char3 =  NULL;
   AalNumKey[9].char3 =  NULL;
}

//----------------------------------
void AlphaNumEnable(void)
{
   AlphaNumFlag = TRUE;
}

void AlphaNumDisable(void)
{
   AlphaNumFlag = FALSE;
   BlinkCount=0;
   PressCount=0;
   CharCount=0;
   CurrentChar=0;
   FnState=0;  
   charStart = 'A';
}
unsigned char IsAlphaNumEnable(void)
{
   return AlphaNumFlag; 
}

void AlphaNumKeypad(void)
{
   
  // SETPOS_R2C1; should be called before calling this function
  if((KeyFlag == TRUE)&&(KeyChar == 'C'))
  {
     AlphaNumDisable();  //Exit from here
  } 
    
   switch(FnState)
   {
      case 0:
      {
         if(KeyFlag == TRUE)
         {  
            if(KeyChar == 'L')
            {  if(CharCount >0) CharCount--;CURSOR_LEFT();KeyFlag = 0;}
            else if(KeyChar == 'R')
            {  if(CharCount < 16) CharCount++;  CURSOR_RIGHT();KeyFlag = 0;}
            else if(KeyChar == 'E') //KeyFlag = 0; should be done by calling function
            {   CURSOR_OFF();  BlinkCount = 0; PressCount = 0; CharCount =0;}//KeyFlag = 0;
             //SETPOS_R1C1;LCD_PrintString(StringBuf);   
            else
            { lcd_cmd(0xc0 + CharCount ); CURSOR_BLINK();CurrentChar = KeyChar; FnState = 1;}
         }
         break;
      } 
      case 1:
      {
         if((KeyChar == CurrentChar) && (BlinkCount < 50))
         {
            BlinkCount++;
            if(KeyFlag == TRUE)
            { 
               BlinkCount =0;         
               if((KeyChar >= '0') && (KeyChar <= '9'))        
               {
                  switch(PressCount)
                  {
                    case 0: StringBuf[CharCount] = KeyChar;lcd_data(KeyChar);CURSOR_LEFT(); PressCount++; break;
                    case 1: 
                         lcd_data(AalNumKey[KeyChar-0x30].char1);PressCount++;KeyFlag = 0;CURSOR_LEFT();
                         StringBuf[CharCount] = AalNumKey[KeyChar-0x30].char1; 
                      break;
                    case 2: 
                       if(AalNumKey[KeyChar-0x30].char2 == NULL)
                       {
                          StringBuf[CharCount] = KeyChar;lcd_data(KeyChar);CURSOR_LEFT();PressCount++;
                          break;
                       }
                       else
                       {  
                         lcd_data(AalNumKey[KeyChar-0x30].char2);
                         PressCount++;KeyFlag = 0;CURSOR_LEFT();
                         StringBuf[CharCount] = AalNumKey[KeyChar-0x30].char2;
                         break;
                       }
                    case 3:
                       if(AalNumKey[KeyChar-0x30].char3 == NULL)
                       {
                          StringBuf[CharCount] = KeyChar;lcd_data(KeyChar);CURSOR_LEFT(); PressCount++;
                          break;
                       }
                       else
                       {  
                          lcd_data(AalNumKey[KeyChar-0x30].char3);PressCount=0;KeyFlag = 0;CURSOR_LEFT();
                          StringBuf[CharCount] = AalNumKey[KeyChar-0x30].char3; 
                       } 
                       break;
                    default : break;
                 }
              }
              if(KeyChar == 'L')
              { if(CharCount >0) CharCount--;  CURSOR_LEFT();KeyFlag = 0;FnState = 0; }
              else if(KeyChar == 'R')
              { if(CharCount < 16) CharCount++;  CURSOR_RIGHT(); KeyFlag = 0;FnState = 0;}
              else if(KeyChar == 'E')
              {  CURSOR_OFF();
                 KeyFlag = 0; BlinkCount = 0; PressCount = 0; FnState = 0;CharCount =0;
              }
              KeyFlag = 0;           
           }                   
        } // end of if((KeyChar == CurrentChar) && (BlinkCount < 50))
        else
        {
           if(KeyChar != CurrentChar)
           {
              if(KeyChar == 'L')
              { 
                 if(CharCount >0) CharCount--;  KeyFlag = 0;CURSOR_LEFT();BlinkCount = 0; PressCount = 0; FnState = 0;
              }
              else
              {
                 if(CharCount <16) CharCount++; else CharCount = 0;
                 CURSOR_RIGHT();BlinkCount = 0; PressCount = 0; FnState = 0;
              }
            } 
            else if(BlinkCount >= 50)
            {  
               if(CharCount <16) CharCount++; else CharCount = 0;
               BlinkCount = 0;FnState = 0;PressCount = 0; CURSOR_RIGHT();
            }
         }
         break;
      } //end of case 1:
      default : break;
   }//end of  switch(FnState)
}

