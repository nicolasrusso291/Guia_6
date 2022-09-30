//=====[#include guards - begin]===============================================

#ifndef _PC_SERIAL_COM_H_
#define _PC_SERIAL_COM_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    PC_SERIAL_COMMANDS,
    PC_SERIAL_GET_CODE,
    PC_SERIAL_SAVE_NEW_CODE,
} pcSerialComMode_t;

//=====[Declarations (prototypes) of public functions]=========================

static pcSerialComMode_t pcSerialComMode = PC_SERIAL_COMMANDS;

void pcSerialComInit();
char pcSerialComCharRead();
void pcSerialComStringWrite( const char* str );
void pcSerialComUpdate();
bool pcSerialComCodeCompleteRead();
void pcSerialComCodeCompleteWrite( bool state );

//=====[#include guards - end]=================================================

#endif // _PC_SERIAL_COM_H_