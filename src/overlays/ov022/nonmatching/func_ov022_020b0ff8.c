/*
 * [nonmatching: the NNSi_FndGetCurrentRootHeap() call result (walking base) colors to r4 vs the original r5 — the call-result-parks-in-r4 limit (sibling of 0208694c)]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted register
 * allocation / scheduling. Left uncarved (byte-exact in the blob).
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern long long func_02030d10(int arg0);
extern void func_0201ef58(long long v);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2eb8;

void func_ov022_020b0ff8(int arg0, int arg1, int arg2, int arg3) {
    int *p = (int *)NNSi_FndGetCurrentRootHeap();
    int i = 0;
    func_0201ef58(func_02030d10(8));
    do {
        if (*p != 0) NNSi_FndFreeFromDefaultHeap(*p);
        i = i + 1;
        p = p + 1;
    } while (i < 4);
    *(int *)&data_ov022_020b2eb8 = 0;
}
