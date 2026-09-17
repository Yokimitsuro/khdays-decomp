typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
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



typedef int PXIProc;
#define HW_MAIN_MEM_SYSTEM 0x027ffc00
typedef struct OSSystemWork {
    u8 reserved[0x388];
    u32 pxiHandleChecker[2];      /* 0x388: fifo tags each processor has a callback for */
} OSSystemWork;
#define OS_GetSystemWork() ((OSSystemWork *)HW_MAIN_MEM_SYSTEM)

/* PXI_IsCallbackReady -- NitroSDK pxi_fifo.c: whether processor `proc` has registered a
 * fifo receive callback for `fifotag` (the shared-work bit set by PXI_SetFifoRecvCallback). */
BOOL PXI_IsCallbackReady(int fifotag, PXIProc proc)
{
    OSSystemWork *p = OS_GetSystemWork();
    return (p->pxiHandleChecker[proc] & (1UL << fifotag)) ? TRUE : FALSE;
}
