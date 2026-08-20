typedef int (*Ov002PhaseProc)(void);

extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_02030788(void);
extern unsigned short func_ov002_0206fb84(int nKind, void *pOut);
extern int func_ov002_02068720(void);
extern int func_ov002_020686fc(void);

/* Pick the next phase routine. Remote players and an already-started slot both
 * go straight on; otherwise a kind-0xb request carrying the three entry values
 * is submitted, and the phase only stalls while its handle is unallocated. */
Ov002PhaseProc func_ov002_02068698(void)
{
    int stk[5];
    int pBase;
    int pHeader;
    int pEntry;
    int i;

    pBase = NNSi_FndGetCurrentRootHeap();
    pHeader = pBase + 0x8ba8;
    pEntry = pBase + 0x8bcc;

    if (func_02030788() == 0) {
        if (*(int *)(pHeader + 0xc) != 0) {
            return func_ov002_02068720;
        }

        stk[4] = *(int *)(pEntry + 0x1c);

        for (i = 0; i < 3; i++) {
            stk[1 + i] = *(int *)(pEntry + 0x44);
            pEntry += 0x2c;
        }

        if (func_ov002_0206fb84(0xb, stk) == 0xffff) {
            return 0;
        }
    }

    return func_ov002_020686fc;
}
