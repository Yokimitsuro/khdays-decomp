/* UNFINISHED -- 704/704 bytes, 176/176 instructions. Correct except ONE register swap: the ROM
 * has ctx=r4 / done=r5, mine has ctx=r5 / done=r4, and every later diff is that rename. Worth 5:
 * ov232_020d197c / ov263_020d199c / ov265_020d1990 / ov280_020d199c are byte-identical twins.
 * (2026-07-17)
 *
 * WHAT IS ALREADY RIGHT -- the size, the 4-entry jump table, every constant, the whole 0x30 frame
 * (sp+0 b / sp+0xc a / sp+0x18 w / sp+0x24 v), and the uninitialised-`b` reading described below.
 * It came out 704/704 on the FIRST compile, so the semantics are not in question.
 *
 * RULED OUT -- none of these move the diff off 0x11:
 *   declaration order, 3 ways: done+dir before ctx | done before ctx | ctx last of all
 *   statement order, 4 ways:   v/ctx/done | done/ctx/v | ctx/done/v | ctx as a decl-initialiser
 *   arity: every callee checked against the tree's own call sites -- all agree. That is the axis
 *   which explained SEVEN other "register ties" today, and here it is genuinely clean.
 *
 *   `done` as the literal 0: it does double duty in `ctx[0xa] = done` (case 1) and `dir = done`
 *   (case 2), which was MY choice to reproduce the ROM's `mov r0, r5`. Spelling either or both as
 *   a plain `0` changes nothing -- mwcc CSEs them back into done's register either way. So done's
 *   live range is not what pins the pair.
 *
 * NO IDEA LEFT that I trust. This is the fourth 2026-07-17 function to land as a pure r4/r5-class
 * rotation with 100% correct code (with ov185_020d11f4, ov212_020d1bfc, ov158_020cd174). Note the
 * honest counter-evidence though: today SEVEN other functions that looked exactly like this were
 * arity / mode / placement bugs, and this one's arity is verified clean against the tree. Treat the
 * four as an open question, NOT as proof of a compiler-build difference -- state.md's own
 * retraction is explicit that counting only the failures is how that mistake gets made.
 *
 func_ov231_020cdd3c -- the circling-attack tick: a 4-phase state machine that walks a ring
 * around the target and commits when the angle and the timers line up.
 *
 * One of a 5-member shape family; the twins live in ov232/ov263/ov265/ov280 and are byte-identical
 * modulo relocs (matched here, fanned out with dedupprop).
 *
 * Every tick: seed v from the constant data_ov231_020cfa4c, run it through
 * func_ov231_020cca74(&v, self, &v), publish it to ctx+0x30, and add the frame delta to the timer
 * at ctx[0xa]. Then dispatch on the phase byte at ctx+0x4a (a real 4-entry jump table):
 *
 *   0  turn by dir * PI/2; drop to phase 2 once the range at ctx[8] is under 0x2000;
 *      finish once the timer passes 0x2800
 *   1  ease the point at ctx+0x3c into ctx+0x30 at 0xc00; once the timer passes 0x2800 reset it,
 *      bump the lap counter at ctx+0x48, and finish if either the range is under 0x5000 or we
 *      have done 3 laps
 *   2  the facing check below
 *   3  finish once the timer passes 0x200
 *
 * Phase 2 decides which way to circle. It rotates the owner's forward vector (ctx[0]+0xa0) by
 * data_02042258 into `a`, then takes the Y component of the 2D cross product with `b`:
 *     cross = FX_Mul(b.x, a.z) - FX_Mul(b.z, a.x)
 * and turns that sign into dir = -1 or +1. If that disagrees with the stored dir at ctx+0x4f the
 * heading is corrected by PI/2. Above a range of 0x4800 it returns to phase 0.
 *
 * ⚠ `b` IS GENUINELY UNINITIALISED, and this is faithful, not a transcription slip. Nothing in the
 * function writes sp+0 before phase 2 reads it, and VEC_DotProduct (verified at 0x01ff8bf8: it
 * reads both operands, writes neither, returns the Q12 dot) is called on it with its RESULT
 * DISCARDED. So the ROM reads a junk vector and steers on the sign of a cross product with it --
 * i.e. this enemy's circling direction is decided by whatever was left on the stack. Reproducing
 * it byte-for-byte is the whole point of a matching decomp; for the port, this is a real bug worth
 * flagging rather than "fixing" silently.
 *
 * The tail scales v out to 0x10000 and offers it to func_ov231_020ccb08. On a hit, a counter at
 * ctx+0x4b runs: on its first tick turn by PI, from 9 latch ctx[6], and from 0xb go to phase 3 and
 * finish. Missing clears the counter. Bit 1 of the owner's byte at ctx[0]+0x17a forces a finish.
 * Finishing queues move 2 and dispatches.
 *
 * Q12 constants from the pool: 0x1922 = PI/2, 0x3244 = PI. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void func_ov231_020cca74(VecFx32 *dst, int self, VecFx32 *src);
extern void func_ov231_020cc9e0(int self);
extern void func_01ffa724(int scale, const VecFx32 *src, VecFx32 *dst);
extern void func_0202f384(VecFx32 *dst, const void *q, const VecFx32 *v);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int func_ov231_020ccb08(int self, const VecFx32 *v, int flag);
extern void func_0203c634(int self, int slot, void *cb);
extern VecFx32 data_ov231_020cfa4c;
extern VecFx32 data_02042258;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov231_020cdd3c(int self) {
    int *ctx;
    VecFx32 v;
    VecFx32 w;
    VecFx32 a;
    VecFx32 b;
    int done;
    int dir;

    ctx = *(int **)(self + 4);
    v = data_ov231_020cfa4c;
    done = 0;
    func_ov231_020cca74(&v, self, &v);
    *(VecFx32 *)((int)ctx + 0x30) = v;
    ctx[0xa] += *(int *)(*(int *)self + 0x2c);

    switch (*(unsigned char *)((int)ctx + 0x4a)) {
    case 0:
        func_ov231_020cc9e0(self);
        ctx[7] -= *(signed char *)((int)ctx + 0x4f) * 0x1922;
        ctx[6] = ctx[7];
        if (ctx[8] < 0x2000) {
            *(unsigned char *)((int)ctx + 0x4a) = 2;
        }
        if (ctx[0xa] >= 0x2800) {
            done = 1;
        }
        break;
    case 1:
        w = *(VecFx32 *)((int)ctx + 0x3c);
        func_01ffa724(0xc00, &w, (VecFx32 *)((int)ctx + 0x30));
        if (ctx[0xa] >= 0xc00) {
            ctx[0xa] = done;
            *(unsigned char *)((int)ctx + 0x48) += 1;
            func_ov231_020cc9e0(self);
            if (ctx[8] < 0x5000 || *(unsigned char *)((int)ctx + 0x48) >= 3) {
                done = 1;
            }
        }
        break;
    case 2:
        func_ov231_020cc9e0(self);
        func_0202f384(&a, (const void *)(ctx[0] + 0xa0), &data_02042258);
        VEC_DotProduct(&b, &a);
        dir = done;
        if (FX_Mul(b.x, a.z) - FX_Mul(b.z, a.x) < 0) {
            dir = 1;
        } else {
            dir = dir - 1;
        }
        if (*(signed char *)((int)ctx + 0x4f) != (signed char)dir) {
            ctx[7] -= *(signed char *)((int)ctx + 0x4f) * 0x1922;
        }
        if (ctx[8] > 0x4800) {
            *(unsigned char *)((int)ctx + 0x4a) = 0;
        }
        if (ctx[0xa] >= 0x2800) {
            done = 1;
        }
        break;
    case 3:
        if (ctx[0xa] >= 0x200) {
            done = 1;
        }
        break;
    }

    func_01ffa724(0x10000, &v, &v);
    if (func_ov231_020ccb08(self, &v, 0) != 0) {
        *(unsigned char *)((int)ctx + 0x4b) += 1;
        if (*(unsigned char *)((int)ctx + 0x4b) == 1) {
            ctx[7] += *(signed char *)((int)ctx + 0x4f) * 0x3244;
        }
        if (*(unsigned char *)((int)ctx + 0x4b) >= 9) {
            ctx[6] = ctx[7];
        }
        if (*(unsigned char *)((int)ctx + 0x4b) >= 0xb) {
            done = 1;
        }
        ctx[0xa] = 0;
        *(unsigned char *)((int)ctx + 0x4a) = 3;
    } else {
        *(unsigned char *)((int)ctx + 0x4b) = 0;
    }

    if ((*(unsigned char *)(ctx[0] + 0x17a) >> 1 & 1) != 0) {
        done = 1;
    }
    if (done == 0) {
        return;
    }
    *(signed char *)(ctx[0] + 0x1c7) = 2;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
