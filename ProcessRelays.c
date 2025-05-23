/*****************************************************************************
 *
 * RELAYS 
 *
 *****************************************************************************
 * FileName:        ProcessRelays.c
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
 * Sanat Patel			14/12/03	...	
 * 
 *****************************************************************************/
#include "system.h"
#define ON  1
#define OFF 0


struct RelayFlag Relay[13];

//global Definition

void RelayOn(unsigned char RlyNo);
void RelayOff(unsigned char RlyNo);
//Locals
/*********************************************************************
 * Function:       InitRelay
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Used to initialize relay states or to OFF all relays 
 *
 ********************************************************************/
void InitRelay(void)
{
   unsigned int rlyno;

   for(rlyno = 1; rlyno < TOTAL_RELAYS; rlyno++ )
   {
      RelayOff(rlyno);
   }
}

/*********************************************************************
 * Function:       ProcessRelay_Task
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Used when 
 *
 ********************************************************************/
void ProcessRelay_Task(void)
{
   unsigned int rlyno;

   for(rlyno = 1; rlyno < TOTAL_RELAYS; rlyno++ )
   {
      if((Relay[rlyno].ON_State == FALSE)&& (Relay[rlyno].ON_Flag == TRUE))
      {
         RelayOn(rlyno);
      }
      else if((Relay[rlyno].ON_State == TRUE)&& (Relay[rlyno].ON_Flag == FALSE))
      {
         RelayOff(rlyno);
      }
      else
      {
          ;//Do nothing
      }
   }
}
/*********************************************************************
 * Function:        RelayOn   
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Used to Switch ON perticular relay 
 *
 ********************************************************************/

void RelayOn(unsigned char RlyNo)
{
   switch(RlyNo)
   {
      case Z1: RLY_Z1 = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case Z2: RLY_Z2 = ON ; Relay[RlyNo].ON_State = TRUE; break;   
      case Z3: RLY_Z3 = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case Z4: RLY_Z4 = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case Z5: RLY_Z5 = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case Z6: RLY_Z6 = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case Z7: RLY_Z7 = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case Z8: RLY_Z8 = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case COMM_HOOTER:RLY_COMM_HOOTER = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case COMM_FIRE:  RLY_COMM_FIRE   = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case COMM_FAULT: RLY_COMM_FAULT  = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case ZONE_RESET: RLY_ZONE_RESET  = ON ; Relay[RlyNo].ON_State = TRUE; break;
      case BATT_CHECK: RLY_BATT_CHECK  = ON ; Relay[RlyNo].ON_State = TRUE; break;
      default: break;
   }
}
/*********************************************************************
 * Function:       RelayOff
 *
 * PreCondition:    None.
 *
 * Input:       	None.	
 *                  
 * Output:      	None.
 *
 * Overview:        Used to Switch OFF perticular Relay 
 *
 ********************************************************************/
void RelayOff(unsigned char RlyNo)
{
   switch(RlyNo)
   {
      case Z1: RLY_Z1 = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case Z2: RLY_Z2 = OFF ; Relay[RlyNo].ON_State = FALSE; break;   
      case Z3: RLY_Z3 = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case Z4: RLY_Z4 = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case Z5: RLY_Z5 = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case Z6: RLY_Z6 = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case Z7: RLY_Z7 = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case Z8: RLY_Z8 = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case COMM_HOOTER:RLY_COMM_HOOTER = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case COMM_FIRE:  RLY_COMM_FIRE   = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case COMM_FAULT: RLY_COMM_FAULT  = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case ZONE_RESET: RLY_ZONE_RESET  = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      case BATT_CHECK: RLY_BATT_CHECK  = OFF ; Relay[RlyNo].ON_State = FALSE; break;
      default: break;
   }
}

