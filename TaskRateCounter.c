#include <p24fxxxx.h>
#include "system.h"

//static unsigned char Count_Task1ms;
//static unsigned char Count_Task10ms;
static unsigned char Count_Task20ms;
static unsigned char Count_Task80ms;
static unsigned char Count_Task100ms;
static unsigned char Count_Task200ms;
//static unsigned char Count_Task500ms;
static unsigned char Count_Task1s;
static unsigned char Count_Task1min;


static unsigned char Flag_Task1ms;  
static unsigned char Flag_Task10ms;
static unsigned char Flag_Task20ms;
static unsigned char Flag_Task80ms;
static unsigned char Flag_Task100ms;
static unsigned char Flag_Task200ms;
static unsigned char Flag_Task500ms;
static unsigned char Flag_Task1s;
static unsigned char Flag_Task1min;



void TaskRateCount1ms(void)
{
   SetFlag_1msInt(0);
   Flag_Task1ms = TRUE;
}
void TaskRateCount10ms(void)
{
   SetFlag_10msInt(0);
   Flag_Task10ms = TRUE;
   Count_Task20ms++;
   Count_Task80ms++;
   Count_Task100ms++;
   Count_Task200ms++;
   if(Count_Task20ms == 2)
   {
      Count_Task20ms = 0;
      Flag_Task20ms = TRUE;
   }
   if(Count_Task80ms == 8)
   {
      Count_Task80ms = 0;
      Flag_Task80ms = TRUE;
   }
   if(Count_Task100ms == 10)
   {
      Count_Task100ms = 0;
      Flag_Task100ms = TRUE;
   }
   if(Count_Task200ms == 20)
   {
      Count_Task200ms = 0;
      Flag_Task200ms = TRUE;
   }
}
      
void TaskRateCount500ms(void)
{
   SetFlag_500msInt(0);
   Flag_Task500ms = TRUE;
   Count_Task1s++;
   Count_Task1min++;
   if(Count_Task1s == 2)
   {
      Count_Task1s = 0;
      Flag_Task1s = TRUE;
   }
   if(Count_Task1min == 120)
   {
      Count_Task1min = 0;
      Flag_Task1min = TRUE;
   }
}

unsigned char GetFlag_Task1ms(void)  
{
   return Flag_Task1ms;
}
unsigned char GetFlag_Task10ms(void)
{
   return Flag_Task10ms;
}
unsigned char GetFlag_Task20ms(void)
{
   return Flag_Task20ms;
}
unsigned char GetFlag_Task80ms(void)
{
   return Flag_Task80ms;
}
unsigned char GetFlag_Task100ms(void)
{
   return Flag_Task100ms;
}
unsigned char GetFlag_Task200ms(void)
{
   return Flag_Task200ms;
}
unsigned char GetFlag_Task500ms(void)
{
   return Flag_Task500ms;
}
unsigned char GetFlag_Task1s(void)
{
   return Flag_Task1s;
}
unsigned char GetFlag_Task1min(void)
{
   return Flag_Task1min;
}

void SetFlag_Task1ms(unsigned char value)  
{
   Flag_Task1ms = value;
}
void SetFlag_Task10ms(unsigned char value)
{
   Flag_Task10ms = value;
}
void SetFlag_Task20ms(unsigned char value)
{
   Flag_Task20ms = value;
}
void SetFlag_Task80ms(unsigned char value)
{
   Flag_Task80ms = value;
}
void SetFlag_Task100ms(unsigned char value)
{
   Flag_Task100ms = value;
}
void SetFlag_Task200ms(unsigned char value)
{
   Flag_Task200ms = value;
}
void SetFlag_Task500ms(unsigned char value)
{
   Flag_Task500ms = value;
}
void SetFlag_Task1s(unsigned char value)
{
   Flag_Task1s = value;
}
void SetFlag_Task1min(unsigned char value)
{
   Flag_Task1min = value;
}

