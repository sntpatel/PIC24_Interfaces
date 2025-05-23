/************************************************************************
*                                                                       *
*  Basic access to SPI EEPROM 25LC256.                                  *
*  Modified for PIC24FJ64GA004 family with PPS.
*                                                                       *
*************************************************************************
* Company:             EMBETRON.                                        *
*                                                                       *
* Software License Agreement                                            *
*                                                                       *
* The software supplied herewith by EMBETRON                            *
* (the "Company") for its PICmicro� Microcontroller is intended and     *
* supplied to you, the Company's customer, for use solely and           *
* exclusively on Microchip PICmicro Microcontroller products. The       *
* software is owned by the Company and/or its supplier, and is          *
* protected under applicable copyright laws. All rights are reserved.   *
* Any use in violation of the foregoing restrictions may subject the    *
* user to criminal sanctions under applicable laws, as well as to       *
* civil liability for the breach of the terms and conditions of this    *
* license.                                                              *
*                                                                       *
* THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,     *
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED     *
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A           *
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,     *
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR            *
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.                     *
*                                                                       *
* Author            Date            Comment                             *
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
* Sanat Patel       Oct 26, 2013    ....                                *
************************************************************************/
#ifndef EEPROM_H
#define EEPROM_H

//#include "iomapping.h"
// peripheral configurations
#define SPI_MASTER  0x0120	// select 8-bit master mode, CKE=1, CKP=0
#define SPI_ENABLE	0x8000	// enable SPI port, clear status
/************************************************************************
* EEPROM Commands                                                       *
*                                                                       *    
************************************************************************/
#define EEPROM_PAGE_SIZE    (unsigned)64
#define EEPROM_PAGE_MASK    (unsigned)0x003f
#define EEPROM_CMD_READ     (unsigned)0b00000011
#define EEPROM_CMD_WRITE    (unsigned)0b00000010
#define EEPROM_CMD_WRDI     (unsigned)0b00000100
#define EEPROM_CMD_WREN     (unsigned)0b00000110
#define EEPROM_CMD_RDSR     (unsigned)0b00000101
#define EEPROM_CMD_WRSR     (unsigned)0b00000001

/************************************************************************
* Aliases for IOs registers related to SPI connected to EEPROM          *
*                                                                       *    
************************************************************************/

//otherwise default to the original values
#define EEPROM_SS_TRIS      TRISGbits.TRISG9
#define EEPROM_SS_PORT      PORTGbits.RG9     //EEPROM CS
#define EEPROM_SCK_TRIS     TRISGbits.TRISG6
#define EEPROM_SDO_TRIS     TRISGbits.TRISG8
#define EEPROM_SDI_TRIS     TRISGbits.TRISG7

/************************************************************************
* Structure STATREG and union _EEPROMStatus_                            *
*                                                                       *
* Overview: Provide a bits and byte access to EEPROM status value.      *
*                                                                       *
************************************************************************/
struct  STATREG{
char    WIP:1;
char    WEL:1;
char    BP0:1;
char    BP1:1;
char    RESERVED:3;
char    WPEN:1;
};

union _EEPROMStatus_{
struct  STATREG Bits;
char    Char;
};

/************************************************************************
* Macro: Lo                                                             *
*                                                                       *
* Preconditions: None                                                   *
*                                                                       *
* Overview: This macro extracts a low byte from a 2 byte word.          *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
#define Lo(X)   (unsigned char)(X&0x00ff)

/************************************************************************
* Macro: Hi                                                             *
*                                                                       *
* Preconditions: None                                                   *
*                                                                       *
* Overview: This macro extracts a high byte from a 2 byte word.         *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
#define Hi(X)   (unsigned char)((X>>8)&0x00ff)

/************************************************************************
* Macro: mEEPROMSSLow                                                   *
*                                                                       *
* Preconditions: SS IO must be configured as output.                    *
*                                                                       *
* Overview: This macro pulls down SS line                               *
*           to start a new EEPROM operation.                            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
#define mEEPROMSSLow()      EEPROM_SS_PORT=0;

/************************************************************************
* Macro: mEEPROMSSHigh                                                  *
*                                                                       *
* Preconditions: SS IO must be configured as output.                    *
*                                                                       *
* Overview: This macro set SS line to high level                        *
*           to start a new EEPROM operation.                            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
#define mEEPROMSSHigh()     EEPROM_SS_PORT=1;

/************************************************************************
* Function: EEPROMInit                                                  *
*                                                                       *
* Preconditions: SPI module must be configured to operate with          *
*                 parameters: Master, MODE16 = 0, CKP = 1, SMP = 1.     *
*                                                                       *
* Overview: This function setup SPI IOs connected to EEPROM.            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
extern void EEPROMInit();

/************************************************************************
* Function: EEPROMReadStatus()                                          *
*                                                                       *
* Preconditions: SPI module must be configured to operate with  EEPROM. *
*                                                                       *
* Overview: This function reads status register from EEPROM.            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: Status register value.                                        *
*                                                                       *
************************************************************************/
extern union _EEPROMStatus_ EEPROMReadStatus();

/************************************************************************
* Function: EEPROMWriteByte()                                           *
*                                                                       *
* Preconditions: SPI module must be configured to operate with  EEPROM. *
*                                                                       *
* Overview: This function writes a new value to address specified.      *
*                                                                       *
* Input: Data to be written and address.                                *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
extern void EEPROMWriteByte(unsigned Data, unsigned Address);

/************************************************************************
* Function: EEPROMReadByte()                                            *
*                                                                       *
* Preconditions: SPI module must be configured to operate with  EEPROM. *
*                                                                       *
* Overview: This function reads a value from address specified.         *
*                                                                       *
* Input: Address.                                                       *
*                                                                       *
* Output: Data read.                                                    *
*                                                                       *
************************************************************************/
extern unsigned EEPROMReadByte(unsigned Address);

/************************************************************************
* Function: EEPROMWriteEnable()                                         *
*                                                                       *
* Preconditions: SPI module must be configured to operate with EEPROM.  *
*                                                                       *
* Overview: This function allows a writing into EEPROM. Must be called  *
* before every writing command.                                         *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
extern void EEPROMWriteEnable();

/************************************************************************
* EOF                                                                   *
************************************************************************/
#endif
