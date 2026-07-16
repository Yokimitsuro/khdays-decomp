/* func_ov208_020d1be0 -- ov208's move CHOOSER (see func_ov206_020cde58 for the family).
 *
 * A dispatcher reads the queued move at ctx[0]+0x1c7 and runs it; this decides what to queue there.
 * Every exit writes +0x1c7 and calls func_0203c634 with a NULL handler, i.e. "run what is queued".
 *
 * Both vectors are FLATTENED to the XZ plane (`[1] = 0`) -- this AI reasons purely in the ground
 * plane, so height never affects the choice. The facing vector is not normalised like ov206's:
 * after the transform its X and Z are overwritten straight from the sin/cos table, indexed by the
 * heading angle in ctx[0xc]. That already leaves it unit-length, which is why the dot product
 * against the (normalised) direction to the target is a valid cosine.
 *
 * With no target it queues move 2. Otherwise, unless the busy byte at *(ctx[1] + 0xad) is set, it
 * rolls a d100:
 *
 *   roll < 20        -> move 10
 *   roll < 60        -> move 5
 *   otherwise, close (gap < 0x5333): move 6 only if the target is ahead, else nothing
 *              far  (gap >= 0x5333): ahead -> move 5
 *                                    else  -> a second d100: <50 move 10, else move 9
 *
 * "Ahead" here is VEC_DotProduct(toTarget, forward) > 0x800: Q12's 1.0 is 0x1000, so 0.5 = a 60
 * degree cone -- tighter than ov206's 0x200. `gap` is the distance between the two collision radii
 * at +0x80.
 *
 * The second roll's comparison is UNSIGNED where the first is signed; both come straight from the
 * ROM's `bhi`/`blt` and are kept as-is.
 *
 * ctx[0x18] takes `*(int *)(*(int *)self + 0x2c) * 30 / 30` -- the two 30s cancel at runtime and
 * mwcc does not fold them (the multiply can overflow). See func_ov206_020cde58.
 *
 * The angle -> sin/cos conversion is the documented Q12-radians form (codegen-cracks.md):
 * 0x28be60db9391 is 65536/(2*pi) in .32, the +0x800<<32 is rounding, and the (unsigned short) cast
 * is what makes the shifts come out as lsl#4/lsr#16/asr#4. */

extern int func_ov208_020d0ea4(int obj, int kind);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern void VEC_Subtract(const int *a, const int *b, int *dst);
extern int VEC_DotProduct(const int *a, const int *b);
extern int func_01ff8d18(const int *v, int *unit);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(int a, int *out);
extern void func_0202f384(int *dst, const int *a, const int *b);
extern void func_01ffa724(int scale, const int *src, int *dst);
extern int func_02023eb4(int mul);
extern short data_0203d210[];

void func_ov208_020d1be0(int self) {
    int *ctx;
    int toTarget[3];
    int forward[3];
    int target;
    int tgt;
    int *owner;
    int gap;
    int scale;
    int roll;
    unsigned int idx;

    ctx = *(int **)(self + 4);
    ctx[0x18] = *(int *)(*(int *)self + 0x2c) * 30 / 30;

    target = func_ov208_020d0ea4(ctx[0], 0);
    ctx[4] = target;
    if (target == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    VEC_Subtract((const int *)(target + 0x190), (const int *)ctx[2], toTarget);
    toTarget[1] = 0;
    tgt = ctx[4];
    owner = (int *)ctx[0];
    gap = func_01ff8d18(toTarget, toTarget);
    gap -= owner[0x20] + *(int *)(tgt + 0x80);
    ctx[0xd] = func_020050b4(toTarget[0], toTarget[2]);

    scale = func_ov107_020c9f48(*(int *)(ctx[0] + 0x3ac), forward);
    func_0202f384(&ctx[5], (const int *)(ctx[0] + 0xa0), forward);
    func_01ffa724(scale, &ctx[5], &ctx[5]);
    idx = (unsigned short)(((long long)ctx[0xc] * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    forward[0] = data_0203d210[idx * 2];
    forward[1] = 0;
    forward[2] = data_0203d210[idx * 2 + 1];

    if (*(unsigned char *)(ctx[1] + 0xad) != 0) {
        return;
    }

    roll = func_02023eb4(100);
    if (roll < 0x14) {
        *(signed char *)(ctx[0] + 0x1c7) = 10;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (roll < 0x3c) {
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if (gap < 0x5333) {
        if (VEC_DotProduct(toTarget, forward) > 0x800) {
            *(signed char *)(ctx[0] + 0x1c7) = 6;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
        }
        return;
    }

    if (VEC_DotProduct(toTarget, forward) > 0x800) {
        *(signed char *)(ctx[0] + 0x1c7) = 5;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    if ((unsigned int)func_02023eb4(100) < 0x32) {
        *(signed char *)(ctx[0] + 0x1c7) = 10;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    *(signed char *)(ctx[0] + 0x1c7) = 9;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
