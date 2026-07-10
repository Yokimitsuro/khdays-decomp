/*
 * NONMATCHING (single mla-result register tie, size-exact byte-diff @0x6A).
 * Fully matched otherwise: struct-copy for the 3-word block, a 2-bit bitfield
 * read for the `& 3` before the `tst #2` guard, and the `|= 0x20` slot update.
 * The only divergence is `addr = iVar1*0x114 + *(pbVar2+0xc)`: the original
 * reuses the base register r2 for the mla result, mwcc reuses the 0x114 reg r1.
 * Tried operand-order swaps and split base/add. Byte-equivalent.
 */
struct blk3_020893f4 {
    int a;
    int b;
    int c;
};

struct pbits_020893f4 {
    unsigned char f01 : 2;
    unsigned char rest : 6;
};

extern void func_ov022_02088e50(int a, struct blk3_020893f4 *b, int c, struct blk3_020893f4 *d);
extern int func_ov022_020891d4(int a, struct blk3_020893f4 *b);

void func_ov022_020893f4(int param_1, struct blk3_020893f4 *param_2, short param_3, int param_4) {
    unsigned char *pbVar2 = *(unsigned char **)(param_1 + 0x20);
    struct blk3_020893f4 buf;
    int iVar1;
    buf = *param_2;
    if ((((struct pbits_020893f4 *)pbVar2)->f01 & 2) != 0) {
        func_ov022_02088e50(param_1, &buf, *(int *)(pbVar2 + 0x1c), &buf);
    }
    iVar1 = func_ov022_020891d4(param_1, &buf);
    if (iVar1 != -1) {
        int addr = iVar1 * 0x114 + *(int *)(pbVar2 + 0xc);
        *(short *)(addr + 0x80) = param_3;
        *(unsigned short *)(addr + 4) = *(unsigned short *)(addr + 4) | 0x20;
    }
}
