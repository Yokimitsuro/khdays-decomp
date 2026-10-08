/* OS_GetOwnerInfo -- NitroSDK os_ownerInfo.c: copy the owner's profile out of the firmware's user
 * settings (NVRAMConfig at 0x027ffc80): the language (the low three bits of the option word at
 * +0x64), the favourite colour, the birthday, and the nickname and comment with their lengths,
 * each string terminated. */

#include "nitro/types.h"
#include "nitro/os_types.h"

extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);

typedef struct {
    unsigned char pad0[0x64];
    unsigned short bits : 3;
    unsigned short : 13;
} SrcA;

typedef struct {
    unsigned char pad0[2];
    unsigned char bits4 : 4;
    unsigned char : 4;
} SrcB;

void OS_GetOwnerInfo(OSOwnerInfo *info) {
    unsigned char *p = (unsigned char *)0x027ffc80;
    info->language = (unsigned char)((SrcA *)p)->bits;
    info->favoriteColor = ((SrcB *)p)->bits4;
    info->birthday.month = p[3];
    info->birthday.day = p[4];
    info->nickNameLength = (unsigned short)p[0x1a];
    info->commentLength = (unsigned short)p[0x50];
    MIi_CpuCopy16(p + 6, info->nickName, OS_OWNERINFO_NICKNAME_MAX * sizeof(u16));
    MIi_CpuCopy16(p + 0x1c, info->comment, OS_OWNERINFO_COMMENT_MAX * sizeof(u16));
    info->nickName[OS_OWNERINFO_NICKNAME_MAX] = 0;
    info->comment[OS_OWNERINFO_COMMENT_MAX] = 0;
}
