/* func_ov008_02082714 -- Ov008_InitPanelSlotManagers: create the panel
 * context's two slot managers.  Manager B (+0x7530, handle kept at +0xbfb4)
 * is initialised with cell 3 of the first source (+0x4), one slot, forwarded
 * to cell (second source +0x8, slot from table 0208fef3 for the page +0xc)
 * when that slot is not -1, loaded with resource 02090e1c (15 entries), and
 * its selected cell (+0xe) is the forward to table 0208fef0's slot or,
 * without one, to cell 2 of the first source.  Manager A (+0x2ab0, handle at
 * +0xbfb0) is initialised with cell 1, two slots, forwarded to table
 * 0208fef1's slot, loaded with resource 02090e30 (27 entries) and forwarded
 * to table 0208fef0's slot (else cell 2).  Handles are
 * (((src + 0x8000) & 0xfffffc) << 7) | 0x80000000 | slot.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;

#define CELL_MASK   0x00fffffc
#define SLOT_MASK   0x1ff
#define CELL_HANDLE(src, cell) (((((src) + 0x8000) & CELL_MASK) << 7) | 0x80000000 | (cell))

typedef struct Ov008SlotManagerCfg {
    u32 handle;               /* 0x00 */
    int nSlots;               /* 0x04 */
    int f8;                   /* 0x08 */
    int fc;                   /* 0x0c */
    int f10;                  /* 0x10 */
    int f14;                  /* 0x14 */
} Ov008SlotManagerCfg;

typedef struct Ov008PanelContext {
    u8  pad_0000[4];
    int cellSrc1;             /* 0x0004 */
    int cellSrc2;             /* 0x0008 */
    s16 nPage;                /* 0x000c */
    u16 nCell;                /* 0x000e */
    u8  pad_0010[0x2ab0 - 0x10];
    u8  managerA[0x7530 - 0x2ab0]; /* 0x2ab0 */
    u8  managerB[0xbfb0 - 0x7530]; /* 0x7530 */
    void *hSlots;             /* 0xbfb0: manager A */
    void *hSlotsB;            /* 0xbfb4: manager B */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov008_02090fac;
extern s8 data_ov008_0208fef0[];                                  /* per page: selected cell (both managers) */
extern s8 data_ov008_0208fef1[];                                  /* per page: manager A first cell */
extern s8 data_ov008_0208fef3[];                                  /* per page: manager B first cell */
extern u8 data_ov008_02090e1c[];                                  /* manager B resource */
extern u8 data_ov008_02090e30[];                                  /* manager A resource */
extern void func_ov008_020542dc(void *pManager, Ov008SlotManagerCfg *pCfg, int nArg, int nSlots); /* InitSubsystemObject */
extern u32  func_0203243c(void *hSlots, u32 nHandle);              /* ForwardTo_02031d90 */
extern void func_ov008_02054678(void *pManager, u8 *pResource, int nCount); /* Ov008_LoadBlockProcessAndFree */

void func_ov008_02082714(void)
{
    Ov008PanelContext *ctx;
    Ov008SlotManagerCfg cfg;
    int nSlot;

    ctx = data_ov008_02090fac;
    cfg.handle = CELL_HANDLE(ctx->cellSrc1, 3);
    cfg.nSlots = 1;
    cfg.f8 = 0;
    cfg.fc = 0;
    cfg.f10 = 0;
    cfg.f14 = 0;
    func_ov008_020542dc(ctx->managerB, &cfg, 0, 1);
    ctx->hSlotsB = ctx->managerB;
    nSlot = data_ov008_0208fef3[ctx->nPage * 4];
    if (nSlot >= 0) {
        func_0203243c(ctx->hSlotsB, CELL_HANDLE(ctx->cellSrc2, nSlot & SLOT_MASK));
    }
    func_ov008_02054678(ctx->managerB, data_ov008_02090e1c, 0xf);
    nSlot = data_ov008_0208fef0[ctx->nPage * 4];
    if (nSlot >= 0) {
        ctx->nCell = func_0203243c(ctx->hSlotsB, CELL_HANDLE(ctx->cellSrc2, nSlot & SLOT_MASK));
    } else {
        ctx->nCell = func_0203243c(ctx->hSlotsB, CELL_HANDLE(ctx->cellSrc1, 2));
    }
    cfg.handle = CELL_HANDLE(ctx->cellSrc1, 1);
    cfg.nSlots = 2;
    cfg.f8 = 0;
    cfg.fc = 0;
    cfg.f10 = 0;
    cfg.f14 = 0;
    func_ov008_020542dc(ctx->managerA, &cfg, 0, 2);
    ctx->hSlots = ctx->managerA;
    nSlot = data_ov008_0208fef1[ctx->nPage * 4];
    if (nSlot >= 0) {
        func_0203243c(ctx->hSlots, CELL_HANDLE(ctx->cellSrc2, nSlot & SLOT_MASK));
    }
    func_ov008_02054678(ctx->managerA, data_ov008_02090e30, 0x1b);
    nSlot = data_ov008_0208fef0[ctx->nPage * 4];
    if (nSlot >= 0) {
        func_0203243c(ctx->hSlots, CELL_HANDLE(ctx->cellSrc2, nSlot & SLOT_MASK));
    } else {
        func_0203243c(ctx->hSlots, CELL_HANDLE(ctx->cellSrc1, 2));
    }
}
