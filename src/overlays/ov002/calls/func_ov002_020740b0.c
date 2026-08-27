typedef unsigned char u8;
typedef signed char s8;

typedef struct Ov002Entry {
    char pad000[1];
    signed char nState : 4; /* bit 0 says the entry has settled */
    signed char nValue : 4;
} Ov002Entry;

typedef struct Ov002EntryList {
    char pad000[8];
    Ov002Entry *apEntries[1];
} Ov002EntryList;

typedef struct Ov002Row {
    char pad000[0x14];
    s8 bIndex;              /* which entry the row reads */
    char pad015[2];
    s8 bFilter;
} Ov002Row;

typedef struct Ov002Ctx {
    char pad000[4];
    Ov002EntryList *pList;
    char pad008[8];
    s8 bDefault;
    char pad011[7];
    int n18;                /* -1 while the screen has nothing to answer for */
    char pad01c[0x28];
    Ov002Row *pRows;
    char pad048[1];
    u8 bCount;
} Ov002Ctx;

extern Ov002Ctx *data_ov002_0207fa14;

/* Answers for one entry when nIndex is a real index, or for the whole row set
   when it is negative.  -1 means the screen has nothing to answer for at all
   and -2 means something has not settled yet; otherwise the single-entry form
   hands back that entry's value and the sweep hands back the default. */
int func_ov002_020740b0(int nIndex, int nFilter)
{
    Ov002Ctx *pCtx;
    Ov002Entry *pEntry;
    Ov002Row *pRow;
    int i;

    pCtx = data_ov002_0207fa14;
    if (pCtx->n18 == -1) {
        return -1;
    }

    if (nIndex >= 0) {
        pEntry = pCtx->pList->apEntries[nIndex];
        if ((pEntry->nState & 1) == 0) {
            return -2;
        }
        return pEntry->nValue;
    }

    for (i = 0; i < pCtx->bCount; i++) {
        pRow = &pCtx->pRows[i];
        if (nFilter < 1 || pRow->bFilter == nFilter) {
            if ((pCtx->pList->apEntries[pRow->bIndex]->nState & 1) == 0) {
                return -2;
            }
        }
    }
    return pCtx->bDefault;
}
