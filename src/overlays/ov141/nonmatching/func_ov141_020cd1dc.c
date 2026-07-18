/* NONMATCHING -- 212/212 B, 4 bytes (one register pair) apart. Head of a 5-member family.
 *
 * SOLVED here -- do NOT rediscover:
 *  - the Q12 radians -> angle -> sin/cos block is the documented form and reproduced whole.
 *  - `v[1] = 0;` must come AFTER the two table reads, not before. Ghidra shows it first, and
 *    that ordering costs 30 differing bytes (37 -> 7) because it materialises the zero into
 *    the wrong register and the whole Q12 block re-colours around it.
 *  - the guard reads its byte UNSIGNED (`ldrb`), not signed.
 *  - the RNG copy artifact `+ (w - w)` is needed on the func_02023eb4 result.
 *
 * LEFT: the ternary result and the owner pointer are in swapped registers (ROM r1/r0, mwcc
 * r2/r1). Ruled out: giving the ternary result its own local, hoisting the destination into a
 * `signed char *` (that one is 4 B long), and declaring `r` inside the if.
 *
 * ⚠ Measured by DIFFERING BYTES throughout, not by verify_idx's first-difference offset --
 * the offset moved the wrong way on the winning variant. */
extern void func_01ffa724(int scale, int *v, unsigned int *out);
extern int  func_02023eb4();
extern void func_0203c634(int self, int index, void *cb);
extern short data_0203d210[];

void func_ov141_020cd1dc(int self) {
    int *obj = *(int **)(self + 4);
    int v[3];
    int idx;
    int r;

    idx = (unsigned short)(((long long)obj[2] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    v[0] = data_0203d210[idx * 2];
    v[2] = data_0203d210[idx * 2 + 1];
    v[1] = 0;
    func_01ffa724(0x300, v, (unsigned int *)(obj + 6));
    if (*(unsigned char *)obj[0x11] == 0) {
        int w;
        r = func_02023eb4(0x65) + (w - w);
        *(signed char *)(*obj + 0x1c7) = r < 0x28 ? 6 : 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    }
}
