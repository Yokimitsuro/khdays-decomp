/* func_ov025_020a54c8 -- Ov008_DrawMissionRow: draw row nIndex (mod 6) of
 * the mission list for entry pEntry.  The row is dimmed (colour 0xf7)
 * when, without the object (02050ff8), the mission is started, or during a
 * transition (02051028) when the entry gate (+0x40) refuses it (0206fb34 /
 * 0206fb2c); the text slot (+0x4: 0 / 4, else game flag 0x3bc9 + slot)
 * picks the slot tag from 0208f9b0 -- 0208f9e0 for a started mission
 * without the object -- at (3, 4 * row + 1), or the locked tag 0x6d.
 * During a transition the mission status (3 bits at 0x2ca4 + 3 * id with a
 * transfer: tags 0x96 .. 0x93 at (0x18, 4 * row + 2), 0x93 notified for 0;
 * else 0x2a4c + 3 * id: 0x90 notified at (0x16 / 0x17, y), 0x92 / 0x91 /
 * 0x90 at (0x19 - (stage - 1), y) for stages 1 / 2 / 3, or 0x90 notified at
 * (0x17, y)) marks the row; otherwise the rank mask (0206fda0) and the
 * reward flags (0x92b + 4 * id) fill the three tiles at (0x15 + i, 4 * row
 * + 1) with 0x82 / 0x83 (rank) or 0x84 / 0x85 (bonus), 0x82 notified for an
 * unused tile; 0x8d is notified at (0x17, 4 * row + 2) and the cleared /
 * started badge follows (special entry or flag 2: 0x8d / 0x98 / 0x87 at
 * (0x17 / 0x17 / 0x18); plain: 0x8c / 0x97), then 0x86 at (0x18, 4 * row).
 * The row's rank surface (+0x1ec + 0x3c * row) shows the rank (+0x6) with a
 * glyph (0x20; 0xff41 / 0xff42 in colour 0xf3 during a transition without
 * transfer by the kind +0x18), then the slot's text (0205b6c8, width 0x60)
 * or text 4 when locked, or in a transition without transfer the reward
 * kind's text (0x15 .. 0x1e, 02090888) expanded by the format +0x48 (width
 * 0x78); the name surface (+0x84 ..) shows the entry's name (+0x3c) or the
 * name node's (0206fd50); the count surface (+0x354 ..) shows "set / total"
 * (0206fc24, 0209088c) outside a transition or the count's text (+0x4c8,
 * 0xe + count) with a transfer.  Slot 0x1a is marked used.  Codegen: the
 * declaration order transition / bonus / unlocked / row / y / dim fixes
 * the spill slots; the two tag tables are struct copies; the gate helpers
 * take the same arguments so the setup is shared; the started test of the
 * slot tag is an inline bool helper (materialised, then tested); the
 * status tests are bool locals; y + 2 is a local in each branch; the rank
 * surface is indexed through the array for the first call, the rank text
 * and the unlock branch, and through a `pInfo` local (set after the first
 * call) for the refresh and the reward branch -- two base registers; the
 * slot is loaded into a local before the three unlock tests.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define ROWS_PER_PAGE   6
#define FLAG_TEXT_SLOT_BASE 0x3bc9
#define FIELD_MISSION_STATUS 0x28e4
#define FIELD_MISSION_TRANSFER 0x2ca4
#define FIELD_MISSION_STAGE 0x2a4c
#define FIELD_MISSION_REWARDS 0x92b
#define TAG_LOCKED      0x6d
#define TAG_RANK_DONE   0x82
#define TAG_RANK_OPEN   0x83
#define TAG_BONUS_DONE  0x84
#define TAG_BONUS_OPEN  0x85
#define TAG_ROW         0x86
#define TAG_STARTED_ALT 0x87
#define TAG_CLEARED_PLAIN 0x8c
#define TAG_BADGE       0x8d
#define TAG_STAGE       0x90
#define TAG_STAGE_2     0x91
#define TAG_STAGE_1     0x92
#define TAG_TRANSFER_0  0x93
#define TAG_TRANSFER_3  0x94
#define TAG_TRANSFER_2  0x95
#define TAG_TRANSFER_1  0x96
#define TAG_STARTED_PLAIN 0x97
#define TAG_STARTED     0x98
#define COLOUR_NORMAL   0xf1
#define COLOUR_ACTIVE   0xf3
#define COLOUR_DIM      0xf7
#define GLYPH_SPACE     0x20
#define GLYPH_MARK_A    0xff41
#define TEXT_LOCKED     4
#define TEXT_REWARD_FIRST 0x15
#define TEXT_COUNT_BASE 0xe
#define RANK_TILES      3
#define TILE_X_FIRST    0x15

typedef struct Ov008MissionListEntry {
    u16   nWord;              /* 0x00 */
    u16   missionId;          /* 0x02 */
    u16   nTextSlot;          /* 0x04 */
    u16   nRank;              /* 0x06 */
    u16   nCount;             /* 0x08 */
    u8    pad_0a[2];
    u8    bSpecial;           /* 0x0c */
    u8    pad_0d[7];
    u8    nFlags;             /* 0x14 */
    u8    pad_15[3];
    int   nKind;              /* 0x18 */
    u8    pad_1c[0x2e - 0x1c];
    u16   nRewardKind;        /* 0x2e */
    u8    pad_30[0x3c - 0x30];
    u16  *pName;              /* 0x3c */
    u8    pad_40[8];
    u16  *pDescFormat;        /* 0x48 */
} Ov008MissionListEntry;

typedef struct Ov008MissionNameNode {
    u16   nWord;              /* 0x00 */
    u8    pad_02[0x3c - 2];
    u16  *pName;              /* 0x3c */
} Ov008MissionNameNode;

typedef struct Ov008RowSurface {
    u8 pad_00[0x3c];
} Ov008RowSurface;

typedef struct Ov008MissionList {
    u8  pad_000[0x40];
    int bEntryGate;           /* 0x040 */
    u8  pad_044[0x84 - 0x44];
    Ov008RowSurface aRowNameSurface[ROWS_PER_PAGE];  /* 0x084 */
    Ov008RowSurface aRowInfoSurface[ROWS_PER_PAGE];  /* 0x1ec */
    Ov008RowSurface aRowDotSurface[ROWS_PER_PAGE]; /* 0x354 */
    u8  textCacheA[0xc];      /* 0x4bc: variable text records */
    u8  textCacheB[0xc];      /* 0x4c8: count texts */
} Ov008MissionList;

typedef struct Ov008SlotTags {
    u32 aTag[12];
} Ov008SlotTags;

extern const Ov008SlotTags data_ov025_020b4660;                          /* slot tags */
extern const Ov008SlotTags data_ov025_020b4690;                          /* slot tags of a started mission */
extern const u16 data_ov025_020b535c[];                                  /* "rank" format */
extern const u16 data_ov025_020b536c[];                                  /* empty reward text */
extern const u16 data_ov025_020b5370[];                                  /* "set / total" format */
extern int   func_ov025_02084a64(void);                                  /* Ov008_GetCtxBlock954c */
extern int   func_ov025_02084e08(void);                                  /* Ov008_GetCtxObject9630 */
extern int   func_ov025_02084e38(void);                                  /* Ov008_GetCtxObject9634: page transition */
extern u32   func_020235d0(int nField, int nBits);                       /* GameState_GetField */
extern int   func_ov025_020a50d8(Ov008MissionList *pList, Ov008MissionListEntry *pEntry); /* IsField8LeField57 */
extern int   func_ov025_020a50d0(Ov008MissionList *pList, Ov008MissionListEntry *pEntry); /* ov008_helper_6fb2c (ignores its arguments) */
extern int   func_02023588(int nFlag);                                   /* GameState_IsFlagSet */
extern void  func_ov025_020a53f4(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueDup */
extern void  func_ov025_020a5484(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueAndNotify2 */
extern u32   func_ov025_020a5344(Ov008MissionList *pList, u32 nWord);    /* Ov008_BuildRankMask */
extern Ov008MissionNameNode *func_ov025_020a52f4(Ov008MissionList *pList, u32 nWord); /* find the name node */
extern void  func_ov025_020a4e80(Ov008RowSurface *pSurface);
extern void  func_02030158(void *pSurface);                              /* Obj_InvokeInnerVtable4 */
extern void  func_020262a0(u16 *pDst, int nCap, const u16 *pFormat, ...); /* Text_FormatUtf16 */
extern void  func_02030278(void *pSurface, int nX, int nY, int nColour, void *pText, int nFlag); /* Text_DrawWithShadow */
extern int   func_ov025_0208dc34(u32 nTextSlot);
extern void  func_ov025_020a4f10(Ov008RowSurface *pSurface, int nValue, int nWidth); /* Ov008_Set_f96c */
extern void *func_ov025_02089894(void *pRecords, int nIndex);            /* GetVarRecordByIndex */
extern void  func_ov025_020a4e9c(Ov008RowSurface *pSurface);
extern void  func_ov025_020a4f4c(Ov008RowSurface *pSurface, void *pText, int nWidth);
extern void  func_ov025_020a51c8(Ov008MissionList *pList, u32 nWord, int *pnSet, u32 *pnTotal); /* Ov008_CountGroupFlagsSet */
extern void  func_ov025_02084964(int nSlot);                             /* Ov008_MarkSlotUsed */

static inline int Ov008_IsMissionStarted(Ov008MissionListEntry *pEntry)
{
    return func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
}

void func_ov025_020a54c8(Ov008MissionList *pList, int nIndex, Ov008MissionListEntry *pEntry)
{
    u16 aDesc[0x80];
    Ov008SlotTags tags;
    Ov008SlotTags tagsStarted;
    u16 aRank[4];
    u16 aCount[4];
    int nSet;
    u32 nTotal;
    int bTransition;
    u8 nBonus;
    int bUnlocked;
    int nRow;
    int nY;
    int bDim;
    int nOwner;
    int bObject;
    u32 nStage;
    int nY2;
    int nX;
    u32 nMask;
    u8 nRanks;
    u8 nRewards;
    u32 i;
    u32 nTag;
    int bCleared;
    int bStarted;
    int nColour;
    Ov008MissionNameNode *pNode;
    int nGlyph;
    u32 nSlot;
    void *pText;
    Ov008RowSurface *pInfo;

    nOwner = func_ov025_02084a64();
    nRow = nIndex % ROWS_PER_PAGE;
    bObject = func_ov025_02084e08();
    bTransition = func_ov025_02084e38();
    bDim = 0;
    if (bObject == 0) {
        bDim = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
    } else if (bTransition != 0) {
        if (pList->bEntryGate != 0) {
            bDim = func_ov025_020a50d8(pList, pEntry) == 0;
        } else {
            bDim = func_ov025_020a50d0(pList, pEntry) == 0;
        }
    }
    if (pEntry->nTextSlot == 0) {
        bUnlocked = 1;
    } else if (pEntry->nTextSlot == 4) {
        bUnlocked = 1;
    } else {
        bUnlocked = func_02023588(pEntry->nTextSlot + FLAG_TEXT_SLOT_BASE);
    }
    tags = data_ov025_020b4660;
    tagsStarted = data_ov025_020b4690;
    if (bUnlocked == 0) {
        func_ov025_020a53f4(nOwner, TAG_LOCKED, 3, (short)(nRow * 4 + 1));
    } else if (bObject == 0 && Ov008_IsMissionStarted(pEntry)) {
        func_ov025_020a53f4(nOwner, tagsStarted.aTag[pEntry->nTextSlot], 3, (short)(nRow * 4 + 1));
    } else {
        func_ov025_020a53f4(nOwner, tags.aTag[pEntry->nTextSlot], 3, (short)(nRow * 4 + 1));
    }
    nY = nRow * 4;
    if (bTransition != 0) {
        if (pList->bEntryGate != 0) {
            nStage = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_TRANSFER, 3);
            nY2 = nY + 2;
            switch (nStage) {
            case 1:
                func_ov025_020a53f4(nOwner, TAG_TRANSFER_1, 0x18, (short)nY2);
                break;
            case 2:
                func_ov025_020a53f4(nOwner, TAG_TRANSFER_2, 0x18, (short)nY2);
                break;
            case 3:
                func_ov025_020a53f4(nOwner, TAG_TRANSFER_3, 0x18, (short)nY2);
                break;
            case 4:
                func_ov025_020a53f4(nOwner, TAG_TRANSFER_0, 0x18, (short)nY2);
                break;
            case 0:
            default:
                func_ov025_020a5484(nOwner, TAG_TRANSFER_0, 0x18, (short)nY2);
                break;
            }
        } else {
            nStage = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STAGE, 3);
            nY2 = nY + 2;
            nX = 0x19 - (nStage - 1);
            func_ov025_020a5484(nOwner, TAG_STAGE, 0x16, (short)nY2);
            func_ov025_020a5484(nOwner, TAG_STAGE, 0x17, (short)nY2);
            switch (nStage) {
            case 1:
                func_ov025_020a53f4(nOwner, TAG_STAGE_1, (short)nX, (short)nY2);
                break;
            case 2:
                func_ov025_020a53f4(nOwner, TAG_STAGE_2, (short)nX, (short)nY2);
                break;
            case 3:
                func_ov025_020a53f4(nOwner, TAG_STAGE, (short)nX, (short)nY2);
                break;
            default:
                func_ov025_020a5484(nOwner, TAG_STAGE, 0x17, (short)nY2);
                break;
            }
        }
    } else {
        nMask = func_ov025_020a5344(pList, pEntry->nWord);
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
                func_ov025_020a53f4(nOwner, nTag, (short)(i + TILE_X_FIRST), (short)(nY + 1));
            } else {
                func_ov025_020a5484(nOwner, TAG_RANK_DONE, (short)(i + TILE_X_FIRST), (short)(nY + 1));
            }
        }
        nY2 = nY + 2;
        func_ov025_020a5484(nOwner, TAG_BADGE, 0x17, (short)nY2);
        if (pEntry->bSpecial != 0 || (pEntry->nFlags & 2)) {
            bCleared = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) == 3;
            if (bCleared) {
                func_ov025_020a53f4(nOwner, TAG_BADGE, 0x17, (short)nY2);
            } else {
                bStarted = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
                if (bStarted) {
                    func_ov025_020a53f4(nOwner, TAG_STARTED, 0x17, (short)nY2);
                } else {
                    func_ov025_020a53f4(nOwner, TAG_STARTED_ALT, 0x18, (short)nY2);
                }
            }
        } else {
            bCleared = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) == 3;
            if (bCleared) {
                func_ov025_020a53f4(nOwner, TAG_CLEARED_PLAIN, 0x17, (short)nY2);
            } else {
                bStarted = func_020235d0(pEntry->missionId * 3 + FIELD_MISSION_STATUS, 3) >= 2;
                if (bStarted) {
                    func_ov025_020a53f4(nOwner, TAG_STARTED_PLAIN, 0x17, (short)nY2);
                }
            }
        }
        func_ov025_020a53f4(nOwner, TAG_ROW, 0x18, (short)nY);
    }
    if (bDim != 0) {
        nColour = COLOUR_DIM;
    } else {
        nColour = COLOUR_NORMAL;
    }
    pNode = 0;
    if (func_ov025_02084e38() != 0) {
        pNode = func_ov025_020a52f4(pList, pEntry->nWord);
    }
    nGlyph = GLYPH_SPACE;
    if (func_ov025_02084e38() != 0) {
        if (pList->bEntryGate == 0) {
            nGlyph = GLYPH_MARK_A;
            if (pEntry->nKind == 2) {
                nGlyph++;
                nColour = COLOUR_ACTIVE;
            }
        }
    }
    func_ov025_020a4e80(&pList->aRowInfoSurface[nRow]);
    pInfo = pList->aRowInfoSurface;
    func_02030158(&pInfo[nRow]);
    func_020262a0(aRank, 4, data_ov025_020b535c, pEntry->nRank, nGlyph);
    func_02030278(&pList->aRowInfoSurface[nRow], 0, 5, nColour, aRank, 1);
    if (func_ov025_02084e38() == 0 || pList->bEntryGate != 0) {
        nSlot = pEntry->nTextSlot;
        if (bUnlocked != 0) {
            func_ov025_020a4f10(&pList->aRowInfoSurface[nRow], func_ov025_0208dc34(nSlot), 0x60);
        }
        if (bUnlocked != 0) {
            func_02030278(&pList->aRowInfoSurface[nRow], 0x14, 5, nColour, (void *)func_ov025_0208dc34(nSlot), 1);
        }
        if (bUnlocked == 0) {
            func_02030278(&pList->aRowInfoSurface[nRow], 0x14, 5, nColour, func_ov025_02089894(pList->textCacheA, TEXT_LOCKED), 1);
        }
    } else {
        pText = (void *)data_ov025_020b536c;
        switch (pEntry->nRewardKind) {
        case 0:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST);
            break;
        case 1:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 1);
            break;
        case 2:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 2);
            break;
        case 3:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 3);
            break;
        case 4:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 4);
            break;
        case 5:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 6);
            break;
        case 6:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 7);
            break;
        case 7:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 8);
            break;
        case 8:
            pText = func_ov025_02089894(pList->textCacheA, TEXT_REWARD_FIRST + 9);
            break;
        }
        func_020262a0(aDesc, 0x100, pEntry->pDescFormat, pText);
        func_ov025_020a4f10(&pInfo[nRow], (int)aDesc, 0x78);
        func_02030278(&pInfo[nRow], 0x14, 5, nColour, aDesc, 1);
    }
    func_ov025_020a4e9c(&pList->aRowNameSurface[nRow]);
    if (*pEntry->pName == 0 && pNode != 0) {
        func_ov025_020a4f4c(&pList->aRowNameSurface[nRow], pNode->pName, 0x80);
        func_02030158(&pList->aRowNameSurface[nRow]);
        func_02030278(&pList->aRowNameSurface[nRow], 0, 1, nColour, pNode->pName, 1);
    } else {
        func_ov025_020a4f4c(&pList->aRowNameSurface[nRow], pEntry->pName, 0x80);
        func_02030158(&pList->aRowNameSurface[nRow]);
        func_02030278(&pList->aRowNameSurface[nRow], 0, 1, nColour, pEntry->pName, 1);
    }
    func_ov025_020a4e80(&pList->aRowDotSurface[nRow]);
    if (bTransition == 0) {
        nSet = 0;
        nTotal = 0;
        func_ov025_020a51c8(pList, pEntry->nWord, &nSet, &nTotal);
        func_02030158(&pList->aRowDotSurface[nRow]);
        func_020262a0(aCount, 4, data_ov025_020b5370, nSet, nTotal);
        func_02030278(&pList->aRowDotSurface[nRow], 2, 7, nColour, aCount, 1);
    } else if (pList->bEntryGate != 0) {
        pText = func_ov025_02089894(pList->textCacheB, pEntry->nCount + TEXT_COUNT_BASE);
        func_02030158(&pList->aRowDotSurface[nRow]);
        if (pEntry->nCount != 0) {
            func_02030278(&pList->aRowDotSurface[nRow], 0, 5, nColour, pText, 1);
        }
    }
    func_ov025_02084964(0x1a);
}
