/*
 * NONMATCHING (single-register tie, size-exact byte-diff @0x41). The guards
 * (predicated early return on & 0x10000), the two 5-arg calls with the stack
 * buffer, and the cross-overlay func_ov002_02076cc8 all match. Only the halfword
 * load `*(u16)(param_1[0x9b5]+0x12)` differs: the orig reuses the now-dead r1
 * (which held param_1[0x9b0]) for the ldrh, mwcc uses r0. Byte-equivalent.
 */
extern int func_ov002_02076cc8(void);
extern void func_ov022_020a1118(unsigned int *a, int b, int *c, int *d, unsigned int *e);
extern void func_ov022_020a1258(int a, unsigned int *b, int c, unsigned int *d, int e);

int func_ov022_0209e4a4(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3,
                        int param_4) {
    unsigned int auStack_24[3];
    int uVar2 = 0;
    if ((*param_1 & 0x10000) != 0) {
        return 0;
    }
    if (param_1[0x9b0] == 4 && (*(unsigned short *)(param_1[0x9b5] + 0x12) & 0x200) == 0) {
        int *piVar1;
        uVar2 = 1;
        piVar1 = (int *)func_ov002_02076cc8();
        func_ov022_020a1118(auStack_24, (int)param_2, (int *)(param_1 + 0x9b2), piVar1, param_3);
        func_ov022_020a1258((int)param_1, param_2, param_1[0x9b5], auStack_24, 1);
    }
    return uVar2;
}
