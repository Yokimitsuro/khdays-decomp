/* func_ov008_020729dc -- Ov008_InitMissionListTrackers: register the mission
 * list's three touch trackers in block 954c -- tag 0 (0x10, 0x30, 0xe0 x
 * 0x80, callback 02073e58), tag 1 (8, 8, 0x48 x 0x20, 02073f44) and tag 2
 * (0x10, 0x10, 0xe0 x 0xa0, 02073e58), all with mask 0xffff -- unless the
 * entry gate (+0x40) is set without the transfer ack (+0x44).  With context
 * object 9634 present tag 2 is disabled and tags 0 / 1 enabled, otherwise
 * tags 0 / 1 are disabled and tag 2 enabled.  Widgets 0x35 and 0x36 of block
 * 4a80 get callbacks 02073fe8 and 0207403c.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define TRACKER_MASK 0xffff
#define WIDGET_A 0x35
#define WIDGET_B 0x36

typedef void (*Ov008ItemCb)(void);

typedef struct Ov008MissionList {
    u8  pad_00[0x40];
    int bEntryGate;           /* 0x40 */
    int bTransferAcked;       /* 0x44 */
} Ov008MissionList;

extern void *func_ov008_02050c3c(void);                                   /* Ov008_GetCtxBlock954c */
extern void *func_ov008_02055808(void *pOwner, int nTag);                 /* ov008_FindEntryByTag */
extern void  func_ov008_020559c0(void *pOwner, void *pEntry, int nX, int nY, int nW, int nH, int nMask, Ov008ItemCb pCallback); /* Ov008_InitAndAppendTracker */
extern int   func_ov008_02051028(void);                                   /* Ov008_GetCtxObject9634 */
extern void  func_ov008_02055a1c(void *pOwner, void *pEntry, int bEnabled); /* SetField20Bit0 */
extern int   func_ov008_02050c64(void);                                   /* Ov008_GetCtxBlock4a80 */
extern void  func_ov008_0205476c(int nCtx, int nId, void *pCallback);     /* Ov008_ResolveEntryStoreWord */
extern void  func_ov008_02073e58(void);
extern void  func_ov008_02073f44(void);
extern void  func_ov008_02073fe8(void);
extern void  func_ov008_0207403c(void);

void func_ov008_020729dc(Ov008MissionList *pList)
{
    void *pOwner;
    int nCtx;

    pOwner = func_ov008_02050c3c();
    if (pList->bEntryGate != 0 && pList->bTransferAcked == 0) {
        return;
    }
    func_ov008_020559c0(pOwner, func_ov008_02055808(pOwner, 0), 0x10, 0x30, 0xe0, 0x80, TRACKER_MASK, func_ov008_02073e58);
    func_ov008_020559c0(pOwner, func_ov008_02055808(pOwner, 1), 8, 8, 0x48, 0x20, TRACKER_MASK, func_ov008_02073f44);
    func_ov008_020559c0(pOwner, func_ov008_02055808(pOwner, 2), 0x10, 0x10, 0xe0, 0xa0, TRACKER_MASK, func_ov008_02073e58);
    if (func_ov008_02051028() != 0) {
        func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 2), 0);
        func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 0), 1);
        func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 1), 1);
    } else {
        func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 0), 0);
        func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 1), 0);
        func_ov008_02055a1c(pOwner, func_ov008_02055808(pOwner, 2), 1);
    }
    nCtx = func_ov008_02050c64();
    func_ov008_0205476c(nCtx, WIDGET_A, func_ov008_02073fe8);
    func_ov008_0205476c(nCtx, WIDGET_B, func_ov008_0207403c);
}
