typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000




void SND_LockChannel(u32 chBitMask, u32 flags);

/* khdays: shared-bss */
u32 sAlarmLock = 0;   /* sAlarmLock */
u32 data_0204a2fc = 0;   /* sCaptureLock */
u32 sChannelLock = 0;   /* sChannelLock */

/* func_02019cb8 -- NitroSystem resource_mgr.c: NNS_SndLockChannel. */
BOOL func_02019cb8 (u32 chBitFlag)
{
    if (chBitFlag == 0) return TRUE;
    if (chBitFlag & sChannelLock) return FALSE;

    SND_LockChannel(chBitFlag, 0);

    sChannelLock |= chBitFlag;

    return TRUE;
}
