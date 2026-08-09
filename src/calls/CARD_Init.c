typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;

enum {
    CARD_STAT_INIT = 1 << 0
};

typedef void (*CARDCallback)(void *argument);

struct CARDiCommandArg {
    int result;
};

struct CARDRomStat;

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

struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *state);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[0x200];
};

extern void func_0200df58(void);
extern void (*CARDi_GetRomAccessor(void))(struct CARDRomStat *state);
extern void func_0200f1f4(void);
extern struct CARDiCommon data_020464e0;
extern u32 data_02046b00;
extern struct CARDRomStat data_02046b20 __attribute__((aligned(32)));

void CARD_Init(void)
{
    struct CARDiCommon *const common = &data_020464e0;

    if (common->flag == 0) {
        common->flag = CARD_STAT_INIT;
        common->src = common->dst = common->len = 0;
        common->dma = (u32)~0;
        common->callback = 0;
        common->callback_arg = 0;

        data_02046b00 = 0;
        func_0200df58();
        data_02046b20.read_func = CARDi_GetRomAccessor();
        func_0200f1f4();
    }
}
