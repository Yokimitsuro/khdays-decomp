/* func_ov025_020acd14 -- Ov008_InitMissionMenuTrackers: register the mission
 * menu's four touch trackers in block 954c -- tag 6 (0xe0, 0x40, 0x10 x
 * 0x60, callback 02078160), tag 0xf0 (8, 0x28, 0x50 x 0x10, 02078184), tag
 * 0xf1 (0x58, 0x28, 0x50 x 0x10, 020781b4) and tag 0xf2 (0xa8, 0x28, 0x50 x
 * 0x10, 020781e4), all with mask 0xffff -- unless the transfer flag (+0x150)
 * is set without its ack (+0x154); all four start disabled.  Widgets 0x35
 * and 0x36 of block 4a80 get callbacks 02078214 and 0207825c.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TRACKER_MASK 0xffff
#define WIDGET_A 0x35
#define WIDGET_B 0x36

typedef void (*Ov008ItemCb)(void);

typedef struct Ov008MissionMenu {
    u8  pad_000[0x150];
    int bTransfer;            /* 0x150 */
    int bTransferAcked;       /* 0x154 */
} Ov008MissionMenu;

extern void *func_ov025_02084a64(void);                                   /* Ov008_GetCtxBlock954c */
extern void *func_ov025_020894b0(void *pOwner, int nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov025_020895d0(void *pOwner, void *pEntry, int nX, int nY, int nW, int nH, int nMask, Ov008ItemCb pCallback); /* Ov008_InitAndAppendTracker */
extern void  func_ov025_0208962c(void *pOwner, void *pEntry, int bEnabled); /* SetField20Bit0 */
extern int   func_ov025_02084a8c(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void  func_ov025_02088420(int nCtx, int nId, void *pCallback);     /* Ov008_ResolveEntryStoreWord */
extern void  func_ov025_020ad7b8(void);
extern void  func_ov025_020ad7dc(void);
extern void  func_ov025_020ad80c(void);
extern void  func_ov025_020ad83c(void);
extern void  func_ov025_020ad86c(void);
extern void  func_ov025_020ad8b4(void);

void func_ov025_020acd14(Ov008MissionMenu *pMenu)
{
    void *pOwner;
    int nCtx;

    pOwner = func_ov025_02084a64();
    if (pMenu->bTransfer != 0 && pMenu->bTransferAcked == 0) {
        return;
    }
    func_ov025_020895d0(pOwner, func_ov025_020894b0(pOwner, 6), 0xe0, 0x40, 0x10, 0x60, TRACKER_MASK, func_ov025_020ad7b8);
    func_ov025_020895d0(pOwner, func_ov025_020894b0(pOwner, 0xf0), 8, 0x28, 0x50, 0x10, TRACKER_MASK, func_ov025_020ad7dc);
    func_ov025_020895d0(pOwner, func_ov025_020894b0(pOwner, 0xf1), 0x58, 0x28, 0x50, 0x10, TRACKER_MASK, func_ov025_020ad80c);
    func_ov025_020895d0(pOwner, func_ov025_020894b0(pOwner, 0xf2), 0xa8, 0x28, 0x50, 0x10, TRACKER_MASK, func_ov025_020ad83c);
    func_ov025_0208962c(pOwner, func_ov025_020894b0(pOwner, 6), 0);
    func_ov025_0208962c(pOwner, func_ov025_020894b0(pOwner, 0xf0), 0);
    func_ov025_0208962c(pOwner, func_ov025_020894b0(pOwner, 0xf1), 0);
    func_ov025_0208962c(pOwner, func_ov025_020894b0(pOwner, 0xf2), 0);
    nCtx = func_ov025_02084a8c();
    func_ov025_02088420(nCtx, WIDGET_A, func_ov025_020ad86c);
    func_ov025_02088420(nCtx, WIDGET_B, func_ov025_020ad8b4);
}
