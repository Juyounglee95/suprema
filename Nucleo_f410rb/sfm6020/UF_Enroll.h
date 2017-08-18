#ifndef __UF_ENROLL_H__
#define __UF_ENROLL_H__

#include "UF_Def.h"

typedef enum {
        UF_ENROLL_ONE_TIME              = 0x30,
        UF_ENROLL_TWO_TIMES1            = 0x31,
        UF_ENROLL_TWO_TIMES2            = 0x32,
        UF_ENROLL_TWO_TEMPLATES1        = 0x41,
        UF_ENROLL_TWO_TEMPLATES2        = 0x42,
} UF_ENROLL_MODE;

typedef enum {
        UF_ENROLL_NONE                  = 0x00,
        UF_ENROLL_ADD_NEW               = 0x71,
        UF_ENROLL_AUTO_ID               = 0x79,
        UF_ENROLL_CONTINUE              = 0x74,
        UF_ENROLL_CHECK_ID              = 0x70,
        UF_ENROLL_CHECK_FINGER          = 0x84,
        UF_ENROLL_CHECK_FINGER_AUTO_ID  = 0x85,
        UF_ENROLL_DURESS                = 0x92,
} UF_ENROLL_OPTION;

BOOL UF_EnrollMsgCallback( BYTE errCode );

#endif