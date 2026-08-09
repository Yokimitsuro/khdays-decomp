typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;
typedef s32 PXIFifoTag;

enum {
    PXI_FIFO_TAG_FS = 11,
    CARD_STAT_REQ = 1 << 5
};

typedef void (*CARDCallback)(void *argument);

struct CARDiCommandArg {
    s32 result;
};

struct OSThread;

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
    struct OSThread *cur_th;
    u32 priority;
    u8 busy_q[8];
    volatile u32 flag;
    u8 dummy[8];
    u8 backup_cache_page_buf[256] __attribute__((aligned(32)));
};

extern void OS_WakeupThreadDirect(struct OSThread *thread);
extern struct CARDiCommon data_020464e0;

void CARDi_OnFifoRecv(PXIFifoTag tag, u32 data, BOOL error)
{
#pragma unused(data)
    if ((tag == PXI_FIFO_TAG_FS) && error) {
        struct CARDiCommon *const common = &data_020464e0;
        common->flag &= ~CARD_STAT_REQ;
        OS_WakeupThreadDirect(common->cur_th);
    }
}
