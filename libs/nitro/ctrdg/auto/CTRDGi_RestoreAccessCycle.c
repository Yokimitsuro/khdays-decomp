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


/* NitroSDK CTRDG library (ctrdg_common.h / ctrdg_work.h): the AGB cartridge slot. */
typedef u32 OSIrqMask;
typedef enum { MI_CTRDG_ROMCYCLE1_10 = 0, MI_CTRDG_ROMCYCLE1_8, MI_CTRDG_ROMCYCLE1_6, MI_CTRDG_ROMCYCLE1_18 } MICartridgeRomCycle1st;
typedef enum { MI_CTRDG_ROMCYCLE2_6 = 0, MI_CTRDG_ROMCYCLE2_4 } MICartridgeRomCycle2nd;
typedef enum { MI_PROCESSOR_ARM9 = 0, MI_PROCESSOR_ARM7 } MIProcessor;
typedef int PXIFifoTag;
#define REG_EXMEMCNT_ADDR 0x04000204
#define REG_IME_ADDR      0x04000208
#define REG_PAUSE_ADDR    0x04000300
#define reg_MI_EXMEMCNT (*(vu16 *)REG_EXMEMCNT_ADDR)
#define reg_OS_IME      (*(vu16 *)REG_IME_ADDR)
#define reg_OS_PAUSE    (*(vu16 *)REG_PAUSE_ADDR)
#define REG_OS_PAUSE_CHK_MASK 0x0001
#define OS_IME_ENABLE 1
#define REG_MI_EXMEMCNT_ROM1st_SHIFT 2
#define REG_MI_EXMEMCNT_ROM1st_MASK  0x000c
#define REG_MI_EXMEMCNT_ROM2nd_SHIFT 4
#define REG_MI_EXMEMCNT_ROM2nd_MASK  0x0010
#define REG_MI_EXMEMCNT_EP_SHIFT     15
#define REG_MI_EXMEMCNT_EP_MASK      0x8000
#define OS_IE_SPFIFO_RECV (1UL << 18)
#define HW_MAIN_MEM 0x02000000
#define HW_CTRDG_ROM 0x08000000
#define HW_CTRDG_MODULE_INFO_BUF        (HW_MAIN_MEM + 0x007ffc30)
#define HW_SET_CTRDG_MODULE_INFO_ONCE   (HW_MAIN_MEM + 0x007fff9a)
#define HW_IS_CTRDG_EXIST               (HW_MAIN_MEM + 0x007fff9b)
#define CTRDG_SYSROM9_NINLOGO_ADR       0xffff0020
#define CTRDG_IS_ROM_CODE               0x96
#define CTRDG_PXI_COMMAND_PARAM_SHIFT   6
#define CTRDG_PXI_COMMAND_INIT_MODULE_INFO 0x0001
#define PXI_FIFO_TAG_CTRDG 13
#define PXI_FIFO_SUCCESS 0

typedef struct {
    u32 startAddress;             /* 0x00 */
    u8 nintendoLogo[0x9c];        /* 0x04 */
    char titleName[12];           /* 0xa0 */
    u32 gameCode;                 /* 0xac */
    u16 makerCode;                /* 0xb0 */
    u8 isRomCode;                 /* 0xb2 */
    u8 machineCode;               /* 0xb3 */
    u8 deviceType;                /* 0xb4 */
    u8 exLsiID[3];                /* 0xb5 */
    u8 reserved_A[4];             /* 0xb8 */
    u8 softVersion;               /* 0xbc */
    u8 complement;                /* 0xbd */
    u16 moduleID;                 /* 0xbe */
} CTRDGHeader;                    /* 0xc0 */

typedef struct {
    union {
        struct {
            u8 bitID;
            u8 numberID :5;
            u8 :2;
            u8 disableExLsiID :1;
        };
        u16 raw;
    };
} CTRDGModuleID;

typedef struct {
    CTRDGModuleID moduleID;       /* 0x00 */
    u8 exLsiID[3];                /* 0x02 */
    u8 isAgbCartridge :1;         /* 0x05 bit 0 */
    u8 detectPullOut :1;          /* 0x05 bit 1 */
    u8 :0;
    u16 makerCode;                /* 0x06 */
    u32 gameCode;                 /* 0x08 */
} CTRDGModuleInfo;                /* 0x0c */

typedef struct CTRDGRomCycle {
    MICartridgeRomCycle1st c1;
    MICartridgeRomCycle2nd c2;
} CTRDGRomCycle;

typedef struct CTRDGLockByProc {
    BOOL locked;
    OSIntrMode irq;
} CTRDGLockByProc;

typedef struct CTRDGWork {
    vu16 subpInitialized;
    u16 lockID;
} CTRDGWork;

#define CTRDGi_GetHeaderAddr()          ((CTRDGHeader *)HW_CTRDG_ROM)
#define CTRDGi_GetModuleIDImageAddr()   ((u16 *)(HW_CTRDG_ROM + 0x0001fffe))
#define CTRDGi_GetModuleInfoAddr()      ((CTRDGModuleInfo *)HW_CTRDG_MODULE_INFO_BUF)

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern OSIrqMask OS_SetIrqMask(OSIrqMask intr);
extern void CTRDGi_LockByProcessor(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_UnlockByProcessor(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_ChangeLatestAccessCycle(CTRDGRomCycle *r);
extern void CTRDGi_RestoreAccessCycle(CTRDGRomCycle *r);
extern void CTRDGi_SendtoPxi(u32 data);
extern void DC_InvalidateRange(void *startAddr, u32 nBytes);
extern void DC_FlushAll(void);
extern void MI_DmaCopy16(u32 dmaNo, const void *src, void *dest, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
#define MI_CpuCopy32 MIi_CpuCopy32
extern int func_020093e8(int tag, u32 data, BOOL err);   /* PXI_SendWordByFifo */
#define PXI_SendWordByFifo func_020093e8
extern void WaitByLoop(s32 count);   /* SVC_WaitByLoop */
#define SVC_WaitByLoop WaitByLoop

static inline void MI_SetCartridgeRomCycle1st(MICartridgeRomCycle1st c1)
{
    reg_MI_EXMEMCNT =
        (u16)((reg_MI_EXMEMCNT & ~REG_MI_EXMEMCNT_ROM1st_MASK) |
              (c1 << REG_MI_EXMEMCNT_ROM1st_SHIFT));
}

static inline MICartridgeRomCycle1st MI_GetCartridgeRomCycle1st(void)
{
    return (MICartridgeRomCycle1st)((reg_MI_EXMEMCNT & REG_MI_EXMEMCNT_ROM1st_MASK) >>
                                    REG_MI_EXMEMCNT_ROM1st_SHIFT);
}

static inline void MI_SetCartridgeRomCycle2nd(MICartridgeRomCycle2nd c2)
{
    reg_MI_EXMEMCNT =
        (u16)((reg_MI_EXMEMCNT & ~REG_MI_EXMEMCNT_ROM2nd_MASK) |
              (c2 << REG_MI_EXMEMCNT_ROM2nd_SHIFT));
}

static inline MICartridgeRomCycle2nd MI_GetCartridgeRomCycle2nd(void)
{
    return (MICartridgeRomCycle2nd)((reg_MI_EXMEMCNT & REG_MI_EXMEMCNT_ROM2nd_MASK) >>
                                    REG_MI_EXMEMCNT_ROM2nd_SHIFT);
}

static inline void MI_SetMainMemoryPriority(MIProcessor proc)
{
    reg_MI_EXMEMCNT =
        (u16)((reg_MI_EXMEMCNT & ~REG_MI_EXMEMCNT_EP_MASK) | (proc << REG_MI_EXMEMCNT_EP_SHIFT));
}

static inline MIProcessor MI_GetMainMemoryPriority(void)
{
    return (MIProcessor)((reg_MI_EXMEMCNT & REG_MI_EXMEMCNT_EP_MASK) >> REG_MI_EXMEMCNT_EP_SHIFT);
}

static inline BOOL OS_EnableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = OS_IME_ENABLE;
    return (BOOL)prep;
}

static inline BOOL OS_RestoreIrq(BOOL enable)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = (u16)enable;
    return (BOOL)prep;
}

/* CTRDGi_RestoreAccessCycle -- NitroSDK ctrdg.c. */
void CTRDGi_RestoreAccessCycle (CTRDGRomCycle *r)
{
	MI_SetCartridgeRomCycle1st(r->c1);
	MI_SetCartridgeRomCycle2nd(r->c2);
}
