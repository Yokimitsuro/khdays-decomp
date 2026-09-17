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


/* NitroSDK CARD library: the game card ROM/backup access shared state (card_common.h / card_rom.h). */
typedef s32 CARDiOwner;
typedef enum { CARD_TARGET_NONE, CARD_TARGET_ROM, CARD_TARGET_BACKUP } CARDTargetMode;
#define CARD_RESULT_SUCCESS 0
#define OS_LOCK_ID_ERROR (-3)
#define CARD_ROM_PAGE_SIZE 512

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct CARDiCommandArg {
    int result;                   /* 0x00: CARDResult */
    int type;                     /* 0x04 */
    u32 id;                       /* 0x08 */
    u32 src;                      /* 0x0c */
    u32 dst;                      /* 0x10 */
    u32 len;                      /* 0x14 */
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *cmd;         /* 0x00 */
    int command;                  /* 0x04 */
    volatile CARDiOwner lock_owner;   /* 0x08 */
    volatile int lock_ref;        /* 0x0c */
    OSThreadQueue lock_queue[1];  /* 0x10 */
    CARDTargetMode lock_target;   /* 0x18 */
    u32 src;                      /* 0x1c */
    u32 dst;                      /* 0x20 */
    u32 len;                      /* 0x24 */
    u32 dma;                      /* 0x28 */
} CARDiCommon;

typedef struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *);   /* 0x00 */
    u32 ctrl;                     /* 0x04 */
    u8 *cache_page;               /* 0x08 */
    u32 dummy[5];                 /* 0x0c */
    u8 cache_buf[CARD_ROM_PAGE_SIZE];   /* 0x20 */
} CARDRomStat;

#define REG_CARDCNT            0x040001a4
#define REG_CARD_DATA          0x04100010
#define CARD_DATA_READY         0x00800000
#define CARD_COMMAND_PAGE       0x01000000
#define CARD_COMMAND_ID         0x07000000
#define CARD_COMMAND_MASK       0x07000000
#define CARD_RESET_HI           0x20000000
#define CARD_READ_MODE          0x00000000
#define CARD_START              0x80000000
#define CARD_LATENCY1_MASK      0x00001FFF
#define MROMOP_G_READ_ID        0xB8000000
#define MROMOP_G_READ_PAGE      0xB7000000

extern u32 data_020423e8;           /* cardi_rom_header_addr */
#define cardi_common data_020464e0
#define rom_stat data_02046b20
#define cardi_rom_header_addr data_020423e8
#define CARD_ALIGN_HI_BIT(n)     (((u32)(n)) & ~(CARD_ROM_PAGE_SIZE - 1))

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_02001f10(OSThreadQueue *queue);   /* OS_SleepThread */
#define OS_SleepThread func_02001f10
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void OS_Terminate(void);
#define OS_Panic(...) OS_Terminate()
#define OS_TPanic(...) OS_Terminate()
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
extern void CARDi_SetRomOp(u32 cmd1, u32 cmd2);

static inline u32 CARDi_GetRomFlag(u32 flag)
{
    const u32 rom_ctrl = *(vu32 *)(cardi_rom_header_addr + 0x60);
    return (u32)((rom_ctrl & ~CARD_COMMAND_MASK) | flag |
                 CARD_READ_MODE | CARD_START | CARD_RESET_HI);
}

static inline void CARDi_SetRomOpReadPage1(u32 src)
{
    CARDi_SetRomOp((u32)(MROMOP_G_READ_PAGE | (src >> 8)), (u32)(src << 24));
}

/* card_rom.c: cardi_common comes from card_common.h (plain extern); rom_stat is defined here ATTRIBUTE_ALIGN(32). */
extern CARDiCommon data_020464e0;   /* cardi_common */
extern CARDRomStat data_02046b20 __attribute__((aligned(32)));   /* rom_stat */
/* CARDi_ReadRomIDCore -- NitroSDK card_rom.c: issue the READ_ID command and return the
 * card's chip id word. */
u32 CARDi_ReadRomIDCore(void)
{
    CARDi_SetRomOp(MROMOP_G_READ_ID, 0);
    *(vu32 *)REG_CARDCNT = (u32)(CARDi_GetRomFlag(CARD_COMMAND_ID) & ~CARD_LATENCY1_MASK);
    while (!(*(vu32 *)REG_CARDCNT & CARD_DATA_READY)) {
    }
    return *(vu32 *)REG_CARD_DATA;
}
