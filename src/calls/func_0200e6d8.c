typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef int BOOL;

enum {
    CARD_STAT_BUSY = 1 << 2
};

typedef void (*CARDCallback)(void *argument);

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
    u8 thread[0xc0];
    void *cur_th;
    u32 priority;
    u8 busy_q[8];
    volatile u32 flag;
};

struct OSiThreadInfoPrefix {
    u32 initialized;
    void *current_thread;
};

extern void func_02000b64(void *p);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02001f10(void *queue);
extern void CARDi_SetTask(void (*task)(struct CARDiCommon *common));
extern void func_0200e4e8(struct CARDiCommon *common);
extern struct CARDiCommon data_020464e0;
extern struct OSiThreadInfoPrefix data_02044330;

static inline void Card_WaitTask(struct CARDiCommon *common,
                                 CARDCallback callback,
                                 void *callbackArgument)
{
    int interruptState = OS_DisableInterrupts();
    while ((common->flag & CARD_STAT_BUSY) != 0) {
        func_02001f10(common->busy_q);
    }
    common->flag |= CARD_STAT_BUSY;
    common->callback = callback;
    common->callback_arg = callbackArgument;
    OS_RestoreInterrupts(interruptState);
}

BOOL func_0200e6d8(u32 src, u32 dst, u32 len, CARDCallback callback,
                    void *callbackArgument, BOOL asynchronous,
                    s32 reqType, s32 reqRetry, s32 reqMode)
{
    struct CARDiCommon *const common = &data_020464e0;

    func_02000b64((void *)0x02000b8c);
    Card_WaitTask(common, callback, callbackArgument);

    common->src = src;
    common->dst = dst;
    common->len = len;
    common->req_type = reqType;
    common->req_retry = reqRetry;
    common->req_mode = reqMode;

    if (asynchronous) {
        CARDi_SetTask(func_0200e4e8);
        return 1;
    }

    data_020464e0.cur_th = data_02044330.current_thread;
    func_0200e4e8(common);
    return (common->cmd->result == 0);
}
