#ifndef __UF_API_H__
#define __UF_API_H__

#include "UF_Def.h"
#include "UF_Error.h"
#include "UF_SysParameter.h"

typedef enum {
        UF_SINGLE_PROTOCOL      = 0,
        UF_NETWORK_PROTOCOL     = 1,
} UF_PROTOCOL;

typedef enum {
        UF_SERIAL_CHANNEL       = 0,
        UF_SOCKET_CHANNEL       = 1,
} UF_CHANNEL_TYPE;

UF_RET_CODE UF_SendPacket( BYTE command, UINT32 param, UINT32 size, BYTE flag, int timeout );

//
// System parameters
//
void UF_InitSysParameter(void);
UF_RET_CODE UF_GetSysParameter( UF_SYS_PARAM parameter, UINT32* value );
UF_RET_CODE UF_SetSysParameter( UF_SYS_PARAM parameter, UINT32 value );
UF_RET_CODE UF_GetMultiSysParameter( int parameterCount, UF_SYS_PARAM* parameters, UINT32* values );
UF_RET_CODE UF_SetMultiSysParameter( int parameterCount, UF_SYS_PARAM* parameters, UINT32* values );
UF_RET_CODE UF_Save();
UF_RET_CODE UF_SaveConfiguration( const char* filename, const char* description, int numOfComponent, UFConfigComponentHeader* componentHeader, void** componentData );
UF_RET_CODE UF_ReadConfigurationHeader( const char* filename, UFConfigFileHeader* header );
UF_RET_CODE UF_LoadConfiguration( const char* filename, int numOfComponent, UF_CONFIG_TYPE* type );
UF_RET_CODE UF_MakeParameterConfiguration( UFConfigComponentHeader* configHeader, BYTE* configData );

#endif
