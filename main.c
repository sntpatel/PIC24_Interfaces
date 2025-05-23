#include <p24fxxxx.h>
#include "system.h"
#include "Buzzer.h"
#include "ProcessADC.h"
#include "SystemProcess.h"
//---------------------------------------------------
/*#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3
void ConvertADCVoltage ( unsigned int adc_conv_data );
typedef struct
{  
  
    volatile unsigned char adones ;
    volatile unsigned char adtens ;
    volatile unsigned char adhunds ;
    volatile unsigned char adthous ;
    volatile unsigned int  temp1 ;

} APP_DATA ;

static APP_DATA adcData ;

static unsigned char char1,char2,char3,char4;
static unsigned int AdcValue = 0;
*/
//---------------------------------------------------
extern void Keypad_Init(void);
extern void Init_Menu(void);
extern void SystemInitialise(void);
extern void LCD_init(void);
extern void ClearPSWDExpired(void);
extern void IO_DirectionSet(void);
extern void SWDelayms(unsigned int cnt);
//unsigned char txData, rxData; 

int main(void)
{
 //IO_DirectionSet();//
 /*  InitRelay(); //Initalize Relay
   BuzzerOFF();
 */
  SPI2INTInit();   // Setup SPI to communicate to EEPROM  
   EEPROMInit();    // Setup EEPROM 
#ifdef SYSTEM_TIME_SET
   RTCCInit();  // Setup the RTCC
#endif

   TimerInit();
   Timer2Init();
   Timer3Init();
   Timer4Init();
 
TRISAbits.TRISA0 = 0;
TRISAbits.TRISA1 = 0;
TRISAbits.TRISA2 = 0;
   _LATA0 = 0;_LATA1 = 0;_LATA2 = 0;
InitPopup();
ActivatePopup(ACFLT_POPUP);
ActivatePopup(HOOTERFLT_POPUP);
TRISGbits.TRISG2 = 0;
_LATG2 = 0;   
LCD_init();
Keypad_Init();

Init_Menu();
SystemInitialise();
//EEPROMWriteByte('P', 32769);
//if( EEPROMReadByte(32769) == 'Q')
    SetNoofBeep(3);
AlphaNumKeypad_Init();
//ZoneLocationDefaultSet();
/*EEPROMWriteByte('4', ADDR_PSWD);
EEPROMWriteByte('5', ADDR_PSWD+1);
EEPROMWriteByte('6', ADDR_PSWD+2);
EEPROMWriteByte('7', ADDR_PSWD+3);
*/
//PSWDExpired =TRUE;
 //_TRISB0 = 1; //ZONE 1 
//_TRISB1 = 1; //ZONE 2 
TRISBbits.TRISB0 = 1;
TRISBbits.TRISB1 = 1;
TRISBbits.TRISB2 = 1;
TRISBbits.TRISB9 = 1;
TRISBbits.TRISB11 = 1;
ClearPSWDExpired();

//_TRISB11 = 1; // AC Fault
  _TRISA7  = 0;// AC fault LEd
_TRISA6  = 0;//batt fault LEd
_TRISF0  = 0;// system ON LEd
ACFLT_LED = 1;
BATTFLT_LED = 1;
SYSTEMON_LED = 1;
ADC_ChannelEnable ( ADC_CHANNEL_ZONE1 ) ;
//ADC_ChannelEnable ( ADC_CHANNEL_ZONE2 ) ;
//ADC_ChannelEnable ( ADC_CHANNEL_ZONE3 ) ;
/*ADC_ChannelEnable ( ADC_CHANNEL_ZONE4 ) ;
ADC_ChannelEnable ( ADC_CHANNEL_ZONE5 ) ;
ADC_ChannelEnable ( ADC_CHANNEL_ZONE6 ) ;
ADC_ChannelEnable ( ADC_CHANNEL_ZONE7 ) ;
ADC_ChannelEnable ( ADC_CHANNEL_ZONE8 ) ;
ADC_ChannelEnable ( ADC_CHANNEL_HOOTER_1 ) ;
*/
ADC_ChannelEnable ( ADC_CHANNEL_BATTERY ) ;
ADC_ChannelEnable ( ADC_CHANNEL_11);
ADCInit();


   while(1)
   {

  LCD_CLEAR();
      //  ADC debug--------------------------
   /*      AdcValue =ADC_Read10bit(0);//ADC_CHANNEL_ZONE1);
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
*/
     TaskScheduler();  

   }

 return 0;  
}

