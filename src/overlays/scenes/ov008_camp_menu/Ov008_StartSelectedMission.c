/* Ov008_StartSelectedMission -- Ov008_StartSelectedMission: commit the mission named by
 * the context.  Records its id (data_0204c23c) when it is listed, fills the game
 * mode record (mission entry word, timer 0, sub 0x13, flags 0xf or 7 in a
 * session, mission kind byte) and copies the entry's seven threshold words, sets
 * the mission's unlock flag (0x3bc9 + slot) if not yet set, plays the start cue
 * (enabling the sound layer when the page has not yet) and, depending on the
 * ctx object 95c0, either targets slot 0 and sets flag 0x200a or targets no
 * slot with 0x5dc.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov008MissionListEntry {
    u16 nWord;                /* 0x00 */
    u8  pad_02[2];
    u16 nCategory;                /* 0x04 */
    u8  pad_06[0x18 - 0x06];
    int nKind;                /* 0x18 */
    u8  pad_1c[4];
    u32 aThreshold[7];        /* 0x20 */
} Ov008MissionListEntry;

typedef struct GameplayThresholdSnapshot {
    u32 words[7];
} GameplayThresholdSnapshot;

typedef struct GameMode {
    u8  nFlags;               /* 0x00 */
    u8  nSub;                 /* 0x01 */
    u16 nWord;                /* 0x02 */
    u16 nTimer;               /* 0x04 */
    u8  nKind;                /* 0x06 */
} GameMode;

typedef struct Ov008PageB {
    u8  pad_000[0x150];
    int bSoundReady;          /* 0x150 */
} Ov008PageB;

#define FLAG_SLOT_BASE 0x3bc9
#define FLAG_TARGET_ANY 0x5dc
#define FLAG_TARGET_SLOT0 0x200a
#define MODE_SUB_MISSION 0x13

extern u16 data_0204c23c;                                  /* current mission id */
extern GameMode data_0204c240;
extern GameplayThresholdSnapshot data_0204c254;

extern Ov008PageB *Ov008_GetPageB(void);              /* Ov008_GetPageB */
extern u32  Ov008_GetCtxField967c(void);                     /* Ov008_GetCtxField967c */
extern Ov008MissionListEntry *Ov008_GetNextMissionEntry_5(u32 nMissionId);
extern void Ov008_CampaignModeHookNoOp(int bEnable);
extern int  Ov008_GetCtxObject95c0(void);                     /* Ov008_GetCtxObject95c0 */
extern void Ov008_SetTargetSlot(int nEntry, int nTarget);  /* Ov008_SetTargetSlot */

void Ov008_StartSelectedMission(void)
{
    Ov008PageB *pPage = Ov008_GetPageB();
    Ov008MissionListEntry *pEntry;

    pEntry = Ov008_GetNextMissionEntry_5(Ov008_GetCtxField967c());
    if (pEntry != 0) {
        data_0204c23c = Ov008_GetCtxField967c();
    }
    data_0204c240.nWord = pEntry->nWord;
    data_0204c240.nTimer = 0;
    data_0204c240.nSub = MODE_SUB_MISSION;
    data_0204c240.nFlags = Session_IsActive() != 0 ? 7 : 0xf;
    data_0204c240.nKind = pEntry->nKind;
    data_0204c254 = *(GameplayThresholdSnapshot *)pEntry->aThreshold;
    if (GameState_IsFlagSet(pEntry->nCategory + FLAG_SLOT_BASE) == 0) {
        GameState_SetFlag(pEntry->nCategory + FLAG_SLOT_BASE);
    }
    if (pPage->bSoundReady == 0) {
        Ov008_CampaignModeHookNoOp(0);
        StampByteAndInvokeSubStructAt(1, 4);
    } else {
        PlaySound(0, 1);
    }
    if (Ov008_GetCtxObject95c0() != 2) {
        Ov008_SetTargetSlot(-1, FLAG_TARGET_ANY);
        return;
    }
    Ov008_SetTargetSlot(0, -1);
    GameState_SetFlag(FLAG_TARGET_SLOT0);
}
