/* CARDi_ReadRomSyncCore -- NitroSDK card_rom.c: the task of a synchronous ROM read. Lets the page
 * cache's accessor (rom_stat.read_func) serve what it can, checks that the card was not pulled out,
 * reports success in the command block and ends the task as CARDi_EndTask does: clear the busy,
 * task and cancel flags, wake the threads waiting for the card and the card thread if it is
 * receiving, then call the caller's callback. */


#include "nitro/types.h"
#include "nitro/os.h"

enum {
    CARD_RESULT_SUCCESS = 0,
    CARD_STAT_BUSY = 1 << 2,
    CARD_STAT_TASK = 1 << 3,
    CARD_STAT_RECV = 1 << 4,
    CARD_STAT_CANCEL = 1 << 6,
    CARD_ROM_PAGE_SIZE = 512
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
    u8 thread[0xc8];
    u8 busy_q[8];
    volatile u32 flag;
};

struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *state);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[CARD_ROM_PAGE_SIZE];
};

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern BOOL CARDi_ReadFromCache(struct CARDRomStat *state);
extern u32 CARDi_ReadRomIDCore(void);
extern void CARDi_CheckPulledOutCore(u32 id);
extern void OS_WakeupThread(void *queue);
extern void OS_WakeupThreadDirect(void *thread);
/* cardi_common: 32-byte aligned, as its backup page buffer (+0x120) is in the SDK; said here, it
 * keeps the block's address in a register instead of re-forming each field's address. */
extern struct CARDiCommon data_020464e0 __attribute__((aligned(32)));
extern struct CARDRomStat data_02046b20;

void CARDi_ReadRomSyncCore(void)
{
    struct CARDRomStat *state = &data_02046b20;
    struct CARDiCommon *common;
    CARDCallback callback;
    void *callbackArgument;
    int interruptState;

    if (CARDi_ReadFromCache(state)) {
        (*state->read_func)(state);
    }
    common = &data_020464e0;
    CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
    common->cmd->result = CARD_RESULT_SUCCESS;
    callback = common->callback;
    callbackArgument = common->callback_arg;
    interruptState = OS_DisableInterrupts();
    common->flag &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
    OS_WakeupThread(common->busy_q);
    if ((common->flag & CARD_STAT_RECV) != 0) {
        OS_WakeupThreadDirect(common->thread);
    }
    OS_RestoreInterrupts(interruptState);
    if (callback != 0) {
        callback(callbackArgument);
    }
}
