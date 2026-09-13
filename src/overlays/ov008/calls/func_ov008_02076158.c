/* func_ov008_02076158 -- Ov008_LayoutMissionBadges: place the mission
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
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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
    u16 nWord;                /* 0x00 */
    u16 missionId;            /* 0x02 */
    u16 nTextSlot;            /* 0x04 */
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

extern const Ov008SlotTags data_ov008_0208fb3c;
extern const Ov008RankTags data_ov008_0208fa28;
extern Ov008MissionGlobals data_0204c300;
extern int   func_ov008_02050c3c(void);                                  /* Ov008_GetCtxBlock954c */
extern u32   func_ov008_020511e0(void);                                  /* Ov008_GetCtxField967c: current mission id */
extern Ov008MissionListEntry *func_ov008_0205b6e8(u32 nMissionId);       /* find the listed mission */
extern int   func_ov008_02050ff8(void);                                  /* Ov008_GetCtxObject9630 */
extern int   func_ov008_02051028(void);                                  /* Ov008_GetCtxObject9634: page transition */
extern int   func_02023588(int nFlag);                                   /* GameState_IsFlagSet */
extern void  func_ov008_020744a0(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueDup */
extern void  func_ov008_0207451c(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueAndNotify */
extern u32   func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern u32   func_ov008_020760f0(Ov008MissionMenu *pMenu, u32 nWord);    /* Ov008_BuildRankMask2 */
extern u8    func_ov008_0205b988(Ov008MissionListEntry *pEntry);         /* Ov008_UpdateMissionSummaryTier */
extern int   func_ov008_0205b974(void);                                  /* cleared mission count */
extern void *func_ov008_02055808(int nOwner, int nTag);                  /* ov008_FindEntryByTag */
extern void  func_ov008_0205589c(int nOwner, void *pEntry);              /* Ov008_TagTracker_InvokeCallback */

void func_ov008_02076158(Ov008MissionMenu *pMenu)
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

    nOwner = func_ov008_02050c3c();
    pEntry = func_ov008_0205b6e8(func_ov008_020511e0());
    bObject = func_ov008_02050ff8();
    bTransition = func_ov008_02051028();
    tags = data_ov008_0208fb3c;
    if (pEntry->nTextSlot == 0) {
        bUnlocked = 1;
    } else if (pEntry->nTextSlot == 4) {
        bUnlocked = 1;
    } else {
        bUnlocked = func_02023588(pEntry->nTextSlot + FLAG_TEXT_SLOT_BASE);
    }
    if (bUnlocked == 0) {
        func_ov008_020744a0(nOwner, TAG_LOCKED, 2, 2);
    } else {
        func_ov008_020744a0(nOwner, tags.aTag[pEntry->nTextSlot], 2, 2);
    }
    if (bTransition != 0) {
        if (pMenu->bTransfer != 0) {
            switch (func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_TRANSFER, 3)) {
            case 1:
                func_ov008_020744a0(nOwner, TAG_TRANSFER_1, 0x17, 3);
                break;
            case 2:
                func_ov008_020744a0(nOwner, TAG_TRANSFER_2, 0x17, 3);
                break;
            case 3:
                func_ov008_020744a0(nOwner, TAG_TRANSFER_3, 0x17, 3);
                break;
            case 4:
                func_ov008_020744a0(nOwner, TAG_TRANSFER_0, 0x17, 3);
                break;
            case 0:
            default:
                func_ov008_0207451c(nOwner, TAG_TRANSFER_0, 0x17, 3);
                break;
            }
        } else {
            nStage = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STAGE, 3);
            nY = 0x18 - (nStage - 1);
            func_ov008_0207451c(nOwner, TAG_STAGE, 0x15, 3);
            func_ov008_0207451c(nOwner, TAG_STAGE, 0x16, 3);
            switch (nStage) {
            case 1:
                func_ov008_020744a0(nOwner, TAG_STAGE_1, nY, 3);
                break;
            case 2:
                func_ov008_020744a0(nOwner, TAG_STAGE_2, nY, 3);
                break;
            case 3:
                func_ov008_020744a0(nOwner, TAG_STAGE, nY, 3);
                break;
            default:
                func_ov008_0207451c(nOwner, TAG_STAGE, 0x16, 3);
                break;
            }
        }
    } else {
        func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3);
        nMask = func_ov008_020760f0(pMenu, pEntry->nWord);
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
        nRewards = func_020235d0(pEntry->missionId * 4 + FIELD_MISSION_REWARDS, 4);
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
                func_ov008_020744a0(nOwner, nTag, (short)(i + TILE_X_FIRST), 2);
            } else {
                func_ov008_0207451c(nOwner, TAG_RANK_DONE, (short)(i + TILE_X_FIRST), 2);
            }
        }
        func_ov008_0207451c(nOwner, TAG_BADGE, 0x16, 3);
        if (pEntry->bSpecial != 0 || (pEntry->nFlags & 2)) {
            bCleared = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) == 3;
            if (bCleared) {
                func_ov008_020744a0(nOwner, TAG_BADGE, 0x16, 3);
            } else {
                bStarted = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
                if (bStarted) {
                    func_ov008_020744a0(nOwner, TAG_STARTED, 0x16, 3);
                } else {
                    func_ov008_020744a0(nOwner, TAG_STARTED_ALT, 0x17, 3);
                }
            }
        } else {
            bCleared = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) == 3;
            if (bCleared) {
                func_ov008_020744a0(nOwner, TAG_CLEARED_PLAIN, 0x16, 3);
            } else {
                bStarted = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
                if (bStarted) {
                    func_ov008_020744a0(nOwner, TAG_STARTED_PLAIN, 0x16, 3);
                }
            }
        }
        func_ov008_020744a0(nOwner, TAG_FOLLOW, 0x17, 1);
    }
    tierTags = data_ov008_0208fa28;
    nTier = func_ov008_0205b988(pEntry);
    nCleared = func_ov008_0205b974();
    if ((int)func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) < 2 && nCleared + pEntry->completionWeight == 0) {
        nTier = 0;
    }
    if (nCleared == CLEARED_ALL) {
        nTier = 0;
    }
    if (bObject == 0 && pMenu->bAllLocked != 0) {
        nTier = 0;
    }
    if (bObject != 0) {
        bStarted = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
        if (bStarted) {
            nTier = 0;
        }
    }
    if (bTransition != 0) {
        nTier = 0;
    }
    func_ov008_020744a0(nOwner, tierTags.aTag[nTier], 0x1c, 3);
    if (nTier == 0) {
        func_ov008_0205589c(nOwner, func_ov008_02055808(nOwner, 0xf));
    } else {
        func_ov008_0205589c(nOwner, func_ov008_02055808(nOwner, 3));
    }
    if (nTier == 0) {
        data_0204c300.bBadgeShown = 1;
    }
}
