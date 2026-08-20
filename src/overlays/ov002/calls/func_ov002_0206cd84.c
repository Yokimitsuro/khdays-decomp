extern int data_ov002_0207fa00;

extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *NNSi_FndAllocFromDefaultExpHeap(int nSize);
extern int strlen(const char *pText);
extern void func_0201f924(char *pDest, const char *pSource);

/* Replace the cached name table with copies of the given strings.
 * Every previous entry is released first; the table holds ten slots. */
void func_ov002_0206cd84(int nCount, const char **ppNames)
{
    int i;
    int nSlot;
    char *pOld;
    int nBase;

    nBase = *(int *)&data_ov002_0207fa00 + 0x8c94;

    nSlot = nBase;
    for (i = 0; i < 10; i++) {
        pOld = *(char **)(nSlot + 0x28);
        if (pOld != 0) {
            NNSi_FndFreeFromDefaultHeap(pOld);
            *(char **)(nSlot + 0x28) = 0;
        }
        nSlot += 4;
    }

    for (i = 0; i < nCount; i++) {
        *(char **)(nBase + 0x28) =
            (char *)NNSi_FndAllocFromDefaultExpHeap(strlen(*ppNames) + 1);
        func_0201f924(*(char **)(nBase + 0x28), *ppNames);
        ppNames++;
        nBase += 4;
    }
}
