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


/* NitroSDK MI library: DMA transfers (mi_dma.c, mi_dma_card.c, mi_dma_gxcommand.c). */
typedef void (*MIDmaCallback)(void *);
#define HW_REG_BASE                 0x04000000
#define REG_DMA0SAD_ADDR            (HW_REG_BASE + 0x0b0)
#define REG_GXFIFO_ADDR             (HW_REG_BASE + 0x400)
#define REG_MI_DMA0CNT_E_MASK       0x80000000
#define MI_DMA_ENABLE               (1UL << 31)
#define MI_DMA_IF_ENABLE            (1UL << 30)
#define MI_DMA_TIMING_IMM           (0UL << 27)
#define MI_DMA_TIMING_CARD          (5UL << 27)
#define MI_DMA_TIMING_GXFIFO        (7UL << 27)
#define MIi_DMA_TIMING_ANY          (u32)(~0)
#define MI_DMA_16BIT_BUS            (0UL << 26)
#define MI_DMA_32BIT_BUS            (1UL << 26)
#define MI_DMA_CONTINUOUS_ON        (1UL << 25)
#define MI_DMA_SRC_INC              (0UL << 23)
#define MI_DMA_SRC_DEC              (1UL << 23)
#define MI_DMA_SRC_FIX              (2UL << 23)
#define MI_DMA_DEST_INC             (0UL << 21)
#define MI_DMA_DEST_FIX             (2UL << 21)
#define MI_DMA_IMM16ENABLE          (MI_DMA_ENABLE | MI_DMA_TIMING_IMM | MI_DMA_16BIT_BUS)
#define MI_DMA_IMM32ENABLE          (MI_DMA_ENABLE | MI_DMA_TIMING_IMM | MI_DMA_32BIT_BUS)
#define MI_CNT_COPY16(size)         (MI_DMA_IMM16ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_INC | ((size) / 2))
#define MI_CNT_COPY32(size)         (MI_DMA_IMM32ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_INC | ((size) / 4))
#define MI_CNT_COPY32_IF(size)      (MI_CNT_COPY32((size)) | MI_DMA_IF_ENABLE)
#define MI_CNT_SEND32(size)         (MI_DMA_IMM32ENABLE | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | ((size) / 4))
#define MI_CNT_SEND32_IF(size)      (MI_CNT_SEND32((size)) | MI_DMA_IF_ENABLE)
#define MI_CNT_CARDRECV32(size)     (MI_DMA_ENABLE | MI_DMA_TIMING_CARD | MI_DMA_SRC_FIX | MI_DMA_DEST_INC | MI_DMA_32BIT_BUS | ((size) / 4))
#define MI_CNT_GXCOPY(size)         (MI_DMA_ENABLE | MI_DMA_TIMING_GXFIFO | MI_DMA_SRC_INC | MI_DMA_DEST_FIX | MI_DMA_32BIT_BUS | ((size) / 4))
#define MI_CNT_GXCOPY_IF(size)      (MI_CNT_GXCOPY(size) | MI_DMA_IF_ENABLE)
#define OS_IE_GXFIFO                (1UL << 21)
#define MIi_GX_LENGTH_ONCE          (118 * sizeof(u32))

#define MIi_Wait_BeforeDMA(dmaCntp, dmaNo) \
    do { \
        dmaCntp = &((vu32 *)REG_DMA0SAD_ADDR)[dmaNo * 3 + 2]; \
        while (*dmaCntp & REG_MI_DMA0CNT_E_MASK) {} \
    } while (0)

#define MIi_Wait_AfterDMA(dmaCntp) \
    do { \
        while (*dmaCntp & REG_MI_DMA0CNT_E_MASK) {} \
    } while (0)

static inline void MIi_CallCallback(MIDmaCallback callback, void *arg)
{
    if (callback) {
        (callback)(arg);
    }
}

extern void MIi_CheckDma0SourceAddress(u32 dmaNo, u32 src, u32 size, u32 dir);
extern void MIi_CheckAnotherAutoDMA(u32 dmaNo, u32 dmaType);
extern void MIi_DmaSetParams(u32 dmaNo, u32 src, u32 dest, u32 ctrl);
extern void func_01ff85d0(u32 dmaNo, u32 src, u32 dest, u32 ctrl);   /* MIi_DmaSetParams_wait (ITCM) */
#define MIi_DmaSetParams_wait func_01ff85d0
extern void MI_WaitDma(u32 dmaNo);
extern void OSi_EnterDmaCallback(u32 dmaNo, MIDmaCallback callback, void *arg);
extern u32 OS_ResetRequestIrqMask(u32 intr);
extern void OS_Terminate(void);
#define OS_Panic(...) OS_Terminate()

typedef struct {
    volatile BOOL isBusy;         /* 0x00 */
    u32 dmaNo;                    /* 0x04 */
    u32 src;                      /* 0x08 */
    u32 length;                   /* 0x0c */
    MIDmaCallback callback;       /* 0x10 */
    void *arg;                    /* 0x14 */
    int fifoCond;                 /* 0x18: GXFifoIntrCond */
    void (*fifoFunc)(void);       /* 0x1c */
} MIiGXDmaParams;
extern MIiGXDmaParams data_020446b0;   /* MIi_GXDmaParams */
#define MIi_GXDmaParams data_020446b0
extern void MIi_DMACallback(void *arg);
extern void MIi_DMAFastCallback(void *arg);

/* MI_SendGXCommandAsyncFast -- NitroSDK mi_dma_gxcommand.c. */
void MI_SendGXCommandAsyncFast (u32 dmaNo, const void * src, u32 commandLength, MIDmaCallback callback, void * arg)
{

	if (commandLength == 0) {
		MIi_CallCallback(callback, arg);
		return;
	}

	while (MIi_GXDmaParams.isBusy  ) {
	}

	MIi_GXDmaParams.isBusy = TRUE;
	MIi_GXDmaParams.dmaNo = dmaNo;
	MIi_GXDmaParams.callback = callback;
	MIi_GXDmaParams.arg = arg;

	MIi_CheckAnotherAutoDMA(dmaNo, MI_DMA_TIMING_GXFIFO);
	MIi_CheckDma0SourceAddress(dmaNo, (u32)src, commandLength, MI_DMA_SRC_INC);
	MI_WaitDma(dmaNo);

	OSi_EnterDmaCallback(dmaNo, MIi_DMAFastCallback, NULL);
	MIi_DmaSetParams(dmaNo, (u32)src, (u32)REG_GXFIFO_ADDR, MI_CNT_GXCOPY_IF(commandLength));
}
