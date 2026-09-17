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


#define SND_COMMAND_BLOCK (1 << 0)

BOOL func_020087c0(u32 flags);
void SND_WaitForCommandProc(u32 tag);
u32 func_020089e8(void);
void SND_StopTimer(u32 chBitMask, u32 capBitMask, u32 alarmBitMask, u32 flags);
void func_02008458(int decay);
typedef enum {
    PXI_FIFO_TAG_EX = 0,
    PXI_FIFO_TAG_USER_0,
    PXI_FIFO_TAG_USER_1,
    PXI_FIFO_TAG_SYSTEM,
    PXI_FIFO_TAG_NVRAM,
    PXI_FIFO_TAG_RTC,
    PXI_FIFO_TAG_TOUCHPANEL,
    PXI_FIFO_TAG_SOUND,
    PXI_FIFO_TAG_PM,
    PXI_FIFO_TAG_MIC,
    PXI_FIFO_TAG_WM,
    PXI_FIFO_TAG_FS,
    PXI_FIFO_TAG_OS,
    PXI_FIFO_TAG_CTRDG,
    PXI_FIFO_TAG_CARD,
    PXI_FIFO_TAG_WVR,
    PXI_FIFO_TAG_CTRDG_Ex,
    PXI_FIFO_TAG_CTRDG_PHI,
    PXI_MAX_FIFO_TAG = 32
} PXIFifoTag;
typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);
void func_0201afac(void);
void func_02019f6c(int fadeFrame);
void func_0201cb80(int fadeFrame);

/* func_02019c20 -- NitroSystem main.c: NNS_SndStopSoundAll. */
void func_02019c20 (void)
{
    u32 commandTag;

    func_02019f6c(0);
#ifndef SDK_SMALL_BUILD
    func_0201cb80(0);
#endif
    func_0201afac();

    func_02008458(0);
    SND_StopTimer(0xffff, 0xffff, 0xffff, 0);

    commandTag = func_020089e8();
    (void)func_020087c0(SND_COMMAND_BLOCK);
    SND_WaitForCommandProc(commandTag);
}
