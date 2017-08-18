/**
 *  	Packet API
 *
 *  	@author sjlee@suprema.co.kr
 *  	see
*/

#include "main.h"
#include "stm32f4xx_hal.h"
#include "UF_Def.h"
#include "UF_API.h"
#include "UF_Packet.h"
#include "UF_Error.h"

extern UART_HandleTypeDef huart1;

int g_ChannelType = UF_SERIAL_CHANNEL;

//
// Static variables
//
void (*s_SendPacketCallback)( BYTE* ) = NULL;
void (*s_ReceivePacketCallback)( BYTE* ) = NULL;
void (*s_SendDataPacketCallback)( int, int ) = NULL;
void (*s_ReceiveDataPacketCallback)( int, int ) = NULL;
void (*s_SendRawDataCallback)( int, int ) = NULL;
void (*s_ReceiveRawDataCallback)( int, int ) = NULL;

int s_DefaultPacketSize = UF_DEFAULT_DATA_PACKET_SIZE;

/**
 * 	Set callback
 */
void UF_SetSendPacketCallback( void (*Callback)( BYTE* ) )
{
	s_SendPacketCallback = Callback;
}

#if 0
int UF_WriteData( unsigned char* buf, int size, int timeout )
{
    if( g_ChannelType == UF_SERIAL_CHANNEL )
    {
        return UF_WriteSerial( buf, size, timeout );
    }
    else
    {
        return -1;
    }

}
#endif


/**
 *  Calculate checksum
 */
BYTE UF_CalculateChecksum( BYTE* packet, int size )
{
    int i;
    int checksum = 0;

    for( i = 0; i < size; i++ )
    {
        checksum += packet[i];
    }

    return checksum & 0xff;
}

/**
 *	Get a component of a packet
 */
UINT32 UF_GetPacketValue( int component, BYTE* packet )
{
    UINT32 value = 0;

    switch( component ) {
        case UF_PACKET_COMMAND:
            value = (UINT32)packet[UF_PACKET_COMMAND_POS];
            break;

        case UF_PACKET_PARAM:
            value = (UINT32)packet[UF_PACKET_PARAM_POS];
            value |= (UINT32)packet[UF_PACKET_PARAM_POS + 1] << 8;
            value |= (UINT32)packet[UF_PACKET_PARAM_POS + 2] << 16;
            value |= (UINT32)packet[UF_PACKET_PARAM_POS + 3] << 24;
            break;

        case UF_PACKET_SIZE:
            value = (UINT32)packet[UF_PACKET_SIZE_POS];
            value |= (UINT32)packet[UF_PACKET_SIZE_POS + 1] << 8;
            value |= (UINT32)packet[UF_PACKET_SIZE_POS + 2] << 16;
            value |= (UINT32)packet[UF_PACKET_SIZE_POS + 3] << 24;
            break;

        case UF_PACKET_FLAG:
            value = (UINT32)packet[UF_PACKET_FLAG_POS];
            break;

        case UF_PACKET_CHECKSUM:
            value = (UINT32)packet[UF_PACKET_CHECKSUM_POS];
            break;

        default:
            break;
    }

    return value;
}

/**
 *	Send a packet
 */
UF_RET_CODE UF_SendPacket( BYTE command, UINT32 param, UINT32 size, BYTE flag, int timeout )
{
    int writeLen;
    BYTE packet[UF_PACKET_LEN];

    UF_MakePacket( command, param, size, flag, packet );

    //writeLen = UF_WriteData( packet, UF_PACKET_LEN, timeout );
    
    HAL_UART_Transmit_IT(&huart1, packet, UF_PACKET_LEN);
    writeLen = huart1.TxXferCount;

    if( writeLen < 0 ) {
        return (g_ChannelType == UF_SERIAL_CHANNEL)? UF_ERR_CANNOT_WRITE_SERIAL : UF_ERR_CANNOT_WRITE_SOCKET;
    } else if( writeLen < UF_PACKET_LEN ) {
        return (g_ChannelType == UF_SERIAL_CHANNEL)? UF_ERR_WRITE_SERIAL_TIMEOUT : UF_ERR_WRITE_SOCKET_TIMEOUT;
    }

    if( s_SendPacketCallback ) {
        (*s_SendPacketCallback)( packet );
    }

    return UF_RET_SUCCESS;
}

/**
 *	Make a packet from components
 */
void UF_MakePacket( BYTE command, UINT32 param, UINT32 size, BYTE flag, BYTE* packet )
{
    packet[UF_PACKET_START_CODE_POS] = UF_PACKET_START_CODE;
    packet[UF_PACKET_COMMAND_POS] = command;
    packet[UF_PACKET_PARAM_POS] = (BYTE)param;
    packet[UF_PACKET_PARAM_POS + 1] = (BYTE)(param >> 8);
    packet[UF_PACKET_PARAM_POS + 2] = (BYTE)(param >> 16);
    packet[UF_PACKET_PARAM_POS + 3] = (BYTE)(param >> 24);
    packet[UF_PACKET_SIZE_POS] = (BYTE)size;
    packet[UF_PACKET_SIZE_POS + 1] = (BYTE)(size >> 8);
    packet[UF_PACKET_SIZE_POS + 2] = (BYTE)(size >> 16);
    packet[UF_PACKET_SIZE_POS + 3] = (BYTE)(size >> 24);
    packet[UF_PACKET_FLAG_POS] = flag;
    packet[UF_PACKET_CHECKSUM_POS] = UF_CalculateChecksum( packet, UF_PACKET_CHECKSUM_POS );
    packet[UF_PACKET_END_CODE_POS] = UF_PACKET_END_CODE;

    printf("\r[PACKET] ");
    for(int i=0; i<13; i++)
        printf("%02X ", packet[i]);
    printf("\r\n");
    return;
}
