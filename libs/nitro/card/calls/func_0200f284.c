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

#define CARD_PXI_COMMAND_TERMINATE 0x0001
#define HW_CPU_CLOCK_ARM9 67027964
#define PM_RESULT_SUCCESS 0
#define SPI_PXI_RESULT_EXCLUSIVE 0x0004

void OS_Terminate();
extern void OS_Terminate(void);
extern void func_0200386c(u32 cycle);
void MI_StopDma(u32 dmaNo);
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
static inline BOOL PAD_DetectFold (void)
{
    return (BOOL)((*(vu16 *)(0x02000000 + 0x007fffa8) & 0x8000 ) >> 15);
}
u32 OSi_TryShutdown(void);
extern void CARDi_SendtoPxi(u32 data, u32 wait);
extern void CARDi_SendtoPxi (u32 data, u32 wait);

/* func_0200f284 -- NitroSDK card_pullOut.c: CARD_TerminateForPulledOut. */
void func_0200f284 (void)
{
#ifndef SDK_TEG
	BOOL should_be_halt = TRUE;

	MI_StopDma(0);
	MI_StopDma(1);
	MI_StopDma(2);
	MI_StopDma(3);

	if (PAD_DetectFold()) {
		u32 res;
		while ((res = OSi_TryShutdown()) == SPI_PXI_RESULT_EXCLUSIVE) {
			func_0200386c(HW_CPU_CLOCK_ARM9 / 100);
		}
		if (res == PM_RESULT_SUCCESS) {
			should_be_halt = FALSE;
		}
	}

	if (should_be_halt) {
		CARDi_SendtoPxi(CARD_PXI_COMMAND_TERMINATE, 1);
	}
#endif

	OS_Terminate();
}
