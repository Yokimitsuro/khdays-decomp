/* func_ov263_020d1e70 -- the two-shot tick: track the aim point, then fire each of the two
 * projectiles as its own moment in the timer arrives.
 *
 * The aim reference is the point at *(ctx[0]+0x388)+0x2c with its X zeroed -- so the shot is
 * aimed straight down the owner's own axis, not at the raw target. func_ov263_020d06bc turns it
 * into the tracked point cached at ctx+0x30.
 *
 * The timer at +0x28 drives everything:
 *   past 0xff0  -- and only while the one-shot flag at +0x54 is set -- effect 1 fires once;
 *   past 0x1298 with two left to fire, or past 0x18f8 with one left, releases the next one.
 * The counter at +0x4b counts DOWN, and it also selects which muzzle (ctx[0]+0x38c+n*4) and which
 * side the shot spins (-1 for the last one, +1 otherwise). A muzzle whose low byte at +0x60 has
 * bit 0 set is already busy and the shot is dropped.
 *
 * The direction handed to func_ov263_020d2d40 is {sin, ctx[0x10], cos} -- the Q12 heading at
 * +0x18 gives the ground plane and +0x40 supplies the Y directly (see codegen-cracks.md for the
 * conversion).
 *
 * The state ends when the gate at *ctx[4] clears: if BOTH muzzles are then free it means neither
 * shot is still alive, so play move 2 and re-enter; otherwise fire mode 1 on the owner and on
 * *(ctx[0]+0x388) and let them finish.
 *
 * data_02041dc8 is a 12-byte vector passed BY VALUE (the `sub r3,sp,#8` straddle). */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* The low-byte bit test must go through the bitfield (ldrh; lsl#0x18; lsr#0x18; tst #1);
 * writing *(u16*)p & 0xff & 1 collapses it to ldrb; tst -- see codegen-cracks.md. */
typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

extern void func_ov263_020d06bc(VecFx32 *out, int self, const VecFx32 *ref);
extern void func_ov107_020c0b90(int owner, int effect, VecFx32 v, int a);
extern void func_ov263_020d0628(int self);
extern void func_ov263_020d2d40(int muzzle, int a, const VecFx32 *dir, signed char spin, int pt);
extern void func_0203c634(int self, int action, void *cb);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov107_020c9ee8(int owner, int mode, int arg);
extern VecFx32 data_02041dc8;
extern short data_0203d210[];

void func_ov263_020d1e70(int self) {
    int *ctx;
    /* Reverse of their stack order: out at sp+8, dir at sp+0x14, ref at sp+0x20. */
    VecFx32 ref;
    VecFx32 dir;
    VecFx32 out;
    int idx;

    ctx = *(int **)(self + 4);
    ref = *(VecFx32 *)(*(int *)(ctx[0] + 0x388) + 0x2c);
    ref.x = 0;

    ctx[0xa] += *(int *)(*(int *)self + 0x2c);
    func_ov263_020d06bc(&out, self, &ref);
    *(VecFx32 *)((char *)ctx + 0x30) = out;

    if (ctx[0xa] >= 0xff0 && ctx[0x15] != 0) {
        func_ov107_020c0b90(ctx[0], 1, data_02041dc8, 0);
        ctx[0x15] = 0;
    }

    if ((ctx[0xa] >= 0x1298 && *(unsigned char *)((char *)ctx + 0x4b) == 2)
        || (ctx[0xa] >= 0x18f8 && *(unsigned char *)((char *)ctx + 0x4b) == 1)) {
        func_ov263_020d0628(self);
        /* The counter field is read directly at each use rather than cached in a local: the ROM
         * re-reads it (ldrb) for the muzzle select, and a local gets CSEd into one load. */
        *(unsigned char *)((char *)ctx + 0x4b) -= 1;

        if ((((Hw60 *)(*(int *)(ctx[0] + *(unsigned char *)((char *)ctx + 0x4b) * 4 + 0x38c) + 0x60))->lo
             & 1)
            == 0) {
            idx = (unsigned short)(((long long)ctx[6] * 0x28be60db9391LL + 0x80000000000LL) >> 44)
                  >> 4;
            dir.y = ctx[0x10];
            dir.x = data_0203d210[idx * 2];
            dir.z = data_0203d210[idx * 2 + 1];

            func_ov263_020d2d40(*(int *)(ctx[0] + *(unsigned char *)((char *)ctx + 0x4b) * 4 + 0x38c),
                                ctx[3], &dir,
                                *(unsigned char *)((char *)ctx + 0x4b) == 1 ? -1 : 1,
                                ctx[5] + 0x190);
        }
    }

    if (*(unsigned char *)ctx[4] != 0) {
        return;
    }

    if ((((Hw60 *)(*(int *)(ctx[0] + 0x38c) + 0x60))->lo & 1) == 0
        || (((Hw60 *)(*(int *)(ctx[0] + 0x390) + 0x60))->lo & 1) == 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    func_ov107_020c9264(ctx[0], 1, 0);
    func_ov107_020c9ee8(*(int *)(ctx[0] + 0x388), 1, 0);
}
