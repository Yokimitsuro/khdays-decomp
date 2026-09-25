/* Types shared by the DS Protect 1.10 units of ov028 (compiled with mwccarm 2.0/sp2p2, the
 * library's own compiler; see config/arm9/file_compilers.json). */
#ifndef DSPROT_TYPES_H
#define DSPROT_TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile signed int vs32;
typedef int BOOL;

#define TRUE 1
#define FALSE 0
#define NULL ((void *)0)

/* NitroSDK OSOwnerInfo (os_ownerInfo.h) */
typedef struct OSBirthday {
    u8 month;
    u8 day;
} OSBirthday;

typedef struct OSOwnerInfo {
    u8 language;
    u8 favoriteColor;
    OSBirthday birthday;
    u16 nickName[10 + 1];
    u16 nickNameLength;
    u16 comment[26 + 1];
    u16 commentLength;
} OSOwnerInfo;

extern s32 OS_GetLockID(void);
extern void OS_ReleaseLockID(u16 lockId);
extern void OS_GetMacAddress(u8 *pMacAddress);
extern void func_02003a20(OSOwnerInfo *pInfo);           /* OS_GetOwnerInfo */
extern void CARD_LockRom(u16 lockId);
extern void CARD_UnlockRom(u16 lockId);

/* The library's own units (ov028) */
extern u32 func_ov028_0208abd0(void);                       /* MACOwner_IsBad */
extern void func_ov028_0208acf0(void *dest, u32 addr, s32 size);  /* ROMUtil_Read */
extern u32 func_ov028_0208ae8c(void *buf, u32 size);        /* ROMUtil_CRC32 */
extern u32 func_ov028_0208af30(void);                       /* ROMTest_IsBad */

#endif
