/* * Was parked as a register-allocation tie. It was not -- it was a THUMB function that had only
 * ever been verified as ARM (giving a nonsense size gap), plus two ordinary steers:
 *   - `i = 0` must be a STATEMENT after the calls, not a declaration-initialiser. As an
 *     initialiser mwcc emits `movs rN, #0` up front; the ROM emits it after the last call.
 *   - declaration order then picks the callee-saved pair: declare `i` BEFORE `p` to get the
 *     ROM's i->r4 / p->r5.
 * The old header's "r4<->r5 coloring swap" was real, but it was a SYMPTOM of the `i = 0`
 * placement, not a compiler limit. (2026-07-17)
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern long long func_02030d10(int arg0);
extern void func_0201ef58(long long v);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2eb8;

void func_ov022_020b0ff8(int arg0, int arg1, int arg2, int arg3) {
    int i;
    int *p = (int *)NNSi_FndGetCurrentRootHeap();
    func_0201ef58(func_02030d10(8));
    i = 0;
    do {
        if (*p != 0) NNSi_FndFreeFromDefaultHeap(*p);
        i = i + 1;
        p = p + 1;
    } while (i < 4);
    *(int *)&data_ov022_020b2eb8 = 0;
}
