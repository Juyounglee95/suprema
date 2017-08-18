#ifndef __UF_DEF_H__
#define __UF_DEF_H__

#include <stdint.h>
#include <stdbool.h>

#ifndef BYTE
typedef unsigned char BYTE ;
#endif

#ifndef UINT32
typedef uint32_t UINT32 ;
#endif

#ifndef USHORT
typedef unsigned short USHORT;
#endif

#ifndef BOOL
typedef _Bool BOOL;
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 1
#endif

typedef void *PVOID;
typedef PVOID HANDLE;


#ifndef DWORD
typedef unsigned long   DWORD;
#endif

#define UFL_SERIAL_SLEEP 1000 // (msec)
#define UFL_RX_SLEEP 1000
#define UFL_TX_SLEEP 1000

#endif
