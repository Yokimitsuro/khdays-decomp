/* Step the panel cursor back one position; answer whether anything moved.
 *
 * The current mode is classified and a six-way jump table dispatches. Class 0
 * scans the slot table backwards for the first slot that is not 7, wrapping
 * modulo the slot count. Class 1 steps within the row. Classes 2 and 3 each
 * walk their own list, falling into the other when the index is already zero
 * and that list has entries. Class 5 refuses unless the cached entry is live
 * and passes both group filters. Either way the new kind goes to the rebuild.
 *
 * Three codegen notes. This is THUMB, so there is no smull and every division
 * goes through the runtime helper -- called explicitly here, as everywhere else
 * in the tree, because spelling it `%` emits a symbol that does not link.
 * The four locals are a struct so that their stack slots come out in the ROM's
 * order, which no declaration order of four separate locals can reproduce. And
 * the first member is volatile, which is what keeps the group in memory instead
 * of letting mwcc cache the running value in a callee-saved register across the
 * calls in cases 2 and 3.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 nKey;
    u16 nTag;
    int nState;
} Ov002PanelEntry;

typedef struct {
    u8 bKind;
    u8 bMode;
    u8 bField0002;
    u8 bListIndex;
    u8 bField0004;
    u8 pad0005[0x13];
    u8 bSlotCount;
    u8 pad0019;
    u16 aSlots[0x243];
    u8 pad04a0[4];
    Ov002PanelEntry *pCachedEntry;
    u8 pad04a8[4];
    u8 bListRowBase;
    u8 bListRowOffset;
} Ov002PanelSession;

typedef struct {
    volatile int nOldMode;
    int nNext;
    int nRow;
    int nClass;
} Ov002PanelWork;

extern Ov002PanelSession *data_ov002_0207f620;

extern long long func_02020400(int nNumerator, int nDenominator);
extern int func_ov002_0205a3f0(int *pOut, int nMode);
extern int func_ov002_0205a830(int *pOut, int nIndex);
extern int func_ov002_0205a4a0(void);
extern int func_ov002_0205a4ec(void);
extern int func_ov002_0205a714(int nGroup, int nKey);
extern int func_ov002_0205a730(int nGroup, int nKey);
extern void func_ov002_0205d214(int nTarget, int nFlag);
extern void func_ov002_0205bff4(int nFrom, int nTo);

int func_ov002_0205d478(void) {
    Ov002PanelSession *s = data_ov002_0207f620;
    Ov002PanelWork work;
    int nCount;
    int nPage;
    int nResult;
    int i;

    work.nNext = s->bKind;
    work.nOldMode = s->bMode;

    switch (func_ov002_0205a3f0(&work.nClass, work.nOldMode)) {
    case 0:
        nCount = s->bSlotCount;
        i = 1;
        if (i < nCount) {
        {
            int nKindAndCount = s->bKind + nCount;

            do {
                int k = (u8)(func_02020400(nKindAndCount - i, nCount) >> 32);

                if (s->aSlots[k] != 7) {
                    work.nNext = k;
                    break;
                }
                i++;
            } while (i < nCount);
        }
        }
        break;

    case 1:
        work.nNext = (u8)(func_02020400(
            func_ov002_0205a830(&work.nRow, s->bField0002), 6) >> 32);
        if (work.nRow != work.nClass) {
            func_ov002_0205d214(work.nRow + 1, -1);
        }
        break;

    case 2:
        nCount = func_ov002_0205a4a0();
        if (s->bListIndex == 0 && func_ov002_0205a4ec() > 0) {
            func_ov002_0205d214(s->bListRowOffset + 5, -1);
            work.nNext = (u8)(func_02020400(func_ov002_0205a4ec() + 5, 6) >> 32);
        } else {
            work.nNext = (u8)(func_02020400(
                s->bListIndex + nCount - 1, nCount) >> 32);
            nPage = (u8)func_02020400(work.nNext, 6);
            if (nPage != work.nClass) {
                func_ov002_0205d214(nPage + 4, -1);
            }
            work.nNext = (u8)(func_02020400(work.nNext, 6) >> 32);
        }
        break;

    case 3:
        nCount = func_ov002_0205a4ec();
        if (s->bField0004 == 0 && func_ov002_0205a4a0() > 0) {
            func_ov002_0205d214(s->bListRowBase + 3, -1);
            work.nNext = (u8)(func_02020400(func_ov002_0205a4a0() + 5, 6) >> 32);
        } else {
            work.nNext = (u8)(func_02020400(
                s->bField0004 + nCount - 1, nCount) >> 32);
            nPage = (u8)func_02020400(work.nNext, 6);
            if (nPage != work.nClass) {
                func_ov002_0205d214(nPage + 6, -1);
            }
            work.nNext = (u8)(func_02020400(work.nNext, 6) >> 32);
        }
        break;

    case 5: {
        Ov002PanelEntry *pEntry = s->pCachedEntry;
        int nKey = pEntry->nKey;

        if (pEntry->nState == 0 ||
            func_ov002_0205a714(0, nKey) == 0 ||
            func_ov002_0205a730(0, nKey) == 0) {
            return 0;
        }
        work.nNext = (u8)(s->bKind == 0);
        break;
    }
    }

    if (s->bMode != work.nOldMode || s->bKind != work.nNext) {
        nResult = 1;
    } else {
        nResult = 0;
    }
    func_ov002_0205bff4(s->bKind, work.nNext);
    return nResult;
}
