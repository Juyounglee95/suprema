#ifndef __UF_PACKET_H__
#define __UF_PACKET_H__

#include "UF_Def.h"

//
// Constants
//
#define UF_PACKET_START_CODE                0x40
#define UF_NETWORK_PACKET_START_CODE    0x41
#define UF_PACKET_END_CODE              0x0a
#define UF_PACKET_LEN                       13
#define UF_NETWORK_PACKET_LEN           15

#define UF_PACKET_COMMAND               0
#define UF_PACKET_TERMINAL_ID       1
#define UF_PACKET_PARAM             2
#define UF_PACKET_SIZE              3
#define UF_PACKET_FLAG              4
#define UF_PACKET_CHECKSUM          5

//
// Byte position of packet components
//
#define UF_PACKET_START_CODE_POS        0
#define UF_PACKET_COMMAND_POS       1
#define UF_PACKET_PARAM_POS         2
#define UF_PACKET_SIZE_POS          6
#define UF_PACKET_FLAG_POS          10
#define UF_PACKET_CHECKSUM_POS      11
#define UF_PACKET_END_CODE_POS      12

#define UF_NETWORK_PACKET_START_CODE_POS    0
#define UF_NETWORK_PACKET_TERMINALID_POS    1
#define UF_NETWORK_PACKET_COMMAND_POS       3
#define UF_NETWORK_PACKET_PARAM_POS         4
#define UF_NETWORK_PACKET_SIZE_POS          8
#define UF_NETWORK_PACKET_FLAG_POS          12
#define UF_NETWORK_PACKET_CHECKSUM_POS      13
#define UF_NETWORK_PACKET_END_CODE_POS      14

//
// Data packet
//
#define UF_DEFAULT_DATA_PACKET_SIZE     (4 * 1024)

void UF_MakePacket( BYTE command, UINT32 param, UINT32 size, BYTE flag, BYTE* packet );
UF_RET_CODE UF_SendPacket( BYTE command, UINT32 param, UINT32 size, BYTE flag, int timeout );
UINT32 UF_GetPacketValue( int component, BYTE* packet );
BYTE UF_CalculateChecksum( BYTE* packet, int size );
void UF_SetSendPacketCallback( void (*Callback)( BYTE* ) );
#endif
