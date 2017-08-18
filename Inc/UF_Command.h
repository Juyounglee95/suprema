#ifndef __UF_COMMAND_H__
#define __UF_COMMAND_H__

//
// Command definitions
//
typedef enum {
        UF_COM_SR			= 0x03,
        UF_COM_ES			= 0x05,
        UF_COM_VS			= 0x08,
        UF_COM_IS			= 0x11,
        UF_COM_DA			= 0x17,
} UF_COMMAND;


int UF_CalculateTimeout( int dataSize );

#endif