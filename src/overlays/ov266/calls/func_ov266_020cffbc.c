/* "Is the target outside the facing cone?" (x3: ov212/266/267). With no target,
 * answer no. Otherwise take the heading from the anchor (ctx[2]) to the target
 * (target+0x190) FLATTENED to the XZ plane, turn it into a Q12-radian angle, and
 * compare it against the stored heading (ctx+0x34): convert both to sin/cos table
 * entries and dot them, which is cos(measured - stored); acos that (0203cd20) and
 * report whether the absolute difference exceeds 0x1ac (~24 degrees).
 *
 * Two spellings are load-bearing:
 *  - The guard must be written as `if (tgt != 0) { ...; return ...; } return 0;`.
 *    The natural `if (tgt == 0) return 0;` makes mwcc predicate the early exit
 *    inline (addeq/moveq/popeq, 1 instruction short); the ROM branches to a shared
 *    out-of-line `return 0` at the end.
 *  - `d.y = 0` is a DEAD store -- d is never read again after d.x/d.z -- but the ROM
 *    emits it, so it stays. */
struct vec3 { int x, y, z; };

extern int *func_ov107_020cab14(int a, int b);
extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int a, int b);
extern int func_0203cd20(int c);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

int func_ov266_020cffbc(void *self) {
    int *ctx = *(int **)((char *)self + 4);
    struct vec3 d;
    int *tgt = func_ov107_020cab14(*ctx, 0);
    unsigned int ia, im;
    int a, ang;

    if (tgt != 0) {
        VEC_Subtract((char *)tgt + 0x190, (void *)ctx[2], &d);
        d.y = 0;
        a = func_020050b4(d.x, d.z);
        ia = ANG2IDX(ctx[0xd]);
        im = ANG2IDX(a);
        ang = func_0203cd20(FX_MUL(data_0203d210[im * 2], data_0203d210[ia * 2]) +
                            FX_MUL(data_0203d210[im * 2 + 1], data_0203d210[ia * 2 + 1]));
        if (ang < 0) {
            ang = -ang;
        }
        return ang > 0x1ac;
    }
    return 0;
}
