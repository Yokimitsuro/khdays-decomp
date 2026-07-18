/* NONMATCHING -- 372 vs 380 B. Head of a 5-member family (380 B). Much closer than the
 * first pass (364); the whole comparison/ternary region and the register allocation now
 * match, only the stack LAYOUT and 8 bytes remain.
 *
 * SOLVED here -- do NOT rediscover:
 *  - Ghidra's five DAT_arm9_ov147__020cc17x: three are POOL LITERALS (0x244d, 0xffffdbb3,
 *    0x10c1), only two are relocs. Cross-check the reloc table against the pool offsets.
 *  - the two vec stores go through a STACK TEMPORARY (`add r5,sp,#0 ; ldm ; stm`), not two
 *    reads of the global. That fixed the frame (0x48 -> 0x54) and the push list at once.
 *  - `*(unsigned char *)(self + 0xad)`, NOT signed: the ROM uses ldrb.
 *  - the gate is `k == 0 || k == 1`, not `k < 2` -- the ROM emits `cmp #0 ; cmpne #1`.
 *    (deferred-ties lists the reverse direction as a tie; in THIS direction it works.)
 *  - the distance test is `> 0x4800`, not `< 0x4801`. The 0x4801 form loads the constant
 *    from the pool, and mwcc then DERIVES the two +-constants from that register
 *    (`subgt r0,r1,#0x3740`) instead of the ROM's `ldrgt` + `mvnle`. One wrong constant
 *    form poisoned three instructions downstream.
 *  - the selections are `field > 0 ? K : -K` (positive case first), and the `> 0x4800`
 *    branch takes the 0x10c1 block -- swapping the condition without swapping the blocks
 *    inverts the semantics.
 *
 * LEFT: 8 bytes and the stack offsets. The ROM has z at sp+0, dir at sp+0xc, tmp at
 * sp+0x18, buf at sp+0x24; mwcc puts buf at sp+0xc. Ruled out: all 24 permutations of the
 * four local declarations (scripted, twice -- once before and once after the fixes above),
 * z in an inner block vs at function scope, and buf sizes 12/13/14/15. */
struct vec { int x, y, z; };
extern void func_0203bc78();
extern int  func_02016320();
extern void VEC_Subtract();
extern int  func_01ff8d18();
extern void func_0203b9fc();
extern void func_0202f188();
extern struct vec data_02042264;
extern struct vec data_02041dc8;

void func_ov147_020cc00c(int self, int a, int b, int c) {
    int o = *(int *)(self + 0x84);
    struct vec dir;
    struct vec tmp;
    int buf[12];
    int n;

    func_0203bc78(self, a, b, c);
    if (func_02016320(*(int *)(self + 0x88) + 0x20, buf, 0, *(unsigned int *)(o + 0x3d0)) != 0) {
        tmp = *(struct vec *)&buf[9];
        if (*(int *)(o + 0x3e4) == 0) {
            VEC_Subtract(&tmp, o + 0x3a4, o + 0x3b0);
        }
        *(struct vec *)(o + 0x3a4) = tmp;
        *(int *)(o + 0x3e4) = 0;
    }
    if (*(unsigned char *)(self + 0xad) == 0) {
        unsigned int k = (unsigned int)*(short *)(*(int *)(self + 0x88) + 2);
        if ((k == 0 || k == 1) && *(int *)(o + 1000) != 0) {
            if (*(int *)(o + 0x394) != 0) {
                VEC_Subtract(*(int *)(o + 0x394) + 400, o + 0xb0, &dir);
                if (func_01ff8d18(&dir, &dir) > 0x4800) {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) > 0 ? 0x10c1 : -0x10c1;
                } else {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) > 0 ? 0x244d : -0x244d;
                }
            }
            func_0203b9fc(self, 0, k, 0);
            n = -*(int *)(o + 0x3bc);
            *(int *)(o + 0x3bc) = n;
            func_0202f188(o + 0x3c0, &data_02042264, n);
        }
        {
            struct vec z = data_02041dc8;
            *(struct vec *)(o + 0x3a4) = z;
            *(struct vec *)(o + 0x3b0) = z;
        }
        *(int *)(o + 0x3e4) = 1;
    }
}
