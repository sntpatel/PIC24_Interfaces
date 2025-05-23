/*****************************************************************************
 *
 * Popup 
 *
 *****************************************************************************
 * FileName:        Popup.c
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

 #define POPUPDISP_TIME 1

 #define STR_BATTERY_FAULT 1
 #define STR_MAINS_FAULT   2
 #define STR_HOOTER_FAULT   3


static unsigned char NewPopup;
static unsigned int PopupDispTimer;



struct PopupConfig
{
   PopupId_T PopupID;
   unsigned  char PopupStr;//need to change for string
   unsigned char Active;
};


struct PopupConfig PopupArray[NO_OF_POPUPS]=
{
   {BATTFLT_POPUP ,    STR_BATTERY_FAULT , FALSE},
   {ACFLT_POPUP ,      STR_MAINS_FAULT ,   FALSE},
   {HOOTERFLT_POPUP ,  STR_HOOTER_FAULT ,  FALSE}
};
struct Popup
{
   unsigned char Id;
   struct Popup * next;
};
struct Popup Tmp;
struct Popup *head;
struct Popup *temp;
struct Popup *p;
struct Popup *Popuplist;

void AddPopup(PopupId_T PopupID,struct Popup **q);
void DisplayPopup(struct Popup **p);
void DisplayString(unsigned  char no);
//************************************************************************************************

void InitPopup(void)
{
//struct Popup * temp;

 Tmp.Id =0;
temp = &Tmp ;
temp->next = NULL;
  head = temp;
}
void PopupHandler_Task(void)
{
   
   DisplayPopup(&head);
   
}


void AddPopup(PopupId_T PopupID,struct Popup **q)
{
   
    NewPopup = TRUE;
    {
      temp = (struct Popup *)&Tmp;
      temp->Id = PopupID;
      temp->next = *q;   
      *q = temp;
   }

}

void DisplayPopup(struct Popup **q)
{
   if(NewPopup)
   { 
      Popuplist = *q; 
      NewPopup = FALSE;  
   }

   if(Popuplist!= NULL)
   {
      if(PopupDispTimer < POPUPDISP_TIME)  
      {_LATA0 =1;
         DisplayString(PopupArray[Popuplist->Id].PopupStr);
         if((Popuplist->Id) == 2)
          _LATA2= 1;
         PopupDispTimer++;
      }
      else
      { _LATA0 =0;
         PopupDispTimer = 0;
         Popuplist = Popuplist->next;
      }
   }
   else
   { 
      Popuplist = temp; 
   }

}

void DisplayString(unsigned  char no)
{
  switch(no)
  {
  case 1: _LATA1 =1;break;
  case 2: _LATA0 =1;break;
  case 3: _LATA2 =1;break;
  }
}

void ActivatePopup(PopupId_T PopupID)
{
   PopupArray[PopupID].Active = TRUE;
  // AddPopup(PopupID,head);
}
void DeactivatePopup(PopupId_T PopupID)
{
   PopupArray[PopupID].Active = FALSE;
   //RemovePopup(PopupID);
}
/*
enum listoffults
{
ac_fail = 1 , acfailfaultUpdate
zone_open 2, zone1openfaultupdate
zone_short 3 , zone1shortFaultUpdate
hooter_fault 4
zone_isolate 5
}

//arrayofFaults[1] = 4, arrayofFaults[2] =1, arrayofFaults[3] =5

arrayofFaults[Maxnooffaults];
int NoofActiveFaults=0;


 if(NoofActiveFaults >0)
{
  if(i<NoofActiveFaults)
  {
    fautID = arrayofFaults[i] ;
    if(fautID)(DisptimeCounts < POPUP_TIME_CNT)
     { 
       Disptimecounts++;
       DisplayString(faultID);
     }
     else
     {
        Disptimecounts =0;
        i++;
     }
  }
    
  
}




if((zonefault)&& Zn1faultUpdate == 0)
 {
  NoofActiveFaults++;
  arrayofFaults[  NoofActiveFaults] = zonefault;
  Zn1faultUpdate = 1;
}
else if(zonfault ==0)
{
   for(i=0; i< NoofActivefaults; i++)
   {
      if(arrayofFaults[i] == zonefault)
       arrayofFaults[i] = 0; //removed
     
   }
}

if((Battault)&& BattfaultUpdate == 0)
 {
  NoofActiveFaults++;
  arrayofFaults[  NoofActiveFaults] = Battfault;
  BattfaultUpdate = 1;
}
else if(zonfault ==0)
{
   for(i=0; i< NoofActivefaults; i++)
   {
      if(arrayofFaults[i] == zonefault)
       arrayofFaults[i] = 0; //removed
     
   }
}

if((acfault)&& acfaultUpdate == 0)
 {
  NoofActiveFaults++;
  arrayofFaults[  NoofActiveFaults] = acfault;
  acfaultUpdate = 1;
}
else if(zonfault ==0)
{
   for(i=0; i< NoofActivefaults; i++)
   {
      if(arrayofFaults[i] == zonefault)
       arrayofFaults[i] = 0; //removed
     
   }
}

GetNoofActiveFaults();




*/