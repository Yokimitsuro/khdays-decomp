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


/* NitroSDK CARD library (card_common.h / card_spi.h): the shared ARM9 request state. */
typedef s32 CARDiOwner;
typedef int CARDResult;
typedef int CARDBackupType;
typedef int CARDRequest;
typedef int CARDRequestMode;
typedef int CARDTargetMode;
typedef void (*MIDmaCallback)(void *);
typedef struct OSThreadQueue { struct OSThread *head; struct OSThread *tail; } OSThreadQueue;

enum {
    CARD_RESULT_SUCCESS = 0, CARD_RESULT_FAILURE, CARD_RESULT_INVALID_PARAM, CARD_RESULT_UNSUPPORTED,
    CARD_RESULT_TIMEOUT, CARD_RESULT_ERROR, CARD_RESULT_NO_RESPONSE, CARD_RESULT_CANCELED
};
enum { CARD_TARGET_NONE, CARD_TARGET_ROM, CARD_TARGET_BACKUP };
enum {
    CARD_REQ_INIT = 0, CARD_REQ_ACK, CARD_REQ_IDENTIFY, CARD_REQ_READ_ID, CARD_REQ_READ_ROM,
    CARD_REQ_WRITE_ROM, CARD_REQ_READ_BACKUP, CARD_REQ_WRITE_BACKUP, CARD_REQ_PROGRAM_BACKUP,
    CARD_REQ_VERIFY_BACKUP, CARD_REQ_ERASE_PAGE_BACKUP, CARD_REQ_ERASE_SECTOR_BACKUP,
    CARD_REQ_ERASE_CHIP_BACKUP, CARD_REQ_READ_STATUS, CARD_REQ_WRITE_STATUS,
    CARD_REQ_ERASE_SUBSECTOR_BACKUP, CARD_REQ_MAX
};
enum { CARD_REQUEST_MODE_RECV, CARD_REQUEST_MODE_SEND, CARD_REQUEST_MODE_SEND_VERIFY, CARD_REQUEST_MODE_SPECIAL };
enum {
    CARD_STAT_INIT = (1 << 0), CARD_STAT_INIT_CMD = (1 << 1), CARD_STAT_BUSY = (1 << 2),
    CARD_STAT_TASK = (1 << 3), CARD_STAT_RECV = (1 << 4), CARD_STAT_REQ = (1 << 5), CARD_STAT_CANCEL = (1 << 6)
};
#define CARD_BACKUP_CAPS_READ               (u32)(1 << CARD_REQ_READ_BACKUP)
#define CARD_BACKUP_CAPS_AVAILABLE          (u32)(CARD_BACKUP_CAPS_READ - 1)
#define CARD_BACKUP_CAPS_WRITE              (u32)(1 << CARD_REQ_WRITE_BACKUP)
#define CARD_BACKUP_CAPS_PROGRAM            (u32)(1 << CARD_REQ_PROGRAM_BACKUP)
#define CARD_BACKUP_CAPS_VERIFY             (u32)(1 << CARD_REQ_VERIFY_BACKUP)
#define CARD_BACKUP_CAPS_ERASE_PAGE         (u32)(1 << CARD_REQ_ERASE_PAGE_BACKUP)
#define CARD_BACKUP_CAPS_ERASE_SECTOR       (u32)(1 << CARD_REQ_ERASE_SECTOR_BACKUP)
#define CARD_BACKUP_CAPS_ERASE_CHIP         (u32)(1 << CARD_REQ_ERASE_CHIP_BACKUP)
#define CARD_BACKUP_CAPS_READ_STATUS        (u32)(1 << CARD_REQ_READ_STATUS)
#define CARD_BACKUP_CAPS_WRITE_STATUS       (u32)(1 << CARD_REQ_WRITE_STATUS)
#define CARD_BACKUP_CAPS_ERASE_SUBSECTOR    (u32)(1 << CARD_REQ_ERASE_SUBSECTOR_BACKUP)
#define CARD_BACKUP_TYPE_DEVICE_SHIFT   0
#define CARD_BACKUP_TYPE_DEVICE_MASK    0xFF
#define CARD_BACKUP_TYPE_DEVICE_EEPROM  1
#define CARD_BACKUP_TYPE_DEVICE_FLASH   2
#define CARD_BACKUP_TYPE_DEVICE_FRAM    3
#define CARD_BACKUP_TYPE_SIZEBIT_SHIFT  8
#define CARD_BACKUP_TYPE_SIZEBIT_MASK   0xFF
#define CARD_BACKUP_TYPE_VENDER_SHIFT   16
#define CARD_BACKUP_TYPE_VENDER_MASK    0xFF
#define CARD_BACKUP_TYPE_NOT_USE        0
#define CARD_THREAD_PRIORITY_DEFAULT    4
#define OS_LOCK_ID_ERROR (-3)
#define PXI_FIFO_TAG_FS 11
#define HW_ROM_HEADER_BUF       0x027FFE00
#define HW_CARD_ROM_HEADER      0x027FFA80
#define HW_CARD_ROM_HEADER_SIZE 0x160
#define HW_WM_BOOT_BUF          0x027FFC40
#define MB_TYPE_MULTIBOOT       2

typedef struct CARDiCommandArg {
    CARDResult result;            /* 0x00 */
    CARDBackupType type;          /* 0x04 */
    u32 id;                       /* 0x08 */
    u32 src;                      /* 0x0c */
    u32 dst;                      /* 0x10 */
    u32 len;                      /* 0x14 */
    struct {                      /* 0x18: the backup device spec */
        u32 total_size;           /* 0x18 */
        u32 sect_size;            /* 0x1c */
        u32 subsect_size;         /* 0x20 */
        u32 page_size;            /* 0x24 */
        u32 addr_width;           /* 0x28 */
        u32 program_page;         /* 0x2c */
        u32 write_page;           /* 0x30 */
        u32 write_page_total;     /* 0x34 */
        u32 erase_chip;           /* 0x38 */
        u32 erase_chip_total;     /* 0x3c */
        u32 erase_sector;         /* 0x40 */
        u32 erase_sector_total;   /* 0x44 */
        u32 erase_subsector;      /* 0x48 */
        u32 erase_subsector_total;/* 0x4c */
        u32 erase_page;           /* 0x50 */
        u8 initial_status;        /* 0x54 */
        u8 padding1[3];
        u32 caps;                 /* 0x58 */
        u8 padding2[4];
    } spec;
} CARDiCommandArg;                /* 0x60 */

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
    CARDRequest req_type;         /* 0x2c */
    int req_retry;                /* 0x30 */
    CARDRequestMode req_mode;     /* 0x34 */
    MIDmaCallback callback;       /* 0x38 */
    void *callback_arg;           /* 0x3c */
    void (*task_func)(struct CARDiCommon *);   /* 0x40 */
    u8 thread[0xc0];              /* 0x44: OSThread (0xc0 bytes in this SDK) */
    struct OSThread *cur_th;      /* 0x104 */
    u32 priority;                 /* 0x108 */
    OSThreadQueue busy_q[1];      /* 0x10c */
    volatile u32 flag;            /* 0x114 */
    u32 flush_threshold_ic;       /* 0x118 */
    u32 flush_threshold_dc;       /* 0x11c */
    u8 backup_cache_page_buf[256] __attribute__((aligned(32)));   /* 0x120 */
} CARDiCommon;                    /* 0x220 */

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_02001f10(OSThreadQueue *queue);   /* OS_SleepThread */
#define OS_SleepThread func_02001f10
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void OS_WakeupThreadDirect(void *thread);
extern void OS_Terminate(void);
#define OS_Panic(...) OS_Terminate()
#define OS_TPanic(...) OS_Terminate()
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void DC_InvalidateRange(void *startAddr, u32 nBytes);
extern void DC_WaitWriteBufferEmpty(void);
extern BOOL CARDi_Request(CARDiCommon *p, int req_type, int retry_max);
extern void CARDi_SetTask(void (*task)(CARDiCommon *));
extern u32 CARD_GetBackupSectorSize(void);
extern void CARD_CheckEnabled(void);
extern void func_02000b64(void *symbol);   /* OSi_ReferSymbol */
#define OSi_ReferSymbol func_02000b64
/* SDK_DEFINE_MIDDLEWARE(cardi_backup_assert, "NINTENDO", "BACKUP"): the "[SDK+NINTENDO:BACKUP]"
 * string lives inside BuildInfo (0x02000b68) in this ROM; SDK_USING_BACKUP references it. */
#define cardi_backup_assert ((char *)0x02000b8c)
#define SDK_USING_BACKUP() OSi_ReferSymbol((void *)cardi_backup_assert)
/* OSi_ThreadInfo (data_02044330): OS_GetCurrentThread() reads its `current` slot. */
extern struct { u32 initialized; struct OSThread *current; } data_02044330;
#define OS_GetCurrentThread() (data_02044330.current)

/* OS_InitThreadQueue: the chained store (tail first, then head) is the SDK inline's form. */
static inline void OS_InitThreadQueue(OSThreadQueue *queue)
{
    queue->head = queue->tail = NULL;
}

static inline void CARDi_WaitTask(CARDiCommon *p, MIDmaCallback callback, void *callback_arg)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();

    while ((p->flag & CARD_STAT_BUSY) != 0) {
        OS_SleepThread(p->busy_q);
    }

    p->flag |= CARD_STAT_BUSY;
    p->callback = callback;
    p->callback_arg = callback_arg;

    (void)OS_RestoreInterrupts(bak_psr);
}

static inline void CARDi_EndTask(CARDiCommon *p, BOOL is_own_task)
{
    const MIDmaCallback func = p->callback;
    void *const arg = p->callback_arg;

    {
        OSIntrMode bak_psr = OS_DisableInterrupts();

        p->flag &= ~(CARD_STAT_BUSY | CARD_STAT_TASK | CARD_STAT_CANCEL);
        OS_WakeupThread(p->busy_q);

        if ((p->flag & CARD_STAT_RECV) != 0) {
            OS_WakeupThreadDirect(p->thread);
        }

        (void)OS_RestoreInterrupts(bak_psr);
    }

    if (is_own_task && func) {
        (*func)(arg);
    }
}
/* card_spi.c: cardi_common is the plain extern of card_common.h. */
extern CARDiCommon data_020464e0;   /* cardi_common */
#define cardi_common data_020464e0

/* func_0200e1a0 -- NitroSDK card_spi.c: CARDi_IdentifyBackupCore. */
void func_0200e1a0(CARDBackupType type)
{
    {
        CARDiCommandArg *const p = cardi_common.cmd;

        MI_CpuFill8(&p->spec, 0, sizeof(p->spec));
        p->type = type;
        p->spec.caps = (CARD_BACKUP_CAPS_AVAILABLE | CARD_BACKUP_CAPS_READ_STATUS);
        if (type != CARD_BACKUP_TYPE_NOT_USE)
        {
            const u32 size = (u32)(1 << ((type >> CARD_BACKUP_TYPE_SIZEBIT_SHIFT) &
                                         CARD_BACKUP_TYPE_SIZEBIT_MASK));
            const int device =
                ((type >> CARD_BACKUP_TYPE_DEVICE_SHIFT) & CARD_BACKUP_TYPE_DEVICE_MASK);
            const int vender =
                ((type >> CARD_BACKUP_TYPE_VENDER_SHIFT) & CARD_BACKUP_TYPE_VENDER_MASK);

            p->spec.total_size = size;
            /* Use 0xFF if the status register does not need to be corrected. (This is usually the case.) */
            p->spec.initial_status = 0xFF;
            if (device == CARD_BACKUP_TYPE_DEVICE_EEPROM)
            {
                switch (size)
                {
                default:
                    goto invalid_type;
                case 0x000200:
                    p->spec.page_size = 0x10;
                    p->spec.addr_width = 1;
                    p->spec.program_page = 5;
                    p->spec.initial_status = 0xF0;
                    break;
                case 0x002000:
                    p->spec.page_size = 0x0020;
                    p->spec.addr_width = 2;
                    p->spec.program_page = 5;
                    p->spec.initial_status = 0x00;
                    break;
                case 0x010000:
                    p->spec.page_size = 0x0080;
                    p->spec.addr_width = 2;
                    p->spec.program_page = 10;
                    p->spec.initial_status = 0x00;
                    break;
                }
                p->spec.sect_size = p->spec.page_size;
                p->spec.caps |= CARD_BACKUP_CAPS_READ;
                p->spec.caps |= CARD_BACKUP_CAPS_PROGRAM;
                p->spec.caps |= CARD_BACKUP_CAPS_VERIFY;
                p->spec.caps |= CARD_BACKUP_CAPS_WRITE_STATUS;
            }
            else if (device == CARD_BACKUP_TYPE_DEVICE_FLASH)
            {
                switch (size)
                {
                default:
                    goto invalid_type;
                case 0x040000:
                case 0x080000:
                case 0x100000:
                    p->spec.write_page = 25;
                    p->spec.write_page_total = 300;
                    p->spec.erase_page = 300;
                    p->spec.erase_sector = 5000;
                    p->spec.caps |= CARD_BACKUP_CAPS_WRITE;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_PAGE;
                    break;
                case 0x200000:
                    p->spec.write_page = 23;
                    p->spec.write_page_total = 300;
                    p->spec.erase_sector = 500;
                    p->spec.erase_sector_total = 5000;
                    p->spec.erase_chip = 10000;
                    p->spec.erase_chip_total = 60000;
                    p->spec.initial_status = 0x00;
                    p->spec.caps |= CARD_BACKUP_CAPS_WRITE;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_PAGE;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_CHIP;
                    p->spec.caps |= CARD_BACKUP_CAPS_WRITE_STATUS;
                    break;
                case 0x400000:
                    p->spec.erase_sector = 600;
                    p->spec.erase_sector_total = 3000;
                    p->spec.erase_subsector = 70;
                    p->spec.erase_subsector_total = 150;
                    p->spec.erase_chip = 23000;
                    p->spec.erase_chip_total = 800000;
                    p->spec.initial_status = 0x00;
                    p->spec.subsect_size = 0x1000;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_SUBSECTOR;
                    p->spec.caps |= CARD_BACKUP_CAPS_ERASE_CHIP;
                    p->spec.caps |= CARD_BACKUP_CAPS_WRITE_STATUS;
                    break;
                case 0x800000:
                    if (vender == 0)
                    {
                        p->spec.erase_sector = 1000;
                        p->spec.erase_sector_total = 3000;
                        p->spec.erase_chip = 68000;
                        p->spec.erase_chip_total = 160000;
                        p->spec.initial_status = 0x00;
                        p->spec.caps |= CARD_BACKUP_CAPS_ERASE_CHIP;
                        p->spec.caps |= CARD_BACKUP_CAPS_WRITE_STATUS;
                    }
                    else if (vender == 1)
                    {
                        p->spec.erase_sector = 1000;
                        p->spec.erase_sector_total = 3000;
                        p->spec.erase_chip = 68000;
                        p->spec.erase_chip_total = 160000;
                        p->spec.initial_status = 0x84;
                        p->spec.caps |= CARD_BACKUP_CAPS_ERASE_CHIP;
                        p->spec.caps |= CARD_BACKUP_CAPS_WRITE_STATUS;
                    }
                    break;
                }
                p->spec.sect_size = 0x010000;
                p->spec.page_size = 0x0100;
                p->spec.addr_width = 3;
                p->spec.program_page = 5;
                p->spec.caps |= CARD_BACKUP_CAPS_READ;
                p->spec.caps |= CARD_BACKUP_CAPS_PROGRAM;
                p->spec.caps |= CARD_BACKUP_CAPS_VERIFY;
                p->spec.caps |= CARD_BACKUP_CAPS_ERASE_SECTOR;
            }
            else if (device == CARD_BACKUP_TYPE_DEVICE_FRAM)
            {
                switch (size)
                {
                default:
                    goto invalid_type;
                case 0x002000:
                case 0x008000:
                    break;
                }
                p->spec.page_size = size;
                p->spec.sect_size = size;
                p->spec.addr_width = 2;
                p->spec.initial_status = 0x00;
                p->spec.caps |= CARD_BACKUP_CAPS_READ;
                p->spec.caps |= CARD_BACKUP_CAPS_PROGRAM;
                p->spec.caps |= CARD_BACKUP_CAPS_VERIFY;
                p->spec.caps |= CARD_BACKUP_CAPS_WRITE_STATUS;
            }
            else
            {
              invalid_type:
                p->type = CARD_BACKUP_TYPE_NOT_USE;
                p->spec.total_size = 0;
                cardi_common.cmd->result = CARD_RESULT_UNSUPPORTED;
                return;
            }
        }
    }
}
