/* ov296 twin of func_ov295_020d3a6c. ov295 and ov296 are byte-identical
 * overlays; this is the same NONMATCHING C with the shared relative
 * offsets and every ov295-internal address rebased +0x1e20. */
/* ov295 (byte-identical with ov296) — countdown/advance state handler (344B).
 * Ticks a timer down by the sampled advance, latches sub-state 3 at zero, and on
 * a live contact toggles the facing bit and re-issues the walk with a fresh dir. */
extern unsigned int func_020c89e8(int param, unsigned int *param_3);
extern void func_020c5af8(int a, int b, int c, int d);

int func_ov296_020d588c(int param_1, int param_2, unsigned int *param_3) {
    int *piVar6 = *(int **)(param_1 + 0x214);
    unsigned int uVar2;
    int iVar3, iVar5;
    if (*(short *)(param_1 + 0x21a) <= 0)
        return 0;
    uVar2 = func_020c89e8(param_1, param_3);
    param_3[0xa] = uVar2;
    iVar3 = (int)*(short *)(param_1 + 0x21a) - uVar2;
    if (iVar3 < 0) {
        iVar5 = 0;
    } else {
        iVar5 = *(short *)(param_1 + 0x218);
        if (iVar3 <= *(short *)(param_1 + 0x218))
            iVar5 = iVar3;
    }
    *(short *)(param_1 + 0x21a) = (short)iVar5;
    if (*(short *)(param_1 + 0x21a) == 0)
        *(char *)(*piVar6 + 0x1c7) = 3;
    if ((int)param_3[0xa] > 0) {
        unsigned int f = (unsigned short)param_3[0];
        if (f & 8) {
            if (f & 0x80) {
                if ((param_3[0] >> 0x10) != 0x80) {
                    unsigned int bVar1 = *(unsigned char *)((char *)piVar6 + 0xc);
                    unsigned int sh = bVar1 << 0x1f;
                    if ((f & 0x22) == 0) {
                        unsigned int nv = bVar1 & 0xfe | ((sh >> 0x1f) + 1 & 1);
                        *(unsigned char *)((char *)piVar6 + 0xc) = (unsigned char)nv;
                        func_020c5af8(param_1, 0x171, ((nv & 0xff) << 0x1f) >> 0x1f ? 0 : 1, piVar6[1]);
                    } else {
                        unsigned int nv = bVar1 & 0xfe | ((sh >> 0x1f) + 1 & 1);
                        *(unsigned char *)((char *)piVar6 + 0xc) = (unsigned char)nv;
                        func_020c5af8(param_1, 0x171, ((nv & 0xff) << 0x1f) >> 0x1f ? 2 : 3, piVar6[1]);
                    }
                }
            }
        }
    }
    return 1;
}
