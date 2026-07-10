/*
 * NONMATCHING (register-allocation tie, size-exact byte-diff @0x9). Twin of the
 * matched 02089384 (5-word table struct-copy + guarded call loop), but the extra
 * (short)param_2 sign-extend shifts the whole allocation: the original keeps
 * param_1 in r9/param_2 in r8, mwcc uses r8/r4, and the table-base/DAT-ptr/iVar2
 * registers cascade differently. Tried hoisting (short)param_2 into a local.
 * Byte-equivalent; this 132B+ tier is coloring-dominated.
 */
extern void func_0202accc(int a, unsigned int b, int c, int d);
extern void func_01fff774(unsigned short *a, unsigned int b, int c);

struct tbl5_020892f0 {
    unsigned int v[5];
};
extern struct tbl5_020892f0 data_ov022_020b236c;

void func_ov022_020892f0(unsigned short *param_1, int param_2) {
    struct tbl5_020892f0 tbl = data_ov022_020b236c;
    int p2 = (short)param_2;
    int iVar2 = 0;
    do {
        unsigned int uVar3 = tbl.v[iVar2];
        unsigned int uVar1 = uVar3 & 0xffff;
        if (0 < (short)param_1[uVar1 + 0x70]) {
            func_0202accc((int)param_1, uVar1, (int)(param_1 + 0x70), p2);
            func_01fff774(param_1, uVar3 & 0xffff, 0);
        }
        iVar2 = iVar2 + 1;
    } while (iVar2 < 5);
}
