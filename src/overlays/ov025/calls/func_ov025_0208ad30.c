/* func_ov025_0208ad30 -- show or hide the hub's sub-menu, ov025. Stores the state at +0x5c0, sets
 * the visibility of entries 7 and 8 and pushes the state to the sub-item sets of entries 1..6.
 * Showing: the tag-2 marker's callback runs, entries 0x10..0x12, 0xe and 0xf are hidden, the
 * sub-menu caption (text record 0x15) is drawn at (10, 0), entry 0x15's first valid slot is saved
 * to +0x5c4, entry 8 takes the parameter overrides and the hover (0x80) and becomes current
 * (+0x88, the hovered id), and entry 9's sub-items follow the state. Hiding: the hub entries are re-initialised,
 * entry 9's sub-items and the 0208acd8 refresh follow, entries 0x10..0x12, 0xe and 0xf are shown
 * again, entry 0x15 gets its saved slots back and entry 9 takes the overrides, the hover and the
 * focus. */
typedef unsigned char u8;

typedef struct Ov025HubScene {
    int nField00;                       /* +0x000 */
    u8 strings[0xc];                    /* +0x004: the hub string set */
    u8 surfaceTitle[0x3c];              /* +0x010 */
    u8 surfaceBody[0x3c];               /* +0x04c */
    int nHoverId;                       /* +0x088: the hovered entry id */
    u8 pad08c[0x5c0 - 0x8c];
    int bSubMenu;                       /* +0x5c0 */
    u8 savedSlots[8];                   /* +0x5c4: entry 0x15's slots while the sub-menu is open */
} Ov025HubScene;

extern int func_ov025_02084a50(void);                                   /* tag tracker */
extern int func_ov025_02084a7c(void);                                   /* entry context */
extern void *func_ov025_0208843c(int nCtx, int nId);                    /* FindEntryById */
extern void func_ov025_0208884c(int nCtx, void *pEntry, int bVisible);  /* SetEntrySlotsVisible */
extern void func_ov025_020887c0(int nCtx, void *pEntry, int nValue);    /* PushSubitemSet */
extern void *func_ov025_020894b0(int nTracker, int nTag);               /* FindEntryByTag */
extern void func_ov025_02089544(int nTracker, void *pCell);             /* invoke the tag callback */
extern void *func_ov025_02089894(void *pRecords, int nIndex);           /* GetVarRecordByIndex */
extern void func_02030158(void *pSurface);                              /* TileSurface_Clear */
extern void func_02030278(void *pSurface, int nX, int nY, int nColour, void *pText, int nFlag);
extern void func_020300f8(void *pSurface);
extern void *func_ov025_020884c8(int nCtx, void *pEntry);               /* first valid slot */
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void func_ov025_0208896c(int nCtx, void *pEntry);                /* swap parameter overrides */
extern void func_ov025_0208bf68(void *pEntry, int nFlags);              /* hover */
extern void func_ov025_0208b7d0(Ov025HubScene *pScene);                 /* init the hub entries */
extern void func_ov025_0208acd8(void);
extern void func_ov025_02088500(int nCtx, void *pEntry, void *pSlots);  /* release two slots */

void func_ov025_0208ad30(Ov025HubScene *pScene, int bShow)
{
    int nTracker = func_ov025_02084a50();
    int nCtx = func_ov025_02084a7c();

    pScene->bSubMenu = bShow;
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 7), bShow);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 8), bShow);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 1), bShow);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 2), bShow);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 3), bShow);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 4), bShow);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 5), bShow);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 6), bShow);
    if (bShow) {
        void *pText;

        func_ov025_02089544(nTracker, func_ov025_020894b0(nTracker, 2));
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x10), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x11), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x12), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0xe), 0);
        func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0xf), 0);
        pText = func_ov025_02089894(pScene->strings, 0x15);
        func_02030158(pScene->surfaceBody);
        func_02030278(pScene->surfaceBody, 10, 0, 2, pText, 1);
        func_020300f8(pScene->surfaceBody);
        MI_CpuCopy8(func_ov025_020884c8(nCtx, func_ov025_0208843c(nCtx, 0x15)), pScene->savedSlots, 8);
        func_ov025_0208896c(nCtx, func_ov025_0208843c(nCtx, 8));
        pScene->nHoverId = 8;
        func_ov025_0208bf68(func_ov025_0208843c(nCtx, 8), 0x80);
        func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 9), bShow);
        return;
    }
    func_ov025_0208b7d0(pScene);
    func_ov025_020887c0(nCtx, func_ov025_0208843c(nCtx, 9), bShow);
    func_ov025_0208acd8();
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x10), 1);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x11), 1);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0x12), 1);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0xe), 1);
    func_ov025_0208884c(nCtx, func_ov025_0208843c(nCtx, 0xf), 1);
    func_ov025_02088500(nCtx, func_ov025_0208843c(nCtx, 0x15), pScene->savedSlots);
    func_ov025_0208896c(nCtx, func_ov025_0208843c(nCtx, 9));
    pScene->nHoverId = 9;
    func_ov025_0208bf68(func_ov025_0208843c(nCtx, 9), 0x80);
}
