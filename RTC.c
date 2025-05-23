/*****************************************************************************
 *
 * Real Time Clock Calender
 *
 *****************************************************************************
 * FileName:        rtcc.c
 * Dependencies:    
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLINK 03.20.01 or higher
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
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sanat Patel         26/10/2013
 *****************************************************************************/

#include "system.h"

/*****************************************************************************
 * Structures: _time and _time_chk
 *
 * Overview: These structures contain the time and date.
 * RTCCProcessEvents updates them. _time_chk is used as input/output for
 * get/set operations.
 *
 *****************************************************************************/
RTCC _time;
RTCC _time_chk;
/*****************************************************************************
 * Arrays: _time_str and _date_str
 *
 * Overview: These arrays contain the time and date strings. 
 * RTCCProcessEvents updates them.
 *
 *****************************************************************************/
char _time_str[16] = "                ";		// "Sat 10:01:15    "
char _date_str[16] = "                ";		// "Sep 30, 2005    "
char DateTimeStr[16] = "                ";		// 13/09/2016 19:10

// The flag stops updating time and date and used for get/set operations.
unsigned char _rtcc_flag;
/*****************************************************************************
 * Function: RTCCProcessEvents
 *
 * Preconditions: RTCCInit must be called before.
 *
 * Overview: The function grabs the current time from the RTCC and translate
 * it into strings.
 *
 * Input: None.
 *
 * Output: It update time and date strings  _time_str, _date_str,
 * and _time, _time_chk structures.
 *
 *****************************************************************************/
void RTCCProcessEvents(void)
{
	// Process time object only if time is not being set
	while (!_rtcc_flag) {
		// Grab the time
		_RTCPTR = 0;			
		_time.prt00 = RTCVAL;
		_RTCPTR = 1;			
		_time.prt01 = RTCVAL;
		_RTCPTR = 2;			
		_time.prt10 = RTCVAL;
		_RTCPTR = 3;			
		_time.prt11 = RTCVAL;

		// Grab the time again 
		_RTCPTR = 0;			
		_time_chk.prt00 = RTCVAL;
		_RTCPTR = 1;			
		_time_chk.prt01 = RTCVAL;
		_RTCPTR = 2;			
		_time_chk.prt10 = RTCVAL;
		_RTCPTR = 3;			
		_time_chk.prt11 = RTCVAL;

		// Verify there is no roll-over
		if ((_time.prt00 == _time_chk.prt00) &&
			(_time.prt01 == _time_chk.prt01) &&
			(_time.prt10 == _time_chk.prt10) &&
			(_time.prt11 == _time_chk.prt11))
		{
			switch (_time.mth) {
				default:
				case 0x01: _date_str[0] = 'J'; _date_str[1] = 'a'; _date_str[2] = 'n'; break; 
				case 0x02: _date_str[0] = 'F'; _date_str[1] = 'e'; _date_str[2] = 'b'; break; 
				case 0x03: _date_str[0] = 'M'; _date_str[1] = 'a'; _date_str[2] = 'r'; break; 
				case 0x04: _date_str[0] = 'A'; _date_str[1] = 'p'; _date_str[2] = 'r'; break; 
				case 0x05: _date_str[0] = 'M'; _date_str[1] = 'a'; _date_str[2] = 'y'; break; 
				case 0x06: _date_str[0] = 'J'; _date_str[1] = 'u'; _date_str[2] = 'n'; break; 
				case 0x07: _date_str[0] = 'J'; _date_str[1] = 'u'; _date_str[2] = 'l'; break; 
				case 0x08: _date_str[0] = 'A'; _date_str[1] = 'u'; _date_str[2] = 'g'; break; 
				case 0x09: _date_str[0] = 'S'; _date_str[1] = 'e'; _date_str[2] = 'p'; break; 
				case 0x10: _date_str[0] = 'O'; _date_str[1] = 'c'; _date_str[2] = 't'; break; 
				case 0x11: _date_str[0] = 'N'; _date_str[1] = 'o'; _date_str[2] = 'v'; break; 
				case 0x12: _date_str[0] = 'D'; _date_str[1] = 'e'; _date_str[2] = 'c'; break; 
			}

			_date_str[3] = ' ';
			_date_str[6] = ',';
			_date_str[7] = ' ';
			_date_str[8] = '2';
			_date_str[9] = '0';

			_date_str[4] = (_time.day >> 4) + '0';
			_date_str[5] = (_time.day & 0xF) + '0';

			_date_str[10] = (_time.yr >> 4) + '0';
			_date_str[11] = (_time.yr & 0xF) + '0';

			switch (_time.wkd) {
				default:
				case 0x00: _time_str[0] = 'S'; _time_str[1] = 'u'; _time_str[2] = 'n'; break; 
				case 0x01: _time_str[0] = 'M'; _time_str[1] = 'o'; _time_str[2] = 'n'; break; 
				case 0x02: _time_str[0] = 'T'; _time_str[1] = 'u'; _time_str[2] = 'e'; break; 
				case 0x03: _time_str[0] = 'W'; _time_str[1] = 'e'; _time_str[2] = 'd'; break; 
				case 0x04: _time_str[0] = 'T'; _time_str[1] = 'h'; _time_str[2] = 'u'; break; 
				case 0x05: _time_str[0] = 'F'; _time_str[1] = 'r'; _time_str[2] = 'i'; break; 
				case 0x06: _time_str[0] = 'S'; _time_str[1] = 'a'; _time_str[2] = 't'; break;  
			}
			
			_time_str[3] = ' ';
			_time_str[6] = ':';
			_time_str[9] = ':';

			_time_str[4] = (_time.hr >> 4) + '0';
			_time_str[5] = (_time.hr & 0xF) + '0';

			_time_str[7] = (_time.min >> 4) + '0';
			_time_str[8] = (_time.min & 0xF) + '0';

			_time_str[10] = (_time.sec >> 4) + '0';
			_time_str[11] = (_time.sec & 0xF) + '0';

			break;
		}	
	}
    DateTimeStr[0] = (_time.day >> 4) + '0';
    DateTimeStr[1] = (_time.day & 0xF) + '0';
    DateTimeStr[2] = '/';
    DateTimeStr[3] = (_time.mth >> 4) + '0';
    DateTimeStr[4] = (_time.mth & 0xF) + '0';
    DateTimeStr[5] = '/';
    DateTimeStr[6] = '2';
    DateTimeStr[7] = '0';
    DateTimeStr[8] = (_time.yr >> 4) + '0';
    DateTimeStr[9] = (_time.yr & 0xF) + '0';
    DateTimeStr[10] = ' ';
    DateTimeStr[11] = (_time.hr >> 4) + '0';
    DateTimeStr[12] = (_time.hr & 0xF) + '0';
    DateTimeStr[13] = ':';
    DateTimeStr[14] = (_time.min >> 4) + '0';
    DateTimeStr[15] = (_time.min & 0xF) + '0';


  // LINE1();LCD_PrintString(_time_str); //Thu 19:26:27
  // LINE2();LCD_PrintString(_date_str); //Sep 01, 2016
  // LINE1();LCD_PrintString(DateTimeStr); //13/09/2016 19:07
}

//void GetRTC(char * RTCdata)
//{
//   RTCdata = &DateTimeStr;
//}

/*****************************************************************************
 * Function: RTCCInit
 *
 * Preconditions: RTCCInit must be called before.
 *
 * Overview: Enable the oscillator for the RTCC
 *
 * Input: None.
 *
 * Output: None.
 *****************************************************************************/
void RTCCInit(void)
{
    char day;
    char month;
    char year;
    char hour;
    char min;
    char sec;
    int dayOfWeek;

    // Enables the SOSC for RTCC operation
	asm("mov #OSCCON,W1");
	asm("mov.b	#0x02, W0");
	asm("mov.b	#0x46, W2");
	asm("mov.b	#0x57, W3");
	asm("mov.b	W2, [W1]");
	asm("mov.b	W3, [W1]");
	asm("mov.b	W0, [W1]");		

    // Unlock sequence must take place for RTCEN to be written
	_RCFGCAL	= 0x0000;			
    mRTCCUnlock();
    _RTCEN = 1;
	mRTCCOn();

     //System Hexfile  Time
    sec =  (((__TIME__[6])&0x0F)<<4) | ((__TIME__[7])&0x0F);
    min =  (((__TIME__[3])&0x0F)<<4) | ((__TIME__[4])&0x0F);
    hour = (((__TIME__[0])&0x0F)<<4) | ((__TIME__[1])&0x0F);
    day =  (((__DATE__[4])&0x0F)<<4) | ((__DATE__[5])&0x0F);
    year = (((__DATE__[9])&0x0F)<<4) | ((__DATE__[10])&0x0F);
   

/**************************/
// Char  Month     BCD
//----------------------
// Ja =  JANUARY = 0x01
// F   = FEB     = 0x02
// Mr  = MAR     = 0x03
// Ap  = APR     = 0x04
// My  = MAY     = 0x05
// Jun = JUNE    = 0x06
// Jul = JULU    = 0x07
// Au  = AUG     = 0x08
// S   = SEP     = 0x09
// O   = OCT     = 0x10
// N   = NOV     = 0x11
// D   = DEC     = 0x12
/**************************/
    //Set the month
    switch(__DATE__[0])
    {
        case 'J':
            //January, June, or July
            switch(__DATE__[1])
            {
                case 'a':
                    //January
        	        month = 0x01;
                    break;
                case 'u':
                    switch(__DATE__[2])
                    {
                        case 'n':
                            //June
        	                month = 0x06;
                            break;
                        case 'l':
                            //July
                            month = 0x07;
                            break;
                    }
                    break;
            }
            break;
        case 'F':
        	month = 0x02;
            break;
        case 'M':
            //March,May
            switch(__DATE__[2])
            {
                case 'r':
                    //March
        	        month = 0x03;
                    break;
                case 'y':
                    //May
        	        month = 0x05;
                    break;
            }
            break;
        case 'A':
            //April, August
            switch(__DATE__[1])
            {
                case 'p':
                    //April
        	        month = 0x04;
                    break;
                case 'u':
                    //August
        	        month = 0x08;
                    break;
            }
            break;
        case 'S':
        	month = 0x09;
            break;
        case 'O':
        	month = 0x10;
            break;
        case 'N':
        	month = 0x11;
            break;
        case 'D':
        	month = 0x12;
            break;
    }
  
    
	mRTCCSetSec(sec);
	mRTCCSetMin(min);
	mRTCCSetHour(hour);
	mRTCCSetDay(day);
    mRTCCSetMonth(month);
	mRTCCSetYear( year );

    dayOfWeek = 6;
    dayOfWeek += ((year>>4)*10)+(year&0x0F);
    dayOfWeek += ((year>>4)*10)+(year&0x0F)/4;
    switch(month)
    {
        case 0x01:  //January
            //fall through
        case 0x10:  //October
            //add nothing
            break;

        case 0x02:  //February
        case 0x03:  //March
        case 0x11:  //November
            dayOfWeek += 3;
            break;

        case 0x04:  //April
        case 0x07:  //July
            dayOfWeek += 6;
            break;

        case 0x05:  //May
            dayOfWeek += 1;
            break;

        case 0x06:  //June
            dayOfWeek += 4;
            break;

        case 0x08:  //August
            dayOfWeek += 2;
            break;

        case 0x09:  //September
            //fall through
        case 0x12:  //December
            dayOfWeek += 5;
            break;
    }
    dayOfWeek += ((day>>4)*10)+(day&0x0F);
    dayOfWeek = dayOfWeek%7;

	mRTCCSetWkDay(dayOfWeek);

	mRTCCSet();
}

/*****************************************************************************
 * Function: RTCCSet
 *
 * Preconditions: None.
 *
 * Overview: The function upload time and date from _time_chk into clock.
 *
 * Input: _time_chk - structure containing time and date.
 *
 * Output: None.
 *
 *****************************************************************************/
void RTCCSet(void)
{
	mRTCCUnlock();			// Unlock the RTCC
	// Set the time
	_RTCPTR = 0;			
	RTCVAL = _time_chk.prt00;
	_RTCPTR = 1;			
	RTCVAL = _time_chk.prt01;
	_RTCPTR = 2;			
	RTCVAL = _time_chk.prt10;
	_RTCPTR = 3;			
	RTCVAL = _time_chk.prt11;
	mRTCCLock();			// Lock the RTCC
	_rtcc_flag = 0;			// Release the lock on the time
}

/*****************************************************************************
 * Function: RTCCUnlock
 *
 * Preconditions: None.
 *
 * Overview: The function allows a writing into the clock registers.
 *
 * Input: None.
 *
 * Output: None.
 *
 *****************************************************************************/
void RTCCUnlock(void){
#if defined(__PIC24F32KA304__) && (__C30_VERSION__ <= 325)		//workaround for naming issue in C30 v3.25
	asm volatile("disi	#5");
	asm volatile("mov	#0x55, w7");
	asm volatile("mov	w7, _NVMKEY");
	asm volatile("mov	#0xAA, w8");
	asm volatile("mov	w8, _NVMKEY");
//	asm volatile("bset	_NVMCON, #15");
    asm volatile("bset	_RCFGCAL1, #13");
	asm volatile("nop");
	asm volatile("nop");
#else
	asm volatile("disi	#5");
	asm volatile("mov	#0x55, w7");
	asm volatile("mov	w7, _NVMKEY");
	asm volatile("mov	#0xAA, w8");
	asm volatile("mov	w8, _NVMKEY");
//	asm volatile("bset	_NVMCON, #15");
    asm volatile("bset	_RCFGCAL, #13");
	asm volatile("nop");
	asm volatile("nop");
#endif

//	EECON2 = 0x55; 
//	EECON2 = 0xAA; 
//	RCFGCALbits.RTCWREN = 1;
}

/*****************************************************************************
 * Function: RTCCSetBinSec
 *
 * Preconditions: None.
 *
 * Overview: The function verifies setting seconds range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Seconds binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinSec(unsigned char Sec){
    if(Sec == 0xff)  Sec = 59;
    if(Sec == 60)  Sec = 0;
    mRTCCSetSec(mRTCCBin2Dec(Sec));
}

/*****************************************************************************
 * Function: RTCCSetBinMin
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting minutes range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Minutes binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinMin(unsigned char Min){
    if(Min == 0xff)   Min = 59;
    if(Min == 60)  Min = 0;
    mRTCCSetMin(mRTCCBin2Dec(Min));
}

/*****************************************************************************
 * Function: RTCCSetBinHour
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting hours range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Hours binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinHour(unsigned char Hour){
    if(Hour == 0xff)  Hour = 23;
    if(Hour == 24) Hour = 0;
    mRTCCSetHour(mRTCCBin2Dec(Hour));
}

/*****************************************************************************
 * Function: RTCCCalculateWeekDay
 *
 * Preconditions: Valid values of day, month and year must be presented in 
 * _time_chk structure.
 *
 * Overview: The function reads day, month and year from _time_chk and 
 * calculates week day. Than It writes result into _time_chk. To write
 * the structure into clock RTCCSet must be called.
 *
 * Input: _time_chk with valid values of day, month and year.
 *
 * Output: Zero based week day in _time_chk structure.
 *
 *****************************************************************************/
void RTCCCalculateWeekDay(){
const char MonthOffset[] =
//jan feb mar apr may jun jul aug sep oct nov dec
{   0,  3,  3,  6,  1,  4,  6,  2,  5,  0,  3,  5 };
unsigned Year;
unsigned Month;
unsigned Day;
unsigned Offset;
    // calculate week day 
    Year  = mRTCCGetBinYear();
    Month = mRTCCGetBinMonth();
    Day  = mRTCCGetBinDay();
    
    // 2000s century offset = 6 +
    // every year 365%7 = 1 day shift +
    // every leap year adds 1 day
    Offset = 6 + Year + Year/4;
    // Add month offset from table
    Offset += MonthOffset[Month-1];
    // Add day
    Offset += Day;

    // If it's a leap year and before March there's no additional day yet
    if((Year%4) == 0)
        if(Month < 3)
            Offset -= 1;
    
    // Week day is
    Offset %= 7;

    mRTCCSetWkDay(Offset);
}

/*****************************************************************************
 * Function: RTCCSetBinDay
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting day range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Day binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinDay(unsigned char Day){
const char MonthDaymax[] =
//jan feb mar apr may jun jul aug sep oct nov dec
{  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
unsigned Daymax;
unsigned Month;
unsigned Year;

    Month = mRTCCGetBinMonth();
    Year = mRTCCGetBinYear();

    Daymax = MonthDaymax[Month-1];

    // February has one day more for a leap year
    if(Month == 2)
    if( (Year%4) == 0)
        Daymax++;

    if(Day == 0) Day = Daymax;
    if(Day > Daymax) Day = 1;
    mRTCCSetDay(mRTCCBin2Dec(Day));
}

/*****************************************************************************
 * Function: RTCCSetBinMonth
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting month range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Month binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinMonth(unsigned char Month){
    if(Month < 1) Month = 12;
    if(Month > 12) Month = 1;
    mRTCCSetMonth(mRTCCBin2Dec(Month));
}

/*****************************************************************************
 * Function: RTCCSetBinYear
 *
 * Preconditions: None.
 *
 * Overview: The function verifies a setting year range, translates it into
 * BCD format and writes into _time_chk structure. To write the structure into
 * clock RTCCSet must be called.
 *
 * Input: Year binary value.
 *
 * Output: Checked BCD value in _time_chk structure.
 *
 *****************************************************************************/
void RTCCSetBinYear(unsigned char Year){
   if(Year == 0xff) Year = 99;
   if(Year == 100)  Year = 0;
    mRTCCSetYear(mRTCCBin2Dec(Year));
    // Recheck day. Leap year influences to Feb 28/29.
    RTCCSetBinDay(mRTCCGetBinDay());
}

/*****************************************************************************
 * EOF
 *****************************************************************************/
