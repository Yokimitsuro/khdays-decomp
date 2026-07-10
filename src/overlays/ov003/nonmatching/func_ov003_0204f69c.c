/* NONMATCHING: large-offset address-split tie, 4 bytes off either way. The three
 * fields at heap+0x1774 / +0x1E10 / +0x1E14 all sit past the 0xFFF ldr/str range.
 * The original recomputes `heap+0x1000` per access-block and reuses it for both the
 * load and store of the counter (`ldr/str [r1,#0x774]`); a plain cast recomputes the
 * store address separately (4B long), and a struct-field form holds the base too
 * aggressively (4B short). No form reproduces the original's per-block base reuse.
 * Semantics exact: lazily inits slot +0x1E14, ticks a bounded counter and pushes
 * two negated fades, else signals full and returns -2. */
extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov105_020bd7c4(void);
extern void func_ov003_0204e91c(int a);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);
extern void func_02020a78(int a, int b);
extern void func_ov003_0204ef68(int a);

int func_ov003_0204f69c(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    if (*(int *)(heap + 0x1e10) == 0)
        *(int *)(heap + 0x1e14) = func_ov105_020bd7c4();
    func_ov003_0204e91c(heap);
    if (*(int *)(heap + 0x1774) < 0x10) {
        int n = *(int *)(heap + 0x1774) + 1;
        *(int *)(heap + 0x1774) = n;
        func_0201e374(-n);
        func_0201e3cc(-*(int *)(heap + 0x1774));
        func_ov003_0204ef68(heap);
        return 0;
    }
    func_02020a78(6, 0);
    return -2;
}
