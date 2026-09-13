/* func_ov025_020913fc -- Ov008_DiffGridSummary: compare a rebuilt grid
 * summary (pNew) against the previous one (pOld).  Every entry of the new
 * summary's three lists (+0x8, +0x14, +0x20) is flagged "new" (word +0xc,
 * +0x10 and +0xc respectively) unless an entry with the same id (+0x0) exists
 * in the old summary's matching list.  Then each of the fourteen category
 * counters (+0x94) marks its "appeared" word (+0x38) when the old count was 0
 * and the new one is positive.
 */
typedef unsigned char u8;

#define CATEGORY_COUNT 14

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
    u8  pad_00[8];
    NNSFndList listA;         /* 0x08 */
    NNSFndList listB;         /* 0x14 */
    NNSFndList listC;         /* 0x20 */
    u8  pad_2c[0x38 - 0x2c];
    int aAppeared[CATEGORY_COUNT]; /* 0x38 */
    u8  pad_70[0x94 - 0x70];
    int aCount[CATEGORY_COUNT];    /* 0x94 */
} Ov008GridSummary;

extern void *NNS_FndGetNextListObject(NNSFndList *pList, void *pObject);

void func_ov025_020913fc(Ov008GridSummary *pNew, Ov008GridSummary *pOld)
{
    Ov008SummaryEntryA *pEntryA;
    Ov008SummaryEntryA *pOtherA;
    Ov008SummaryEntryB *pEntryB;
    Ov008SummaryEntryB *pOtherB;
    int i;

    for (pEntryA = NNS_FndGetNextListObject(&pNew->listA, 0); pEntryA != 0;
         pEntryA = NNS_FndGetNextListObject(&pNew->listA, pEntryA)) {
        pEntryA->bNew = 1;
        for (pOtherA = NNS_FndGetNextListObject(&pOld->listA, 0); pOtherA != 0;
             pOtherA = NNS_FndGetNextListObject(&pOld->listA, pOtherA)) {
            if (pEntryA->nId == pOtherA->nId) {
                pEntryA->bNew = 0;
                break;
            }
        }
    }
    for (pEntryB = NNS_FndGetNextListObject(&pNew->listB, 0); pEntryB != 0;
         pEntryB = NNS_FndGetNextListObject(&pNew->listB, pEntryB)) {
        pEntryB->bNew = 1;
        for (pOtherB = NNS_FndGetNextListObject(&pOld->listB, 0); pOtherB != 0;
             pOtherB = NNS_FndGetNextListObject(&pOld->listB, pOtherB)) {
            if (pEntryB->nId == pOtherB->nId) {
                pEntryB->bNew = 0;
                break;
            }
        }
    }
    for (pEntryA = NNS_FndGetNextListObject(&pNew->listC, 0); pEntryA != 0;
         pEntryA = NNS_FndGetNextListObject(&pNew->listC, pEntryA)) {
        pEntryA->bNew = 1;
        for (pOtherA = NNS_FndGetNextListObject(&pOld->listC, 0); pOtherA != 0;
             pOtherA = NNS_FndGetNextListObject(&pOld->listC, pOtherA)) {
            if (pEntryA->nId == pOtherA->nId) {
                pEntryA->bNew = 0;
                break;
            }
        }
    }
    for (i = 0; i < CATEGORY_COUNT; i++) {
        if (pOld->aCount[i] == 0 && pNew->aCount[i] > 0) {
            pNew->aAppeared[i] = 1;
        } else {
            pNew->aAppeared[i] = 0;
        }
    }
}
