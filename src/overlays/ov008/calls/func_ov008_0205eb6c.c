/* func_ov008_0205eb6c -- Ov008_ComputeGridChanges: fill the change set of a
 * rebuilt grid summary (pNew) against the previous one (pOld); returns 1
 * when any of the seven stat totals moved.  The local player's member kind
 * (session slot) picks the weapon record of each summary (0208b890 with the
 * summary's weapon id, +0x74); a kind of 0 or 0x13 falls back to 0x13 / 0
 * by the summary's own flag (+0x2c).  With +0x30 set the record's alternate
 * stat replaces its second one.  The deltas of the two plain totals (+0x78,
 * +0x7c) and of the five weapon-added totals (+0x80 .. +0x90 plus the
 * record's stats) go to +0x64 .. +0x7c of the change set; the entry count
 * (020539f0) and node count (02053a54) deltas to +0x8 / +0xc, the two header
 * words to +0x0 / +0x4.  The "new" flag (+0x14) is set when any entry of the
 * new summary's lists (+0x20, +0x14, +0x8: words +0xc, +0x10, +0xc) is new;
 * failing that, every category but the player's own (0208f3c8 by member
 * kind) is scanned: the delta of categories with a positive count goes to
 * +0x10 and any "appeared" word (+0x38) sets the flag.  Codegen: the kind
 * table is a 22-word struct copy; nOld is declared before nNew.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

#define CATEGORY_COUNT 14
#define KIND_NONE      0
#define KIND_DEFAULT   0x13

typedef struct NNSFndList {
    u8 pad[12];
} NNSFndList;

typedef struct Ov008SummaryEntryA {
    int nId;                  /* 0x00 */
    u8  pad_04[8];
    int bNew;                 /* 0x0c */
} Ov008SummaryEntryA;

typedef struct Ov008SummaryEntryB {
    int nId;                  /* 0x00 */
    u8  pad_04[12];
    int bNew;                 /* 0x10 */
} Ov008SummaryEntryB;

typedef struct Ov008GridSummary {
    int nHeaderA;             /* 0x00 */
    int nHeaderB;             /* 0x04 */
    NNSFndList listA;         /* 0x08 */
    NNSFndList listB;         /* 0x14 */
    NNSFndList listC;         /* 0x20 */
    int bNoCharacter;         /* 0x2c: weapon kind 0x13 instead of 0 */
    int bAltStat;             /* 0x30: use the weapon's alternate stat */
    u8  pad_34[4];
    int aAppeared[CATEGORY_COUNT]; /* 0x38 */
    u8  pad_70[4];
    int nWeaponId;            /* 0x74 */
    int aTotal[7];            /* 0x78: two plain, five weapon-added */
    int aCount[CATEGORY_COUNT];    /* 0x94 */
    u8  pad_cc[0x100 - 0xcc];
} Ov008GridSummary;

typedef struct Ov008GridChanges {
    int nHeaderA;             /* 0x00 */
    int nHeaderB;             /* 0x04 */
    int nEntries;             /* 0x08 */
    int nNodes;               /* 0x0c */
    int nCategories;          /* 0x10 */
    int bNew;                 /* 0x14 */
    u8  pad_18[0x64 - 0x18];
    int aTotal[7];            /* 0x64 */
    u8  pad_80[0xb8 - 0x80];
} Ov008GridChanges;

/* weapon-stat record filled by Ov008_LoadCharacterWeapon (0208b890) */
typedef struct Ov008WeaponBuf {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    int w8;
    s16 hc;
    s16 he;
    u8  pad_10[16];
} Ov008WeaponBuf;

typedef struct Ov008KindCategoryTable {
    int aOwnCategory[22];     /* category owned by each member kind */
} Ov008KindCategoryTable;

typedef struct SessionSlotInfo {
    int bOccupied;            /* 0x00 */
    int nMemberKind;          /* 0x04 */
} SessionSlotInfo;

extern const Ov008KindCategoryTable data_ov008_0208f3c8;
extern u32   func_02030788(void);                                 /* Session_GetLocalPlayerIndex */
extern SessionSlotInfo *func_020315c0(int nSlot);                 /* Slot4_GetIfOccupied */
extern void  func_ov008_0208b890(Ov008WeaponBuf *pOut, int nKind, int nWeaponId); /* Ov008_LoadCharacterWeapon */
extern int   func_ov008_020539f0(Ov008GridSummary *pSummary);     /* count the entries */
extern int   func_ov008_02053a54(Ov008GridSummary *pSummary);     /* Ov008_CountListNodes */
extern void *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);
extern void  func_ov008_0205c580(int *pOutValue, int *pOutKind);  /* read the player's slot config */

int func_ov008_0205eb6c(Ov008GridChanges *pOut, Ov008GridSummary *pOld, Ov008GridSummary *pNew)
{
    Ov008KindCategoryTable table;
    Ov008WeaponBuf bufOld;
    Ov008WeaponBuf bufNew;
    int nKind;
    int bChanged;
    int nKindNew;
    int nKindOld;
    int nDelta;
    Ov008SummaryEntryA *pEntryA;
    Ov008SummaryEntryB *pEntryB;
    int nOld;
    int nNew;
    int nSkip;
    int i;

    bChanged = 0;
    nKindNew = func_020315c0(func_02030788())->nMemberKind;
    if (nKindNew == KIND_NONE || nKindNew == KIND_DEFAULT) {
        nKindOld = pOld->bNoCharacter != 0 ? KIND_DEFAULT : KIND_NONE;
        nKindNew = pNew->bNoCharacter != 0 ? KIND_DEFAULT : KIND_NONE;
    } else {
        nKindOld = nKindNew;
    }
    func_ov008_0208b890(&bufOld, nKindOld, pOld->nWeaponId);
    func_ov008_0208b890(&bufNew, nKindNew, pNew->nWeaponId);
    if (pOld->bAltStat != 0) {
        bufOld.h2 = bufOld.he;
    }
    if (pNew->bAltStat != 0) {
        bufNew.h2 = bufNew.he;
    }
    nDelta = pNew->aTotal[0] - pOld->aTotal[0];
    pOut->aTotal[0] = nDelta;
    if (nDelta != 0) {
        bChanged = 1;
    }
    nDelta = pNew->aTotal[1] - pOld->aTotal[1];
    pOut->aTotal[1] = nDelta;
    if (nDelta != 0) {
        bChanged = 1;
    }
    nDelta = (pNew->aTotal[2] + bufNew.h2) - (pOld->aTotal[2] + bufOld.h2);
    pOut->aTotal[2] = nDelta;
    if (nDelta != 0) {
        bChanged = 1;
    }
    nDelta = (pNew->aTotal[3] + bufNew.h4) - (pOld->aTotal[3] + bufOld.h4);
    pOut->aTotal[3] = nDelta;
    if (nDelta != 0) {
        bChanged = 1;
    }
    nDelta = (pNew->aTotal[4] + bufNew.h6) - (pOld->aTotal[4] + bufOld.h6);
    pOut->aTotal[4] = nDelta;
    if (nDelta != 0) {
        bChanged = 1;
    }
    nDelta = (pNew->aTotal[5] + bufNew.w8) - (pOld->aTotal[5] + bufOld.w8);
    pOut->aTotal[5] = nDelta;
    if (nDelta != 0) {
        bChanged = 1;
    }
    nDelta = (pNew->aTotal[6] + bufNew.hc) - (pOld->aTotal[6] + bufOld.hc);
    pOut->aTotal[6] = nDelta;
    if (nDelta != 0) {
        bChanged = 1;
    }
    pOut->nEntries = func_ov008_020539f0(pNew) - func_ov008_020539f0(pOld);
    pOut->nNodes = func_ov008_02053a54(pNew) - func_ov008_02053a54(pOld);
    pOut->nHeaderA = pNew->nHeaderA - pOld->nHeaderA;
    pOut->nHeaderB = pNew->nHeaderB - pOld->nHeaderB;
    pOut->bNew = 0;
    for (pEntryA = NNS_FndGetNextListObject(&pNew->listC, 0); pEntryA != 0;
         pEntryA = NNS_FndGetNextListObject(&pNew->listC, pEntryA)) {
        if (pEntryA->bNew != 0) {
            pOut->bNew = 1;
            break;
        }
    }
    if (pOut->bNew == 0) {
        for (pEntryB = NNS_FndGetNextListObject(&pNew->listB, 0); pEntryB != 0;
             pEntryB = NNS_FndGetNextListObject(&pNew->listB, pEntryB)) {
            if (pEntryB->bNew != 0) {
                pOut->bNew = 1;
                break;
            }
        }
    }
    if (pOut->bNew == 0) {
        for (pEntryA = NNS_FndGetNextListObject(&pNew->listA, 0); pEntryA != 0;
             pEntryA = NNS_FndGetNextListObject(&pNew->listA, pEntryA)) {
            if (pEntryA->bNew != 0) {
                pOut->bNew = 1;
                break;
            }
        }
    }
    if (pOut->bNew == 0) {
        table = data_ov008_0208f3c8;
        nOld = 0;
        nNew = 0;
        func_ov008_0205c580(0, &nKind);
        nSkip = table.aOwnCategory[nKind];
        for (i = 0; i < CATEGORY_COUNT; i++) {
            if (i != nSkip) {
                if (pOld->aCount[i] > 0) {
                    nOld++;
                }
                if (pNew->aCount[i] > 0) {
                    nNew++;
                }
                if (pNew->aAppeared[i] != 0) {
                    pOut->bNew = 1;
                }
            }
        }
        pOut->nCategories = nNew - nOld;
    }
    return bChanged;
}
