/* func_ov008_020776bc -- Ov008_InitMissionMenuTrackers: register the mission
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

extern void *func_ov008_02050c3c(void);                                   /* Ov008_GetCtxBlock954c */
extern void *func_ov008_02055808(void *pOwner, int nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov008_020559c0(void *pOwner, void *pEntry, int nX, int nY, int nW, int nH, int nMask, Ov008ItemCb pCallback); /* Ov008_InitAndAppendTracker */
extern void  func_ov008_02055a1c(void *pOwner, void *pEntry, int bEnabled); /* SetField20Bit0 */
extern int   func_ov008_02050c64(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void  func_ov008_0205476c(int nCtx, int nId, void *pCallback);     /* Ov008_ResolveEntryStoreWord */
extern void  func_ov008_02078160(void);
extern void  func_ov008_02078184(void);
extern void  func_ov008_020781b4(void);
extern void  func_ov008_020781e4(void);
extern void  func_ov008_02078214(void);
extern void  func_ov008_0207825c(void);

void func_ov008_020776bc(Ov008MissionMenu *pMenu)
{
    void *pOwner;
    int nCtx;

    pOwner = func_ov008_02050c3c();
    if (pMenu->bTransfer != 0 && pMenu->bTransferAcked == 0) {
        return;
    }
    func_ov008_020559c0(pOwner, func_ov008_02055808(pOwner, 6), 0xe0, 0x40, 0x10, 0x60, TRACKER_MASK, func_ov008_02078160);
    func_ov008_020559c0(pOwner, func_ov008_02055808(pOwner, 0xf0), 8, 0x28, 0x50, 0x10, TRACKER_MASK, func_ov008_02078184);
    func_ov008_020559c0(pOwner, func_ov008_02055808(pOwner, 0xf1), 0x58, 0x28, 0x50, 0x10, TRACKER_MASK, func_ov008_020781b4);
    func_ov008_020559c0(pOwner, func_ov008_02055808(pOwner, 0xf2), 0xa8, 0x28, 0x50, 0x10, TRACKER_MASK, func_ov008_020781e4);
    func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 6), 0);
    func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 0xf0), 0);
    func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 0xf1), 0);
    func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 0xf2), 0);
    nCtx = func_ov008_02050c64();
    func_ov008_0205476c(nCtx, WIDGET_A, func_ov008_02078214);
    func_ov008_0205476c(nCtx, WIDGET_B, func_ov008_0207825c);
}
