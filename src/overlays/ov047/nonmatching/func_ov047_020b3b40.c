/* NONMATCHING -- 88/88 B, 7 differing bytes: a register permutation plus one scheduling
 * difference (the ROM computes `row + off` before the call, mwcc after). Head of a 4-member
 * family.
 *
 * SOLVED here -- do NOT rediscover:
 *  - the shared base must be a `char *` (`(char *)self + 0x2000`). As an `int` it is 4 B long,
 *    and without it 8 B long: mwcc then splits 0x63c into `add #0x23c` + `ldr [#0x400]`.
 *  - declaration order matters and was swept: 60 legal permutations, best three give 7 bytes,
 *    the base ordering used here (i, p, base, obj, off) among them; the worst give 15.
 *
 * Ruled out: hoisting the destination `int *dst` above the call (14 bytes, worse).
 * All measured with tools/bytedist.py. */
extern void WM_EndKeySharing_0x020b15a4(int a, int b);
extern int data_ov047_020b4380;

void func_ov047_020b3b40(int self) {
    int i = 0;
    int p = *(int *)&data_ov047_020b4380 + 0x2d78;
    char *base = (char *)self + 0x2000;
    int obj = *(int *)(base + 0x644);
    int off = 0;

    do {
        int row = *(int *)(obj + 0xc);
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), p);
        i = i + 1;
        *(int *)(row + off + 0x130) = p;
        off = off + 0x1c8;
        p = p + 0x24;
    } while (i < 10);
}
