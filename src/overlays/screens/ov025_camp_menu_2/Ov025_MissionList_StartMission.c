/* Ov025_MissionList_StartMission -- Ov025_MissionList_StartMission: launch the selected mission (the listed
 * entry of the current id, 02084ff0 / 0208dc54).  The id is kept in data_0204c23c and the menu
 * left into the mission (ov002 0206d970 with the entry's payload); the session info
 * (data_0204c240) takes the payload as room, 0x13 in its second byte and the entry's status
 * (+0x18) in its seventh; flag 0x18ca is cleared, and set again when the 9630 object is up
 * (02084e08), where the session bits become 1, or 3 with the entry's thresholds (+0x20) copied
 * to data_0204c254 during a page transition (02084e38); flag 0x3bc9 + the text slot is set once.
 * Without a transfer (+0x150 of page B) touch is disabled (02084d14) and the jingle 1 / 4 plays
 * (02033fb4), else sound 0 / 1; the target slot becomes -1 / 0x5dc (02084798), or 0 / -1 with
 * flag 0x200a set when the 95c0 object (02084dd8) is 2. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct GameplayThresholdSnapshot {
    u32  words[7];
} GameplayThresholdSnapshot;

typedef struct Ov008MissionListEntry {
    u16  nFileNumber;               /* 0x00: the mission's payload for ov002 */
    u16  missionId;           /* 0x02 */
    u16  nCategory;           /* 0x04 */
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
extern Ov008MissionMenu *Ov025_GetPageB(void);                 /* Ov025_GetPageB */
extern u32   Ov025_GetCtxField967c(void);                             /* Ov008_GetCtxField967c: current mission id */
extern Ov008MissionListEntry *Ov025_GetNextMissionEntry_5(u32 nMissionId);  /* find the listed mission */
extern void  Ov002_PostResultReport(int nPayload);                     /* leave the menu into the mission */
extern int   Ov025_GetCtxObject9630(void);                             /* Ov008_GetCtxObject9630 */
extern int   Ov025_GetCtxObject9634(void);                             /* Ov025_GetCtxObject9634: page transition */
extern void  Ov025_CampaignModeHookNoOp(int bEnabled);                     /* Ov025_SetTouchEnabled */
extern int   Ov025_GetCtxObject95c0(void);                             /* Ov008_GetCtxObject95c0 */
extern void  Ov025_SetTargetSlot(int nEntry, int nTarget);          /* Ov008_SetTargetSlot */

void Ov025_MissionList_StartMission(void)
{
    Ov008MissionMenu *pMenu;
    Ov008MissionListEntry *pEntry;

    pMenu = Ov025_GetPageB();
    pEntry = Ov025_GetNextMissionEntry_5(Ov025_GetCtxField967c());
    if (pEntry != 0) {
        data_0204c23c = Ov025_GetCtxField967c();
        Ov002_PostResultReport(pEntry->nFileNumber);
    }
    data_0204c240.nRoom = pEntry->nFileNumber;
    data_0204c240.nField04 = 0;
    data_0204c240.nField01 = 0x13;
    GameState_ClearFlag(0x18ca);
    if (Ov025_GetCtxObject9630() != 0) {
        GameState_SetFlag(0x18ca);
        if (Ov025_GetCtxObject9634() == 0) {
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
    if (GameState_IsFlagSet(pEntry->nCategory + 0x3bc9) == 0) {
        GameState_SetFlag(pEntry->nCategory + 0x3bc9);
    }
    if (pMenu->bTransfer == 0) {
        Ov025_CampaignModeHookNoOp(0);
        StampByteAndInvokeSubStructAt(1, 4);
    } else {
        PlaySound(0, 1);
    }
    if (Ov025_GetCtxObject95c0() != 2) {
        Ov025_SetTargetSlot(-1, 0x5dc);
    } else {
        Ov025_SetTargetSlot(0, -1);
        GameState_SetFlag(0x200a);
    }
}
