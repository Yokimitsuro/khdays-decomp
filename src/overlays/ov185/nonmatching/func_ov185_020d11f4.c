/* UNFINISHED -- 716/716 bytes, 179/179 instructions. Everything is correct except ONE allocator
 * choice, which then rotates three registers through the whole function. Worth 3 functions: the
 * twins ov186_020d3014 / ov187_020d6c54 are byte-identical modulo relocs and unlock via dedupprop
 * the moment this lands. (2026-07-17)
 *
 * WHAT IS ALREADY RIGHT -- do not re-derive any of it:
 *   - size, every constant, every branch target, and the ENTIRE stack layout (sp+8 / 0xc / 0x18 /
 *     0x3c / 0x4c / 0x58 all land exactly, so the local declaration order for the aggregates is
 *     correct: first-declared = highest address).
 *   - `pi` as a LOCAL is load-bearing and cost 12 bytes to find. Spelling `0x3244` twice lets mwcc
 *     fold `0x3244 * 2` into 0x6488, pool it a SECOND time, and branch instead of predicate. As a
 *     value it stays in the register the compare loaded and the wrap becomes `subgt r0,r1,r0,lsl#1`.
 *   - the hw60 `hi &= ~6` DOES carry the `lsl#0x10 ; lsr#0x10` trunc pair -> bitfield form (right).
 *   - the guard is a `||` of the negations; each failing test branches to the shared move-2 block.
 *
 * THE ONE DIFFERENCE, and where it starts (read this before touching anything):
 *   ROM:  r4 = ctx, r5 = self, r6 = lo, and `ip` caches ctx[0x1d] for the guard  (0x034)
 *   mine: r5 = ctx, r6 = self, r4 = lo, and r4 also caches ctx[0x1d]            (0x034)
 * mwcc COALESCES the guard's ctx[0x1d] cache and `lo` into r4 -- their live ranges are disjoint, so
 * this is legal and arguably smarter. The ROM instead spends `ip` (caller-saved, free because the
 * guard contains no call) on the cache and keeps r6 for lo. That single choice at 0x034 pushes ctx
 * to r5 and self to r6, and every later diff is downstream of it (including the Pair16 copy taking
 * +4/+6 in the other order, and `add r4,r5,#0x18` appearing in the hw60 block).
 *
 * RULED OUT -- four declaration arrangements, all byte-IDENTICAL output, so this is NOT decl-order
 * driven the way `WalkRecords` was:
 *   1. lo/d declared after ctx (original)      3. lo/d declared FIRST, before ctx
 *   2. lo/d block-scoped inside the guard      4. ctx as a declaration-initialiser
 * Also ruled out: `dist` must stay a variable computed BEFORE the guard (the ROM calls
 * func_01ff8d18 unconditionally at 0x02c and only compares at 0x06c, so it cannot be inlined into
 * the 4th `||` term without changing when the call happens).
 *
 * NEXT IDEA (untried): find a source form that makes the guard's ctx[0x1d] cache land in a
 * caller-saved register instead of being coalesced with `lo`. Same class as
 * func_ov158_020cd174 (r6/r7 swap, ~10 attempts) -- but note that one is a PAIR swap and this is a
 * three-way rotation with a clear, identified origin, so it is not obviously the same tie. Do not
 * fold this into the mwcc-build theory: state.md's own retraction says that tally is 50/50.
 *
 * ---- what it does ----------------------------------------------------------------------------
 *
 * The orbit tick: circle the target on a spinning offset, keep facing it, and hand off once the
 * target's own state says the pass is over.
 *
 * Shape family of 3: ov185_020d11f4 / ov186_020d3014 / ov187_020d6c54.
 *
 * ctx[0x1d] is the thing being orbited, ctx[0x11] our own position.
 *
 * First a bail-out test. The orbit only continues while ALL of these hold, and the FIRST thing
 * that fails queues move 2 and dispatches instead:
 *     the target shares our owner (*(int *)(target + 4) == *(int *)(ctx[0] + 4))
 *     *(u16 *)(*(int *)(target + 0x18c) + 0x12) is non-zero
 *     bit 0 of the target's hw60 low byte is set
 *     we are within 0x2c00 of it
 *     bit 1 of *(u8 *)(ctx[0] + 0x1c4) is CLEAR
 * Written as a `||` of the negations because that is how the ROM branches: each failing test jumps
 * forward to the shared move-2 block, and only the last one falls through into the body.
 *
 * The body:
 *   - spin the offset vector at ctx+0x84 by a quaternion built from axis ctx[0x1e] and the running
 *     angle ctx[0x18], add it to the target's position, and steer toward the result at 15x the
 *     frame delta. ctx[0x18] advances by delta*30/4 per tick and wraps by subtracting 2*PI once it
 *     passes PI (0x3244) -- so the orbit is a fixed circle around the target, not a chase.
 *   - rebuild our orientation from func_0203cd7c/func_0202ea48 into ctx[6].
 *   - every 0x800 of accumulated delta (ctx[0xe]) fire func_ov107_020ca918.
 *
 * Then read the target's flags at +0x1e4:
 *   & 3 -> the pass is over: push a 4-byte record from data_ov185_020d16a0[1] through the callback
 *          at ctx[0]+0x24 (if set), clear hw60 hi bits 1|2, latch the current heading into
 *          ctx[0x19..0x1b] with a 0x400 rate, rebuild ctx[6] to face it, copy that into ctx[2],
 *          and continue at func_ov185_020d14c0.
 *   & 4 -> queue move 2 and dispatch.
 *   else -> keep orbiting.
 *
 * The hw60 `hi &= ~6` here DOES carry the `lsl #0x10 ; lsr #0x10` trunc pair, so it wants the
 * BITFIELD form, not the explicit extract/reassemble (codegen-cracks.md). Read the pair off the
 * disassembly -- the sibling write in ov221's EnterChargeState has no pair and needs the opposite
 * spelling.
 *
 * `func_02023eb4(d + 1) + lo` keeps the addend as a real add (the RNG returns long long). */

typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quaternion;

typedef struct {
    int m[9];
} MtxFx33;

typedef struct {
    u16 a;
    u16 b;
} Pair16;

typedef struct {
    u16 lo : 8;
    u16 hi : 8;
} Hw60;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern int func_02023eb4();
extern void func_0203c634(int self, int slot, void *cb);
extern void func_0202f188(Quaternion *dst, const VecFx32 *axis, int angle);
extern void func_0202f384(VecFx32 *dst, const Quaternion *q, const VecFx32 *v);
extern void func_01ffa724(int scale, const VecFx32 *src, VecFx32 *dst);
extern void func_0203cd7c(MtxFx33 *m, const VecFx32 *a, const VecFx32 *b, const VecFx32 *c);
extern void func_0202ea48(Quaternion *q, const MtxFx33 *m);
extern int func_020050b4(int x, int z);
extern void func_ov107_020ca918(int a, int b, int c, int d, const VecFx32 *e, int f);
extern void func_ov185_020d14c0(void);
extern VecFx32 data_020475ac;
extern VecFx32 data_02042264;
extern VecFx32 data_02041dc8;
extern Pair16 data_ov185_020d16a0[];

void func_ov185_020d11f4(int self) {
    int *ctx = *(int **)(self + 4);
    int lo;
    int d;
    VecFx32 offset;
    VecFx32 aimPos;
    Quaternion spin;
    MtxFx33 m;
    VecFx32 toTarget;
    Pair16 rec;
    int dist;
    int pi;
    int flags;
    void (*cb)(int, const Pair16 *, int);

    VEC_Subtract((const VecFx32 *)(ctx[0x1d] + 0x190), (const VecFx32 *)ctx[0x11], &toTarget);
    dist = func_01ff8d18(&toTarget, &toTarget);

    if (*(int *)(ctx[0x1d] + 4) != *(int *)(ctx[0] + 4) ||
        *(u16 *)(*(int *)(ctx[0x1d] + 0x18c) + 0x12) == 0 ||
        (((Hw60 *)(ctx[0x1d] + 0x60))->lo & 1) == 0 || dist > 0x2c00 ||
        (*(unsigned char *)(ctx[0] + 0x1c4) & 2) != 0) {
        lo = *(int *)(ctx[0] + 0x224);
        d = *(int *)(ctx[0] + 0x228) - lo;
        if (d < 0) {
            d = -d;
        }
        ctx[0x10] = func_02023eb4(d + 1) + lo;
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }

    func_0202f188(&spin, (const VecFx32 *)((int)ctx + 0x78), ctx[0x18]);
    ctx[0x18] += *(int *)(*(int *)self + 0x2c) * 30 / 4;
    /* PI held in a local, not spelled `0x3244` twice: mwcc folds the literal `0x3244 * 2` into
     * 0x6488 and pools it a SECOND time, then branches instead of predicating (+12 B). As a value
     * it stays in the register the compare already loaded, and the wrap becomes the ROM's
     * `subgt r0, r1, r0, lsl #1`. */
    pi = 0x3244;
    if (ctx[0x18] > pi) {
        ctx[0x18] = ctx[0x18] - pi * 2;
    }
    func_0202f384(&aimPos, &spin, (const VecFx32 *)((int)ctx + 0x84));
    VEC_Add((const VecFx32 *)(ctx[0x1d] + 0x74), &aimPos, &aimPos);
    VEC_Subtract(&aimPos, (const VecFx32 *)ctx[0x11], &offset);
    func_01ffa724(*(int *)(*(int *)self + 0x2c) * 15, &offset, (VecFx32 *)((int)ctx + 0x2c));

    func_0203cd7c(&m, &data_020475ac, (const VecFx32 *)ctx[0x11], &data_02042264);
    func_0202ea48((Quaternion *)((int)ctx + 0x18), &m);

    ctx[0xe] += *(int *)(*(int *)self + 0x2c);
    if (ctx[0xe] >= 0x800) {
        ctx[0xe] = 0;
        func_ov107_020ca918(ctx[0x1d], ctx[0], ctx[0], 0, &data_02041dc8, 0x10);
    }

    flags = *(int *)(ctx[0x1d] + 0x1e4);
    if ((flags & 3) != 0) {
        rec = data_ov185_020d16a0[1];
        cb = *(void (**)(int, const Pair16 *, int))(ctx[0] + 0x24);
        if (cb != 0) {
            cb(ctx[0], &rec, 4);
        }
        ((Hw60 *)(ctx[0] + 0x60))->hi &= ~6;
        ctx[0x19] = ctx[0xb];
        ctx[0x1a] = 0x400;
        ctx[0x1b] = ctx[0xd];
        func_0202f188((Quaternion *)((int)ctx + 0x18), &data_02042264,
                      func_020050b4(ctx[0xb], ctx[0xd]));
        *(Quaternion *)((int)ctx + 8) = *(Quaternion *)((int)ctx + 0x18);
        func_0203c634(self, *(signed char *)(self + 0x20), func_ov185_020d14c0);
        return;
    }
    if ((flags & 4) != 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
    }
}
