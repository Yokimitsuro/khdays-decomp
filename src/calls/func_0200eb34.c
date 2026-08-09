typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef volatile unsigned long vu32;
typedef int BOOL;

enum {
    FALSE = 0,
    TRUE = 1,
    MI_DMA_MAX_NUM = 3,
    CARD_COMMAND_PAGE = 0x01000000,
    CARD_COMMAND_MASK = 0x07000000,
    CARD_READ_MODE = 0,
    CARD_START = 0x80000000,
    CARD_RESET_HI = 0x20000000,
    CARD_ROM_PAGE_SIZE = 512,
    HW_CACHE_LINE_SIZE = 32,
    HW_ITCM = 0x01ff8000,
    HW_ITCM_SIZE = 0x8000,
    HW_DTCM_SIZE = 0x4000,
    OS_IE_CARD_DATA = 1 << 19
};

typedef void (*CARDCallback)(void *argument);
typedef void (*OSIrqFunction)(void);

struct CARDiCommandArg {
    int result;
};

struct CARDiCommon {
    struct CARDiCommandArg *cmd;
    s32 command;
    volatile s32 lock_owner;
    volatile s32 lock_ref;
    u8 lock_queue[8];
    s32 lock_target;
    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
    s32 req_type;
    s32 req_retry;
    s32 req_mode;
    CARDCallback callback;
    void *callback_arg;
    void (*task_func)(struct CARDiCommon *common);
    u8 thread[0xc8];
    u8 busy_q[8];
    volatile u32 flag;
    u32 icache_threshold;
    u32 dcache_threshold;
};

struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *state);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[CARD_ROM_PAGE_SIZE];
};

extern u32 OS_GetDTCMAddress(void);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void IC_InvalidateRange(void *address, u32 size);
extern void IC_InvalidateAll(void);
extern void DC_StoreRange(void *address, u32 size);
extern void DC_InvalidateRange(void *address, u32 size);
extern void DC_WaitWriteBufferEmpty(void);
extern void DC_FlushAll(void);
extern OSIrqFunction OS_SetIrqFunction(u32 mask, OSIrqFunction function);
extern void OS_ResetRequestIrqMask(u32 mask);
extern void OS_EnableIrqMask(u32 mask);
extern void CARDi_SetCardDma(void);
extern void func_0200ea64(void);
extern void OSi_VBlankInterruptHandler(void);
extern struct CARDiCommon data_020464e0;
extern u32 data_020423e8;

static inline BOOL Card_IsInTcm(u32 buffer, u32 length)
{
    const u32 instructionTcm = (u32)OSi_VBlankInterruptHandler;
    const u32 dataTcm = OS_GetDTCMAddress();
    return ((buffer + length > instructionTcm) &&
            (buffer < HW_ITCM + HW_ITCM_SIZE)) ||
           ((dataTcm < buffer + length) &&
            (dataTcm + HW_DTCM_SIZE > buffer));
}

static inline u32 Card_GetRomFlag(u32 flag)
{
    const u32 control = *(vu32 *)(data_020423e8 + 0x60);
    return (control & ~CARD_COMMAND_MASK) | flag |
           CARD_READ_MODE | CARD_START | CARD_RESET_HI;
}

BOOL func_0200eb34(struct CARDRomStat *state)
{
    struct CARDiCommon *const common = &data_020464e0;
    const u32 destination = common->dst;
    u32 length = common->len;
    const BOOL asynchronous = !(destination & (HW_CACHE_LINE_SIZE - 1)) &&
                              (common->dma <= MI_DMA_MAX_NUM) &&
                              !Card_IsInTcm(destination, length) &&
                              !((common->src | length) & (CARD_ROM_PAGE_SIZE - 1)) &&
                              (length > 0);

    state->ctrl = Card_GetRomFlag(CARD_COMMAND_PAGE);
    if (asynchronous) {
        int interruptState = OS_DisableInterrupts();

        if (length < common->icache_threshold) {
            IC_InvalidateRange((void *)destination, length);
        } else {
            IC_InvalidateAll();
        }

        if (length < common->dcache_threshold) {
            u32 position = destination;
            u32 misalignment = destination & (HW_CACHE_LINE_SIZE - 1);
            if (misalignment) {
                position -= misalignment;
                DC_StoreRange((void *)position, HW_CACHE_LINE_SIZE);
                DC_StoreRange((void *)(position + length), HW_CACHE_LINE_SIZE);
                length += HW_CACHE_LINE_SIZE;
            }
            DC_InvalidateRange((void *)position, length);
            DC_WaitWriteBufferEmpty();
        } else {
            DC_FlushAll();
        }

        OS_SetIrqFunction(OS_IE_CARD_DATA, func_0200ea64);
        OS_ResetRequestIrqMask(OS_IE_CARD_DATA);
        OS_EnableIrqMask(OS_IE_CARD_DATA);
        OS_RestoreInterrupts(interruptState);
        CARDi_SetCardDma();
    }
    return asynchronous;
}
