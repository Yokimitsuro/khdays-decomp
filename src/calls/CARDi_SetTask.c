typedef unsigned char u8;
typedef unsigned long u32;
typedef signed long s32;

struct CARDiCommon {
    void *cmd;
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
    void *callback;
    void *callback_arg;
    void (*task_func)(struct CARDiCommon *common);
    u8 thread[0xc0];
    void *cur_th;
    u32 priority;
    u8 busy_q[8];
    volatile u32 flag;
};

extern struct CARDiCommon data_020464e0;
extern int OSi_WaitOnExitProc(void *target, int newval);
extern void OS_WakeupThreadDirect(void *thread);

void CARDi_SetTask(void (*task)(struct CARDiCommon *common))
{
    struct CARDiCommon *const common = &data_020464e0;

    OSi_WaitOnExitProc(common->thread, common->priority);
    common->cur_th = common->thread;
    common->task_func = task;
    common->flag |= 8;
    OS_WakeupThreadDirect(common->thread);
}
