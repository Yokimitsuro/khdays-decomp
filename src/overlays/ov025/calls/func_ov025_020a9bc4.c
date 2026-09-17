/* func_ov025_020a9bc4 -- Ov025_MissionList_StartMission: launch the selected mission (the listed
 * entry of the current id, 02084ff0 / 0208dc54).  The id is kept in data_0204c23c and the menu
 * left into the mission (ov002 0206d970 with the entry's payload); the session info
 * (data_0204c240) takes the payload as room, 0x13 in its second byte and the entry's status
 * (+0x18) in its seventh; flag 0x18ca is cleared, and set again when the 9630 object is up
 * (02084e08), where the session bits become 1, or 3 with the entry's thresholds (+0x20) copied
 * to data_0204c254 during a page transition (02084e38); flag 0x3bc9 + the text slot is set once.
 * Without a transfer (+0x150 of page B) touch is disabled (02084d14) and the jingle 1 / 4 plays
 * (02033fb4), else sound 0 / 1; the target slot becomes -1 / 0x5dc (02084798), or 0 / -1 with
 * flag 0x200a set when the 95c0 object (02084dd8) is 2. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct GameplayThresholdSnapshot {
    u32  words[7];
} GameplayThresholdSnapshot;

typedef struct Ov008MissionListEntry {
    u16  nWord;               /* 0x00: the mission's payload for ov002 */
    u16  missionId;           /* 0x02 */
    u16  nTextSlot;           /* 0x04 */
    u8   pad_06[0x18 - 0x6];
    int  nStatus;             /* 0x18 */
    u8   pad_1c[4];
    GameplayThresholdSnapshot thresholds; /* 0x20 */
} Ov008MissionListEntry;

typedef struct Ov008MissionMenu {
    u8   pad_000[0x150];
    int  bTransfer;           /* 0x150 */
} Ov008MissionMenu;

typedef struct Ov008SessionInfo {
    u8   nBits;               /* 0x00: 0 story, 1 client, 3 wireless host */
    u8   nField01;            /* 0x01 */
    u16  nRoom;               /* 0x02: the mission payload */
    u16  nField04;            /* 0x04 */
    u8   nStatus;             /* 0x06 */
} Ov008SessionInfo;

extern u16   data_0204c23c;                                         /* the current mission id */
extern Ov008SessionInfo data_0204c240;
extern GameplayThresholdSnapshot data_0204c254;
extern Ov008MissionMenu *func_ov025_02084b14(void);                 /* Ov025_GetPageB */
extern u32   func_ov025_02084ff0(void);                             /* Ov008_GetCtxField967c: current mission id */
extern Ov008MissionListEntry *func_ov025_0208dc54(u32 nMissionId);  /* find the listed mission */
extern void  func_ov002_0206d970(int nPayload);                     /* leave the menu into the mission */
extern void  func_020235bc(int nFlag);                              /* GameState_ClearFlag */
extern int   func_ov025_02084e08(void);                             /* Ov008_GetCtxObject9630 */
extern void  func_020235a8(int nFlag);                              /* GameState_SetFlag */
extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern int   func_02023588(int nFlag);                              /* GameState_IsFlagSet */
extern void  func_ov025_02084d14(int bEnabled);                     /* Ov025_SetTouchEnabled */
extern void  func_02033fb4(int nKind, int nSound);                  /* PlayJingle */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern int   func_ov025_02084dd8(void);                             /* Ov008_GetCtxObject95c0 */
extern void  func_ov025_02084798(int nEntry, int nTarget);          /* Ov008_SetTargetSlot */

void func_ov025_020a9bc4(void)
{
    Ov008MissionMenu *pMenu;
    Ov008MissionListEntry *pEntry;

    pMenu = func_ov025_02084b14();
    pEntry = func_ov025_0208dc54(func_ov025_02084ff0());
    if (pEntry != 0) {
        data_0204c23c = func_ov025_02084ff0();
        func_ov002_0206d970(pEntry->nWord);
    }
    data_0204c240.nRoom = pEntry->nWord;
    data_0204c240.nField04 = 0;
    data_0204c240.nField01 = 0x13;
    func_020235bc(0x18ca);
    if (func_ov025_02084e08() != 0) {
        func_020235a8(0x18ca);
        if (func_ov025_02084e38() == 0) {
            data_0204c240.nBits = 1;
            data_0204c240.nStatus = pEntry->nStatus;
        } else {
            data_0204c240.nBits = 3;
            data_0204c240.nStatus = pEntry->nStatus;
            data_0204c254 = pEntry->thresholds;
        }
    } else {
        data_0204c240.nBits = 0;
        data_0204c240.nStatus = pEntry->nStatus;
    }
    if (func_02023588(pEntry->nTextSlot + 0x3bc9) == 0) {
        func_020235a8(pEntry->nTextSlot + 0x3bc9);
    }
    if (pMenu->bTransfer == 0) {
        func_ov025_02084d14(0);
        func_02033fb4(1, 4);
    } else {
        func_02033b78(0, 1);
    }
    if (func_ov025_02084dd8() != 2) {
        func_ov025_02084798(-1, 0x5dc);
    } else {
        func_ov025_02084798(0, -1);
        func_020235a8(0x200a);
    }
}
