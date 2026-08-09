typedef signed long s32;
typedef unsigned long u32;
typedef unsigned char u8;
typedef volatile unsigned long vu32;
typedef int BOOL;

enum {
    FALSE = 0,
    TRUE = 1,
    CARD_ROM_PAGE_SIZE = 512,
    CARD_DATA_READY = 0x00800000,
    CARD_START = 0x80000000,
    MROMOP_G_READ_PAGE = 0xb7000000
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
    u8 remainder[0xdc];
};

struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *state);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[CARD_ROM_PAGE_SIZE];
};

#define REG_CARD_CONTROL (*(vu32 *)0x040001a4)
#define REG_CARD_DATA (*(vu32 *)0x04100010)

extern void CARDi_SetRomOp(u32 command1, u32 command2);
extern BOOL CARDi_ReadFromCache(struct CARDRomStat *state);
extern struct CARDiCommon data_020464e0;

static inline void Card_SetReadPageCommand(u32 source)
{
    CARDi_SetRomOp(MROMOP_G_READ_PAGE | (source >> 8), source << 24);
}

static inline BOOL Card_AdvanceReadPage(struct CARDRomStat *state)
{
#pragma unused(state)
    struct CARDiCommon *common = &data_020464e0;
    common->src += CARD_ROM_PAGE_SIZE;
    common->dst += CARD_ROM_PAGE_SIZE;
    common->len -= CARD_ROM_PAGE_SIZE;
    return common->len > 0;
}

void func_0200ecc0(struct CARDRomStat *state)
{
    struct CARDiCommon *const common = &data_020464e0;

read_page:
    {
        const u32 length = CARD_ROM_PAGE_SIZE;
        u32 source = common->src & ~(CARD_ROM_PAGE_SIZE - 1);
        u32 destination;

        if ((source != common->src) ||
            ((common->dst & 3) != 0) ||
            (common->len < length)) {
            destination = (u32)state->cache_buf;
            state->cache_page = (u8 *)source;
        } else {
            destination = common->dst;
        }

        Card_SetReadPageCommand(source);
        {
            u32 index = 0;

            REG_CARD_CONTROL = state->ctrl;
            while (TRUE) {
                const u32 control = REG_CARD_CONTROL;
                if ((control & CARD_DATA_READY) != 0) {
                    u32 data = REG_CARD_DATA;
                    if (index * sizeof(u32) < length) {
                        ((u32 *)destination)[index++] = data;
                    }
                }
                if ((control & CARD_START) == 0) {
                    break;
                }
            }
        }

        if (destination == common->dst) {
            if (Card_AdvanceReadPage(state)) {
                goto read_page;
            }
        } else if (CARDi_ReadFromCache(state)) {
            goto read_page;
        }
    }
}
