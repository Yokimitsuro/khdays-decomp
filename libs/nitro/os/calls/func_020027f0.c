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

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define SDK_ARM9 
#define OS_InitPrintServer() ((void)0)
#define SDK_EXCEPTION_BUG 

void func_02001ba4(void);
void OS_InitIrqTable(void);
extern void OSi_InitStackChecker(void);
void OS_InitLock(void);
void OSi_InstallExceptionVector(void);
void OS_InitArena(void);
void OS_InitArenaEx(void);
void OS_InitTick(void);
void OS_InitAlarm(void);
void func_020037a0(void);
void func_02003894(void);
void OSi_InitVramExclusive(void);
void WM_EndKeySharing_0x0200926c(void);
void CARD_Init(void);
void MI_Init(void);
void func_0200cb40(void);
void func_0200f6d8(void);
extern void OSi_CancelDma0 (void);

/* func_020027f0 -- NitroSDK os_init.c: OS_Init. */
void func_020027f0 (void)
{
#ifdef SDK_ARM9
#ifdef SDK_ENABLE_ARM7_PRINT
    OS_InitPrintServer();
#endif
    OS_InitArena();

    WM_EndKeySharing_0x0200926c();

    OS_InitLock();
    OS_InitArenaEx();
    OS_InitIrqTable();
    OSi_InitStackChecker();
    OSi_InstallExceptionVector();

    MI_Init();

    func_020037a0();
    OSi_InitVramExclusive();

#ifndef SDK_NO_THREAD
    func_02001ba4();
#endif

#ifndef SDK_SMALL_BUILD
    func_02003894();
#endif

#ifndef SDK_TEG
    func_0200f6d8();
#endif

#ifndef SDK_SMALL_BUILD
    CARD_Init();
#endif

#ifndef SDK_TEG
    func_0200cb40();
#endif

    OSi_CancelDma0();

#else
    OS_InitArena();
    WM_EndKeySharing_0x0200926c();
    OS_InitLock();
    OS_InitIrqTable();

#define SDK_EXCEPTION_BUG
#ifndef SDK_EXCEPTION_BUG
    OSi_InstallExceptionVector();
#endif
    OS_InitTick();
    OS_InitAlarm();
    func_02001ba4();

#ifndef SDK_SMALL_BUILD
    func_02003894();
#endif

#ifndef SDK_TEG
    func_0200f6d8();
#endif

#endif
}
