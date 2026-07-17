/* Rebuild the panel view (x7: ov000/004/005/008/009/025/026). Load the three message
 * databases this screen needs -- the caller's type code plus 0x14 and 0x13 -- but only
 * the ones not already resident, remembering which we loaded so we can drop exactly
 * those again at the end. Lay out every entry in the source list (each at its own
 * 0xa0-byte row) and total their heights into self[0]. Then snapshot the three 64-bit
 * cell masks out of self+0xcc, hand each to the row renderer, and count every set cell
 * across the 3 panels of 8 rows x 5 columns into self[1]. Finally give every list node
 * a non-zero default for its two counters and refresh the cursor.
 *
 * The masks really are 64-bit: the ROM builds `1LL << bit` as a hi/lo pair (the
 * lsl/rsb/orr/orr dance) and tests both words, which is why `unsigned long long` is the
 * right type -- and it also gives the stride-8 indexing the ROM uses.
 *
 * Two spellings are load-bearing:
 *  - `pairs[k]` must come off a struct member: 0xcc is not a multiple of the 8-byte
 *    element, so `self[k*2 + 0x33]` makes mwcc build a k*2 induction variable instead of
 *    the ROM's `add r0, r4, r5, lsl #3`. See codegen-cracks.md.
 *  - `base` must advance in the for-increment. Written as a statement in the body it is
 *    emitted BEFORE the mask pointer's own increment; the ROM does the mask first.
 *
 * (Ghidra renders func_02034150 with four arguments here. It takes TWO -- the ROM sets
 * only r0/r1, and there is a call between the first two uses that clobbers r2/r3.) */
extern void func_ov025_02086ff0(int *self);
extern int func_ov025_020858d0(int a);
extern int func_020342b4(int db);
extern void func_02034150(int id, int a);
extern void func_02034258(int id);
extern void *NNS_FndGetNextListObject(void *list, void *cur);
extern void MIi_CpuCopy32(const void *src, void *dst, unsigned int n);
extern void func_ov025_02086744(int *self, int a, void *node, int idx);
extern void func_ov025_02086cb8(int *self, int base, int a, int b, unsigned long long *m);

struct Pair { int a, b; };
struct Self { char pad[0xcc]; struct Pair pairs[3]; };
extern void func_ov025_0208595c(void *p);

void func_ov025_02087260(int *self, int base, void *list, int p4) {
    unsigned long long mask[3];
    int k;
    int tc;
    void *node;
    int row, col;

    func_ov025_02086ff0(self);
    tc = func_ov025_020858d0(0);
    self[0x3d] = 0;
    self[0x3c] = 0;
    self[0x3a] = 0;
    if (func_020342b4(tc) == 0) {
        func_02034150(tc, 0xe);
        self[0x3d] = 1;
    }
    if (func_020342b4(0x14) == 0) {
        func_02034150(0x14, 0xe);
        self[0x3c] = 1;
    }
    if (func_020342b4(0x13) == 0) {
        func_02034150(0x13, 0xe);
        self[0x3a] = 1;
    }
    for (node = NNS_FndGetNextListObject(list, 0); node != 0;
         node = NNS_FndGetNextListObject(list, node)) {
        func_ov025_02086744(self, *(unsigned short *)((char *)node + 0xa) * 0xa0 + base, node,
                            *(unsigned short *)((char *)node + 0xa));
        self[0] += *(unsigned short *)((char *)node + 8);
    }
    MIi_CpuCopy32((char *)self + 0xcc, mask, 0x18);
    for (k = 0; k < 3; k++, base += 0xa0) {
        func_ov025_02086cb8(self, base, ((struct Self *)self)->pairs[k].a,
                            ((struct Self *)self)->pairs[k].b, &mask[k]);
    }
    self[1] = 0;
    for (k = 0; k < 3; k++) {
        for (row = 0; row < 8; row++) {
            for (col = 0; col < 5; col++) {
                if ((mask[k] & (1ULL << (col + row * 5))) != 0) {
                    self[1]++;
                }
            }
        }
    }
    for (node = NNS_FndGetNextListObject((char *)self + 8, 0); node != 0;
         node = NNS_FndGetNextListObject((char *)self + 8, node)) {
        if (*(int *)((char *)node + 0x14) == 0) {
            *(int *)((char *)node + 0x14) = 1;
        }
        if (*(int *)((char *)node + 0x10) == 0) {
            *(int *)((char *)node + 0x10) = 1;
        }
    }
    func_ov025_0208595c((char *)self + 0x2c);
    if (self[0x3a] != 0) {
        func_02034258(0x13);
        self[0x3a] = 0;
    }
    if (self[0x3c] != 0) {
        func_02034258(0x14);
        self[0x3c] = 0;
    }
    if (self[0x3d] != 0) {
        func_02034258(tc);
        self[0x3d] = 0;
    }
}
