/* NONMATCHING -- 376 vs 380 B, four bytes short. Head of a 5-member family (380 B).
 *
 * SOLVED on the way here -- do NOT rediscover:
 *  - Ghidra's five DAT_arm9_ov147__020cc17x: three are POOL LITERALS (0x244d, 0xffffdbb3,
 *    0x10c1) and only two are relocs (data_02042264, data_02041dc8). Checking the reloc
 *    table against the pool offsets is what separates them.
 *  - the two `*(struct vec *)(o + 0x3a4) = data_02041dc8;` stores go through a STACK
 *    TEMPORARY: the ROM copies the global to sp+0 once (`add r5,sp,#0 ; ldm ; stm`) and
 *    then copies from there into both destinations. Reading the global twice is 4
 *    instructions AND 12 stack bytes short -- that single change fixed both the frame
 *    (0x48 -> 0x54) and the push list.
 *  - the +-constant selections are `*(int *)(o + 0x3bc) < 1 ? -K : K` with K = 0x244d
 *    and 0x10c1.
 *
 * What is left: 4 bytes, and the locals sit at the wrong stack offsets (ROM has buf at
 * sp+0x24, i.e. 36 bytes of vec3s below it; mine has 12). Ruled out: all 24 permutations
 * of the four local declarations (dir / tmp / z / buf), scripted, and buf[12] / [13] /
 * [14] / [15] (the frame size does not follow the array size). */
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
    if (*(signed char *)(self + 0xad) == 0) {
        unsigned int k = (unsigned int)*(short *)(*(int *)(self + 0x88) + 2);
        if (k < 2 && *(int *)(o + 1000) != 0) {
            if (*(int *)(o + 0x394) != 0) {
                VEC_Subtract(*(int *)(o + 0x394) + 400, o + 0xb0, &dir);
                if (func_01ff8d18(&dir, &dir) < 0x4801) {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) < 1 ? -0x244d : 0x244d;
                } else {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) < 1 ? -0x10c1 : 0x10c1;
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
