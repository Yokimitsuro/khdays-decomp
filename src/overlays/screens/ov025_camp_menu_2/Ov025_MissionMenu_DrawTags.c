/* Ov025_MissionMenu_DrawTags -- Ov008_LayoutMissionBadges: place the mission
 * menu's badge tags for the listed entry of the current mission.  The
 * entry's text slot (+0x4: 0 / 4 always unlocked, else game flag 0x3bc9 +
 * slot) picks its tag from the 0208fb3c table at (2, 2), or the locked tag
 * 0x455.  During a page transition (02051028) the status field of the
 * mission (3 bits at 0x2ca4 + 3 * id with a transfer (+0x150), tags 0x47e
 * .. 0x47b at (0x17, 3), 0x47b notified for 0 / others; else at 0x2a4c +
 * 3 * id: 0x478 notified at (0x15, 3) and (0x16, 3), then 0x47a / 0x479 /
 * 0x478 at (0x18 - (status - 1), 3) for status 1 / 2 / 3, or 0x478 notified
 * at (0x16, 3)).  Otherwise the rank mask (020760f0 of the entry's word)
 * counts the ranks (bits 0 / 1) and the bonus (bit 3); the reward flags (4
 * bits at 0x92b + 4 * id) then decide the three rank tiles at (0x14 + i,
 * 2): rank i below the count shows 0x46a, or 0x46b without its flag; the
 * bonus tile shows 0x46c, or 0x46d without flag 3; an unused tile is 0x46a
 * notified.  Tag 0x475 is notified at (0x16, 3) and the status field
 * (0x28e4 + 3 * id) adds a badge: a special entry (+0xc) or one with flag 2
 * (+0x14) shows 0x475 when cleared (3), 0x480 when started (2) or 0x46f at
 * (0x17, 3); a plain entry shows 0x474 when cleared or 0x47f when started;
 * 0x46e follows at (0x17, 1).  Finally the tier (0205b988) -- 0 when the
 * mission is not started with nothing cleared (0205b974) counting its
 * weight (+0x15), when 12 are cleared, without the object (02050ff8) while
 * +0x17c is set, with it when the mission is started, or during a
 * transition -- picks the tier tag of 0208fa28 at (0x1c, 3); tier 0 invokes
 * tag 0xf and marks 0204c300 +0x4f, other tiers invoke tag 3.  Codegen: the
 * two tag tables are struct copies; the menu pointer, the transition and
 * object flags are spilled; the entry is declared before the owner; the
 * field index (id * 3) is written inline in both transition branches so
 * the bit count 3 hoists above the branch; the rank / bonus counters are
 * u8 increments; the tile loop index is unsigned with signed compares
 * against the count, its tags picked by if / else and derived from the
 * pool constant 0x46d; the status tests are bool locals; the transition
 * branch is written first; the tier's byte store is a second test after
 * the callback if / else.
 */

#include "nitro/types.h"

#define FLAG_TEXT_SLOT_BASE 0x3bc9
#define FIELD_MISSION_STATUS 0x28e4
#define FIELD_MISSION_TRANSFER 0x2ca4
#define FIELD_MISSION_STAGE 0x2a4c
#define FIELD_MISSION_REWARDS 0x92b
#define TAG_LOCKED      0x455
#define TAG_RANK_DONE   0x46a
#define TAG_RANK_OPEN   0x46b
#define TAG_BONUS_DONE  0x46c
#define TAG_BONUS_OPEN  0x46d
#define TAG_FOLLOW      0x46e
#define TAG_STARTED_ALT 0x46f
#define TAG_CLEARED_PLAIN 0x474
#define TAG_BADGE       0x475
#define TAG_STAGE       0x478
#define TAG_STAGE_2     0x479
#define TAG_STAGE_1     0x47a
#define TAG_TRANSFER_0  0x47b
#define TAG_TRANSFER_3  0x47c
#define TAG_TRANSFER_2  0x47d
#define TAG_TRANSFER_1  0x47e
#define TAG_STARTED_PLAIN 0x47f
#define TAG_STARTED     0x480
#define RANK_TILES      3
#define TILE_X_FIRST    0x14
#define CLEARED_ALL     12

typedef struct Ov008MissionListEntry {
    u16 nFileNumber;                /* 0x00 */
    u16 missionId;            /* 0x02 */
    u16 nCategory;            /* 0x04 */
    u8  pad_06[6];
    u8  bSpecial;             /* 0x0c */
    u8  pad_0d[7];
    u8  nFlags;               /* 0x14 */
    u8  completionWeight;     /* 0x15 */
} Ov008MissionListEntry;

typedef struct Ov008MissionMenu {
    u8  pad_000[0x150];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x17c - 0x154];
    int bAllLocked;           /* 0x17c */
} Ov008MissionMenu;

typedef struct Ov008SlotTags {
    u32 aTag[12];
} Ov008SlotTags;

typedef struct Ov008RankTags {
    u32 aTag[4];
} Ov008RankTags;

typedef struct Ov008MissionGlobals {
    u8  pad_00[0x4f];
    u8  bBadgeShown;          /* 0x4f */
} Ov008MissionGlobals;

extern const Ov008SlotTags data_ov025_020b47ec;
extern const Ov008RankTags data_ov025_020b46d8;
extern Ov008MissionGlobals data_0204c300;
extern int   Ov025_GetCtxBlock954c(void);                                  /* Ov008_GetCtxBlock954c */
extern u32   Ov025_GetCtxField967c(void);                                  /* Ov008_GetCtxField967c: current mission id */
extern Ov008MissionListEntry *Ov025_GetNextMissionEntry_5(u32 nMissionId);       /* find the listed mission */
extern int   Ov025_GetCtxObject9630(void);                                  /* Ov008_GetCtxObject9630 */
extern int   Ov025_GetCtxObject9634(void);                                  /* Ov008_GetCtxObject9634: page transition */
extern int   GameState_IsFlagSet(int nFlag);                                   /* GameState_IsFlagSet */
extern void  Ov025_ApplyTempFieldsByTag(int nOwner, u32 nTag, int nX, int nY); /* Ov008_SetTagValueDup */
extern void  Ov025_ConfigureEntryByTag_2(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueAndNotify */
extern u32   GameState_GetField(int nField, int nBits);                       /* GameState_GetField */
extern u32   Ov025_BuildBadgeMask2(Ov008MissionMenu *pMenu, u32 nWord);    /* Ov008_BuildBadgeMask2 */
extern u8    Ov025_UpdateMissionSummaryTier(Ov008MissionListEntry *pEntry);         /* Ov008_UpdateMissionSummaryTier */
extern unsigned char   Ov025_GetPageAByte14F3(void);                                  /* cleared mission count */
extern void *Ov025_FindEntryByTag(int nOwner, int nTag);                  /* ov008_FindEntryByTag */
extern void  Ov025_TagTracker_InvokeCallback(int nOwner, void *pEntry);              /* Ov008_TagTracker_InvokeCallback */

void Ov025_MissionMenu_DrawTags(Ov008MissionMenu *pMenu)
{
    Ov008SlotTags tags;
    Ov008RankTags tierTags;
    Ov008MissionListEntry *pEntry;
    int nOwner;
    int bObject;
    int bTransition;
    int bUnlocked;
    u32 nStage;
    int nY;
    u32 nMask;
    u8 nRanks;
    u8 nBonus;
    u8 nRewards;
    u32 i;
    u32 nTag;
    int bCleared;
    int bStarted;
    int nTier;
    int nCleared;

    nOwner = Ov025_GetCtxBlock954c();
    pEntry = Ov025_GetNextMissionEntry_5(Ov025_GetCtxField967c());
    bObject = Ov025_GetCtxObject9630();
    bTransition = Ov025_GetCtxObject9634();
    tags = data_ov025_020b47ec;
    if (pEntry->nCategory == 0) {
        bUnlocked = 1;
    } else if (pEntry->nCategory == 4) {
        bUnlocked = 1;
    } else {
        bUnlocked = GameState_IsFlagSet(pEntry->nCategory + FLAG_TEXT_SLOT_BASE);
    }
    if (bUnlocked == 0) {
        Ov025_ApplyTempFieldsByTag(nOwner, TAG_LOCKED, (short)2, (short)2);
    } else {
        Ov025_ApplyTempFieldsByTag(nOwner, tags.aTag[pEntry->nCategory], (short)2, (short)2);
    }
    if (bTransition != 0) {
        if (pMenu->bTransfer != 0) {
            switch (GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_TRANSFER, 3)) {
            case 1:
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_TRANSFER_1, (short)0x17, (short)3);
                break;
            case 2:
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_TRANSFER_2, (short)0x17, (short)3);
                break;
            case 3:
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_TRANSFER_3, (short)0x17, (short)3);
                break;
            case 4:
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_TRANSFER_0, (short)0x17, (short)3);
                break;
            case 0:
            default:
                Ov025_ConfigureEntryByTag_2(nOwner, TAG_TRANSFER_0, 0x17, 3);
                break;
            }
        } else {
            nStage = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STAGE, 3);
            nY = 0x18 - (nStage - 1);
            Ov025_ConfigureEntryByTag_2(nOwner, TAG_STAGE, 0x15, 3);
            Ov025_ConfigureEntryByTag_2(nOwner, TAG_STAGE, 0x16, 3);
            switch (nStage) {
            case 1:
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_STAGE_1, (short)nY, (short)3);
                break;
            case 2:
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_STAGE_2, (short)nY, (short)3);
                break;
            case 3:
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_STAGE, (short)nY, (short)3);
                break;
            default:
                Ov025_ConfigureEntryByTag_2(nOwner, TAG_STAGE, 0x16, 3);
                break;
            }
        }
    } else {
        GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3);
        nMask = Ov025_BuildBadgeMask2(pMenu, pEntry->nFileNumber);
        nRanks = 0;
        if (nMask & 1) {
            nRanks++;
        }
        if (nMask & 2) {
            nRanks++;
        }
        nBonus = 0;
        if (nMask & 8) {
            nBonus++;
        }
        nRewards = GameState_GetField(pEntry->missionId * 4 + FIELD_MISSION_REWARDS, 4);
        for (i = 0; (int)i < RANK_TILES; i++) {
            nTag = -1;
            if (i <= 1) {
                if ((int)i < nRanks) {
                    if (nRewards & (1 << i)) {
                        nTag = TAG_RANK_DONE;
                    } else {
                        nTag = TAG_RANK_OPEN;
                    }
                }
            } else if (i == 2) {
                if (nBonus != 0) {
                    if (nRewards & (1 << (i + 1))) {
                        nTag = TAG_BONUS_DONE;
                    } else {
                        nTag = TAG_BONUS_OPEN;
                    }
                }
            }
            if (nTag != -1) {
                Ov025_ApplyTempFieldsByTag(nOwner, nTag, (short)(i + TILE_X_FIRST), (short)2);
            } else {
                Ov025_ConfigureEntryByTag_2(nOwner, TAG_RANK_DONE, (short)(i + TILE_X_FIRST), 2);
            }
        }
        Ov025_ConfigureEntryByTag_2(nOwner, TAG_BADGE, 0x16, 3);
        if (pEntry->bSpecial != 0 || (pEntry->nFlags & 2)) {
            bCleared = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) == 3;
            if (bCleared) {
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_BADGE, (short)0x16, (short)3);
            } else {
                bStarted = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
                if (bStarted) {
                    Ov025_ApplyTempFieldsByTag(nOwner, TAG_STARTED, (short)0x16, (short)3);
                } else {
                    Ov025_ApplyTempFieldsByTag(nOwner, TAG_STARTED_ALT, (short)0x17, (short)3);
                }
            }
        } else {
            bCleared = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) == 3;
            if (bCleared) {
                Ov025_ApplyTempFieldsByTag(nOwner, TAG_CLEARED_PLAIN, (short)0x16, (short)3);
            } else {
                bStarted = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
                if (bStarted) {
                    Ov025_ApplyTempFieldsByTag(nOwner, TAG_STARTED_PLAIN, (short)0x16, (short)3);
                }
            }
        }
        Ov025_ApplyTempFieldsByTag(nOwner, TAG_FOLLOW, (short)0x17, (short)1);
    }
    tierTags = data_ov025_020b46d8;
    nTier = Ov025_UpdateMissionSummaryTier(pEntry);
    nCleared = Ov025_GetPageAByte14F3();
    if ((int)GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) < 2 && nCleared + pEntry->completionWeight == 0) {
        nTier = 0;
    }
    if (nCleared == CLEARED_ALL) {
        nTier = 0;
    }
    if (bObject == 0 && pMenu->bAllLocked != 0) {
        nTier = 0;
    }
    if (bObject != 0) {
        bStarted = GameState_GetField(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
        if (bStarted) {
            nTier = 0;
        }
    }
    if (bTransition != 0) {
        nTier = 0;
    }
    Ov025_ApplyTempFieldsByTag(nOwner, tierTags.aTag[nTier], (short)0x1c, (short)3);
    if (nTier == 0) {
        Ov025_TagTracker_InvokeCallback(nOwner, Ov025_FindEntryByTag(nOwner, 0xf));
    } else {
        Ov025_TagTracker_InvokeCallback(nOwner, Ov025_FindEntryByTag(nOwner, 3));
    }
    if (nTier == 0) {
        data_0204c300.bBadgeShown = 1;
    }
}
