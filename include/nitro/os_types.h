/* OS types, with the NitroSDK's names. */
#ifndef NITRO_OS_TYPES_H
#define NITRO_OS_TYPES_H

#include "nitro/types.h"

/* What OS_DisableInterrupts returns and OS_RestoreInterrupts takes: the CPSR's IRQ-disable bit
 * as it was. An enum in the SDK; built with `-enum int`, the same as int. */
typedef int OSIntrMode;

/* The 64-bit tick count (OS_GetTick). */
typedef u64 OSTick;

/* The firmware's languages (OSOwnerInfo.language). */
#define OS_LANGUAGE_JAPANESE 0
#define OS_LANGUAGE_ENGLISH 1
#define OS_LANGUAGE_FRENCH 2
#define OS_LANGUAGE_GERMAN 3
#define OS_LANGUAGE_ITALIAN 4
#define OS_LANGUAGE_SPANISH 5

#define OS_OWNERINFO_NICKNAME_MAX 10
#define OS_OWNERINFO_COMMENT_MAX 26

typedef struct OSBirthday {
    u8 month;                                       /* 0x00 */
    u8 day;                                         /* 0x01 */
} OSBirthday;

/* The owner's profile from the firmware settings (OS_GetOwnerInfo). */
typedef struct OSOwnerInfo {
    u8 language;                                    /* 0x00: OS_LANGUAGE_* */
    u8 favoriteColor;                               /* 0x01 */
    OSBirthday birthday;                            /* 0x02 */
    u16 nickName[OS_OWNERINFO_NICKNAME_MAX + 1];    /* 0x04 */
    u16 nickNameLength;                             /* 0x1a */
    u16 comment[OS_OWNERINFO_COMMENT_MAX + 1];      /* 0x1c */
    u16 commentLength;                              /* 0x52 */
} OSOwnerInfo;                                      /* 0x54 */

#endif
