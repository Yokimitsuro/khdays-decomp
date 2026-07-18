/* The 0x60 test reads the hw60 LOW byte through the bitfield (`->lo & 1`), which is what
 * gives the ROM's lsl#24/lsr#24 before the test; a plain `*(u16 *)(self+0x60) & 1` folds
 * to `tst #1` and is 8 B short. The state check is four explicit `!=` comparisons, not
 * `> 1`, and both byte reads are SIGNED (ldrsb). */
struct Hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c650(int a, int b);
extern void func_ov107_020cb100();
extern void func_ov107_020c7ca4(int self);

void func_ov199_020d3df4(int self) {
    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0) {
        if (*(int *)(self + 0x3f4) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3f4));
            *(int *)(self + 0x3f4) = 0;
        }
        if (*(signed char *)(self + 0x1c7) == -1) {
            signed char s = *(signed char *)(self + 0x1c6);
            if (s != 0 && s != 1 && s != 3 && s != 6) {
                if (*(int *)(self + 0x3ec) != 0) {
                    func_ov107_020cb100();
                    *(int *)(self + 0x3ec) = 0;
                }
                *(signed char *)(self + 0x1c7) = 6;
            }
        }
    }
    if ((((struct Hw60 *)(self + 0x60))->lo & 1) == 0) {
        if (*(int *)(self + 0x3ec) != 0) {
            func_ov107_020cb100();
            *(int *)(self + 0x3ec) = 0;
        }
        if (*(int *)(self + 0x3f4) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3f4));
            *(int *)(self + 0x3f4) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}
