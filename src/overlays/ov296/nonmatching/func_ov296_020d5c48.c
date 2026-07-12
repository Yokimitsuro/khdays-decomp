/* ov296 twin of func_ov295_020d3e28. ov295 and ov296 are byte-identical
 * overlays; this is the same NONMATCHING C with the shared relative
 * offsets and every ov295-internal address rebased +0x1e20. */
/* ov295 (byte-identical with ov296) — enemy steering/pathing tick (1100B). Picks a
 * move target: (1) a direct line-of-sight goal, else (2) the nearest of several path
 * candidates via a min-distance loop, else (3) a fallback flag flip. Applies Q12
 * fixed-point displacement to the body position, commits, and updates the facing bits.
 * All idioms proven on the sibling ov301 (Q12 mul, barrel high-byte, bitfield). Large;
 * expected near-match by the whole-fn scheduling/optimization pattern. */
extern int  func_01fff8b8(int a, int b, int *c, int d);
extern void func_01ffd144(int a, int *b, unsigned int *c);        /* ScaleVec3Fixed27 */
extern void func_01ff8d18(unsigned int *a, int *b);               /* Vec3Normalize */
extern void func_020c5c54(int a, void *desc);
extern void func_0202ed60(unsigned int *out, int *tbl, int *src);
extern void func_0203c9d0(unsigned int *a, unsigned int *b);
extern void func_0203c634(int a, int b, int c);                   /* SetIndexedSlot */
extern int  func_020ca414(int a, int *b, unsigned char *c, unsigned int *d);
extern void func_01ff8bc4(int *a, int *b, int *c);
extern int  func_01ff8cb8(int *a);
extern int data_02042264[];

struct wd { unsigned b : 8, rest : 24; };

void func_ov296_020d5c48(int param_1, int param_2, int param_3, int param_4) {
    int *piVar8 = *(int **)(param_1 + 4);
    int iVar4 = *(int *)(*piVar8 + 0x388);
    int iVar9 = *(int *)(*piVar8 + 4);
    unsigned int scr[4];
    unsigned int uVar1, t;
    int local_34, local_30, local_2c, uStack_28;
    int local_40, local_3c, local_38;
    unsigned int local_4c, local_48, local_44;

    ((struct wd *)(iVar4 + 8))->b |= 1;
    local_34 = 0;
    local_30 = 0x1200;
    local_2c = 0;
    uStack_28 = param_4;

    iVar4 = func_01fff8b8(*(int *)(iVar9 + 0x7c), piVar8[1], &local_34, 0);
    if (iVar4 != 0) {
        int iVar5 = *(int *)(iVar4 + 8);
        if (iVar5 == 0 || (*(unsigned short *)(iVar5 + 0x22) & 0xff) == 0) {
            func_01ffd144(*(int *)(iVar4 + 0xc), &local_34, (unsigned int *)&local_34);
            local_4c = (unsigned short)*(short *)(*(int *)(iVar4 + 4) + 0x14);
            local_48 = (unsigned short)*(short *)(*(int *)(iVar4 + 4) + 0x16);
            local_44 = (unsigned short)*(short *)(*(int *)(iVar4 + 4) + 0x18);
            func_01ff8d18(&local_4c, (int *)&local_4c);
            local_40 = *(int *)piVar8[1] + local_34 +
                       (int)(((long long)(int)local_4c * 0x1200 + 0x800) >> 12);
            local_3c = *(int *)(piVar8[1] + 4) + local_30 +
                       (int)(((long long)(int)local_48 * 0x1200 + 0x800) >> 12);
            local_38 = *(int *)(piVar8[1] + 8) + local_2c +
                       (int)(((long long)(int)local_44 * 0x1200 + 0x800) >> 12);
            func_020c5c54(*piVar8, &local_40);
            func_0202ed60(scr, data_02042264, (int *)&local_4c);
            func_0203c9d0((unsigned int *)(*piVar8 + 0xa0), scr);
            uVar1 = *(unsigned short *)(*piVar8 + 0x60);
            t = (((unsigned)uVar1 << 16) >> 24) | 0x40;
            *(unsigned short *)(*piVar8 + 0x60) = uVar1 & 0xff | (unsigned short)((t << 24) >> 16);
            uVar1 = *(unsigned short *)(*piVar8 + 0x60);
            t = ((unsigned)uVar1 << 16) >> 24 & ~0x1e;
            *(unsigned short *)(*piVar8 + 0x60) = uVar1 & 0xff | (unsigned short)((t << 24) >> 16);
            func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
            return;
        }
    }
    {
        int *piVar6 = (int *)piVar8[1];
        unsigned char stackpath[48];
        int cand[3];
        int local_6c, iStack_68, iStack_64, local_60;
        local_6c = piVar6[0];
        iStack_68 = piVar6[1];
        iStack_64 = piVar6[2];
        local_60 = 0x1200;
        iVar4 = func_020ca414(*(int *)(iVar9 + 0x7c), &local_6c, stackpath, (unsigned int *)&local_4c);
        if (0 < iVar4) {
            int best = 0x7fffffff;
            int i = 0;
            unsigned int *pp = (unsigned int *)cand;
            do {
                int d;
                pp = (unsigned int *)((int *)pp + 3);
                func_01ff8bc4(&local_6c, (int *)pp, cand);
                d = func_01ff8cb8(cand);
                if (d < best) {
                    func_01ff8d18((unsigned int *)cand, (int *)&local_4c);
                    best = d;
                }
                i = i + 1;
            } while (i < iVar4);
            best = 0x1200 - best;
            local_40 = *(int *)piVar8[1] +
                       (int)(((long long)(int)local_4c * best + 0x800) >> 12);
            local_3c = *(int *)(piVar8[1] + 4) +
                       (int)(((long long)(int)local_48 * best + 0x800) >> 12);
            local_38 = *(int *)(piVar8[1] + 8) +
                       (int)(((long long)(int)local_44 * best + 0x800) >> 12);
            func_020c5c54(*piVar8, &local_40);
            func_0202ed60(scr, data_02042264, (int *)&local_4c);
            func_0203c9d0((unsigned int *)(*piVar8 + 0xa0), scr);
            uVar1 = *(unsigned short *)(*piVar8 + 0x60);
            t = (((unsigned)uVar1 << 16) >> 24) | 0x40;
            *(unsigned short *)(*piVar8 + 0x60) = uVar1 & 0xff | (unsigned short)((t << 24) >> 16);
            uVar1 = *(unsigned short *)(*piVar8 + 0x60);
            t = ((unsigned)uVar1 << 16) >> 24 & ~0x1e;
            *(unsigned short *)(*piVar8 + 0x60) = uVar1 & 0xff | (unsigned short)((t << 24) >> 16);
            func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
            return;
        }
    }
    {
        int obj = *piVar8;
        if ((int)((unsigned)*(unsigned char *)(obj + 0x17a) << 0x1f) < 0) {
            func_0202ed60(scr, data_02042264, (int *)(obj + 0x124));
            func_0203c9d0((unsigned int *)(*piVar8 + 0xa0), scr);
            uVar1 = *(unsigned short *)(*piVar8 + 0x60);
            t = (((unsigned)uVar1 << 16) >> 24) | 0x40;
            *(unsigned short *)(*piVar8 + 0x60) = uVar1 & 0xff | (unsigned short)((t << 24) >> 16);
            func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
            return;
        }
        uVar1 = *(unsigned short *)(obj + 0x60);
        t = ((unsigned)uVar1 << 16) >> 24 & ~0x48;
        *(unsigned short *)(obj + 0x60) = uVar1 & 0xff | (unsigned short)((t << 24) >> 16);
    }
}
