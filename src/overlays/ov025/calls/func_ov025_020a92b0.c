/* func_ov025_020a92b0 -- Ov025_MissionList_Back: the B button on the mission list.  Nothing
 * while it animates (+0x68); a pending selection (+0x4f8) is cancelled instead (+0x4fc cleared,
 * 020a6fec) with the cancel sound (02033b78 0 / 3).  Otherwise, unless the entry gate (+0x40) is
 * up without the transfer acknowledged (+0x44), the session info (data_0204c240: room 10000,
 * the bits cleared) is reset, the mission badge flagged (data_0204c300 +0x4f) and the page left:
 * the menu entirely when the context object (02084dd8) is 1 (ov002 0206d970, target -1 / -1;
 * 02084798), to entry 5 with mission 0 (02084fd8 / 02084830) when the 9630 object is set outside
 * a page transition (02084e08 / 02084e38), else to target 0 / -1; the cancel sound plays. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList {
    u8   pad_000[0x40];
    int  bEntryGate;          /* 0x040 */
    int  bTransferAcked;      /* 0x044 */
    u8   pad_048[0x68 - 0x48];
    int  bAnimating;          /* 0x068 */
    u8   pad_06c[0x4f8 - 0x6c];
    int  bSelectionPending;   /* 0x4f8 */
    int  nField4fc;           /* 0x4fc */
} Ov008MissionList;

typedef struct Ov008SessionInfo {
    u8   nBits;               /* 0x00: bit 1 = client, bit 2 = wireless session */
    u8   nField01;            /* 0x01 */
    u16  nRoom;               /* 0x02: the room number */
    u16  nField04;            /* 0x04 */
} Ov008SessionInfo;

typedef struct Ov008MissionGlobals {
    u8   pad_00[0x4f];
    u8   bBadgeShown;         /* 0x4f */
} Ov008MissionGlobals;

extern Ov008SessionInfo data_0204c240;
extern u8 data_0204c300[];                                          /* Ov008MissionGlobals: +0x4f the badge flag */
extern void  func_ov025_020a6fec(Ov008MissionList *pList, int nArg);  /* Ov025_MissionList_CancelSelection */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern int   func_ov025_02084dd8(void);                             /* Ov008_GetCtxObject95c0 */
extern void  func_ov002_0206d970(int nPayload);                     /* leave the menu */
extern void  func_ov025_02084798(int nEntry, int nTarget);          /* Ov008_SetTargetSlot */
extern int   func_ov025_02084e08(void);                             /* Ov008_GetCtxObject9630 */
extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern void  func_ov025_02084fd8(int nMission);                     /* Ov025_SetCtxField967c */
extern void  func_ov025_02084830(int nEntry);                       /* Ov025_SetGlobalConfigAndInit */

void func_ov025_020a92b0(Ov008MissionList *pList)
{
    if (pList->bAnimating != 0) {
        return;
    }
    if (pList->bSelectionPending != 0) {
        pList->nField4fc = 0;
        func_ov025_020a6fec(pList, 0);
        func_02033b78(0, 3);
        return;
    }
    if (pList->bEntryGate != 0 && pList->bTransferAcked == 0) {
        return;
    }
    data_0204c240.nRoom = 10000;
    data_0204c240.nField04 = 0;
    data_0204c240.nField01 = 0;
    data_0204c240.nBits = 0;
    data_0204c300[0x4f] = 1;
    if (func_ov025_02084dd8() == 1) {
        func_ov002_0206d970(0);
        func_ov025_02084798(-1, -1);
    } else if (func_ov025_02084e08() != 0 && func_ov025_02084e38() == 0) {
        func_ov025_02084fd8(0);
        func_ov025_02084830(5);
    } else {
        func_ov025_02084798(0, -1);
    }
    func_02033b78(0, 3);
}
