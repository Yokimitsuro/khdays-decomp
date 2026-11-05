/* Ov026_InitPanelSlotManagers -- Ov008_InitPanelSlotManagers: create the panel
 * context's two slot managers.  Manager B (+0x7530, handle kept at +0xbfb4)
 * is initialised with cell 3 of the first source (+0x4), one slot, forwarded
 * to cell (second source +0x8, slot from table 0208fef3 for the page +0xc)
 * when that slot is not -1, loaded with resource 02090e1c (15 entries), and
 * its selected cell (+0xe) is the forward to table 0208fef0's slot or,
 * without one, to cell 2 of the first source.  Manager A (+0x2ab0, handle at
 * +0xbfb0) is initialised with cell 1, two slots, forwarded to table
 * 0208fef1's slot, loaded with resource 02090e30 (27 entries) and forwarded
 * to table 0208fef0's slot (else cell 2).  Handles are
 * ARCHIVE_HANDLE(src, slot) (game/archive.h).
 */

#include "nitro/types.h"
#include "game/archive.h"

#define SLOT_MASK   0x1ff

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
    int pContainerA;             /* 0x0004: ui/shop/res.p2 container */
    int pContainerB;             /* 0x0008: ui/shop/res_i18n.p2 container */
    s16 nPage;                /* 0x000c */
    u16 nCell;                /* 0x000e */
    u8  pad_0010[0x2ab0 - 0x10];
    u8  managerA[0x7530 - 0x2ab0]; /* 0x2ab0 */
    u8  managerB[0xbfb0 - 0x7530]; /* 0x7530 */
    void *hSlots;             /* 0xbfb0: manager A */
    void *hSlotsB;            /* 0xbfb4: manager B */
} Ov008PanelContext;

extern Ov008PanelContext *data_ov026_02091368;
extern s8 data_ov026_02091148[];                                  /* per page: selected cell (both managers) */
extern s8 data_ov026_02091149[];                                  /* per page: manager A first cell */
extern s8 data_ov026_0209114b[];                                  /* per page: manager B first cell */
extern u8 gOv026UiShopSpUoPath[];                                  /* manager B resource */
extern u8 gOv026UiShopSpLoPath[];                                  /* manager A resource */
extern void Ov026_InitSubsystemObject(void *pManager, Ov008SlotManagerCfg *pCfg, int nArg, int nSlots); /* InitSubsystemObject */
extern u32  DispObjList_AddResource(void *hSlots, u32 nHandle);
extern void Ov026_LoadBlockProcessAndFree(void *pManager, u8 *pResource, int nCount); /* Ov008_LoadBlockProcessAndFree */

void Ov026_InitPanelSlotManagers(void)
{
    Ov008PanelContext *ctx;
    Ov008SlotManagerCfg cfg;
    int nSlot;

    ctx = data_ov026_02091368;
    cfg.handle = ARCHIVE_HANDLE(ctx->pContainerA, 3);
    cfg.nSlots = 1;
    cfg.f8 = 0;
    cfg.fc = 0;
    cfg.f10 = 0;
    cfg.f14 = 0;
    Ov026_InitSubsystemObject(ctx->managerB, &cfg, 0, 1);
    ctx->hSlotsB = ctx->managerB;
    nSlot = data_ov026_0209114b[ctx->nPage * 4];
    if (nSlot >= 0) {
        DispObjList_AddResource(ctx->hSlotsB, ARCHIVE_HANDLE(ctx->pContainerB, nSlot & SLOT_MASK));
    }
    Ov026_LoadBlockProcessAndFree(ctx->managerB, gOv026UiShopSpUoPath, 0xf);
    nSlot = data_ov026_02091148[ctx->nPage * 4];
    if (nSlot >= 0) {
        ctx->nCell = DispObjList_AddResource(ctx->hSlotsB, ARCHIVE_HANDLE(ctx->pContainerB, nSlot & SLOT_MASK));
    } else {
        ctx->nCell = DispObjList_AddResource(ctx->hSlotsB, ARCHIVE_HANDLE(ctx->pContainerA, 2));
    }
    cfg.handle = ARCHIVE_HANDLE(ctx->pContainerA, 1);
    cfg.nSlots = 2;
    cfg.f8 = 0;
    cfg.fc = 0;
    cfg.f10 = 0;
    cfg.f14 = 0;
    Ov026_InitSubsystemObject(ctx->managerA, &cfg, 0, 2);
    ctx->hSlots = ctx->managerA;
    nSlot = data_ov026_02091149[ctx->nPage * 4];
    if (nSlot >= 0) {
        DispObjList_AddResource(ctx->hSlots, ARCHIVE_HANDLE(ctx->pContainerB, nSlot & SLOT_MASK));
    }
    Ov026_LoadBlockProcessAndFree(ctx->managerA, gOv026UiShopSpLoPath, 0x1b);
    nSlot = data_ov026_02091148[ctx->nPage * 4];
    if (nSlot >= 0) {
        DispObjList_AddResource(ctx->hSlots, ARCHIVE_HANDLE(ctx->pContainerB, nSlot & SLOT_MASK));
    } else {
        DispObjList_AddResource(ctx->hSlots, ARCHIVE_HANDLE(ctx->pContainerA, 2));
    }
}
