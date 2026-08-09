typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;
typedef s32 PXIFifoTag;
typedef s32 PXIProc;
typedef s32 CARDResult;
typedef s32 CARDBackupType;
typedef s32 CARDRequest;
typedef u32 OSIntrMode;

enum {
    TRUE = 1,
    PXI_FIFO_TAG_FS = 11,
    PXI_PROC_ARM7 = 1,
    CARD_RESULT_SUCCESS = 0,
    CARD_RESULT_TIMEOUT = 4,
    CARD_REQ_INIT = 0,
    CARD_STAT_INIT_CMD = 1 << 1,
    CARD_STAT_REQ = 1 << 5
};

typedef void (*CARDCallback)(void *argument);

struct CARDBackupSpec {
    u32 total_size;
    u32 sector_size;
    u32 page_size;
    u32 address_width;
    u32 program_page;
    u32 write_page;
    u32 write_page_total;
    u32 erase_chip;
    u32 erase_chip_total;
    u32 erase_sector;
    u32 erase_sector_total;
    u32 erase_page;
    u8 initial_status;
    u8 padding_31[3];
    u32 capabilities;
    u8 padding_38[16];
};

struct CARDiCommandArg {
    CARDResult result;
    CARDBackupType type;
    u32 id;
    u32 src;
    u32 dest;
    u32 len;
    struct CARDBackupSpec spec;
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
    u8 thread[0xc0];
    void *cur_th;
    u32 priority;
    u8 busy_q[8];
    volatile u32 flag;
    u8 dummy[8];
    u8 backup_cache_page_buf[256] __attribute__((aligned(32)));
};

struct OSThreadQueue;

extern BOOL PXI_IsCallbackReady(PXIFifoTag tag, PXIProc processor);
extern void func_0200386c(u32 cycles);
extern void DC_FlushRange(void *address, u32 size);
extern void DC_WaitWriteBufferEmpty(void);
extern s32 func_020093e8(PXIFifoTag tag, u32 data, BOOL error);
extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void func_02001f10(struct OSThreadQueue *queue);
extern void DC_InvalidateRange(void *address, u32 size);

static inline void CARDi_SendPxi(u32 data)
{
    while (func_020093e8(PXI_FIFO_TAG_FS, data, TRUE) < 0) {
    }
}

BOOL CARDi_Request(struct CARDiCommon *common, CARDRequest requestType, s32 retryCount)
{
    if ((common->flag & CARD_STAT_INIT_CMD) == 0) {
        common->flag |= CARD_STAT_INIT_CMD;
        while (!PXI_IsCallbackReady(PXI_FIFO_TAG_FS, PXI_PROC_ARM7)) {
            func_0200386c(100);
        }

        CARDi_Request(common, CARD_REQ_INIT, 1);
    }
    DC_FlushRange(common->cmd, sizeof(*common->cmd));
    DC_WaitWriteBufferEmpty();

    do {
        common->command = requestType;
        common->flag |= CARD_STAT_REQ;
        CARDi_SendPxi((u32)requestType);

        switch (requestType) {
        case CARD_REQ_INIT:
            CARDi_SendPxi((u32)common->cmd);
            break;
        }

        {
            OSIntrMode interruptState = OS_DisableInterrupts();
            while ((common->flag & CARD_STAT_REQ) != 0) {
                func_02001f10(0);
            }
            OS_RestoreInterrupts(interruptState);
        }
        DC_InvalidateRange(common->cmd, sizeof(*common->cmd));
    } while ((common->cmd->result == CARD_RESULT_TIMEOUT) &&
             (--retryCount > 0));

    return common->cmd->result == CARD_RESULT_SUCCESS;
}
