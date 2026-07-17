/* func_ov266_020cfb00 -- the move CHOOSER for ov212's family: pick a move, then (for move 6, the
 * dodge) prove the escape direction is actually walkable before committing to it.
 * Returns 1 if a move was queued at ctx[0]+0x1c7 and the timer re-armed, 0 otherwise.
 *
 * One of a 3-member shape family; the twins live in ov212/ov267 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Early-out: ctx[0x13] (the think timer) still counting down -> 0, nothing touched.
 *
 * Rolls a d100 once into `roll`, clears the timer, then picks in priority order:
 *
 *   1. two reactive openings, each its OWN extra d100 and each queueing move 5:
 *        020cd60c(ctx,1) && !020cdae8(ctx) && rand(100) < 0x14   (a 20% take)
 *        020cd63c(ctx,1) && rand(100) < 5                        (a 5% take)
 *      both also stamp ctx[0x11] with *(int *)(*(int *)self + 0x2c).
 *   2. otherwise a distance-banded ladder on the FIRST roll:
 *        dist < 0x3000  : <0 move 6 | <0x5a && 020cd60c move 0xb | <0x64 move 9
 *        dist < 0x10000 : <0x37 move 6 | <0x50 move 9 | 020cd63c && ctx[0x11] >= 0xf000 -> move 2
 *        dist >= 0x10000: <0 move 6 | <0x46 move 9 | 020cd63c && ctx[0x11] >= 0xf000 -> move 2
 *      Move 2 also runs 020cd5ec(ctx,1) and pushes the timer out by 0x1100.
 *
 * The `roll < 0` tests are transcribed as the ROM has them (`cmp r5,#0 ; bge`), signed, even though
 * rand(100) can never be negative -- so those two move-6 arms are dead in this overlay. The two
 * extra rolls at step 1 are UNSIGNED (`bhs`) where the ladder is signed; both come straight off the
 * ROM's branches, as in ov208's chooser.
 *
 * Then the validation pass. Anything other than move 6 arms the timer and returns 1. Move 6 (the
 * dodge) first builds the escape direction:
 *   ctx[0]+0x5a8 set -> aim away from that thing: its position at +0x190, lifted by our radius,
 *                       minus ours, normalised.
 *   otherwise        -> fall back to our own heading ctx[0xd], via the Q12-radians -> 16-bit index
 *                       -> sin/cos table conversion (codegen-cracks.md).
 * The direction is scaled out to `dist + radius*2` and tested with 020cd5ec's two collision probes;
 * if EITHER reports a hit the move is cancelled (+0x1c7 = -1) and it returns 0. So move 6 is the
 * only move that can be vetoed after being chosen.
 *
 * `extern const short data_0203d210[]` -- the `const` is load-bearing, not decoration. Without it
 * mwcc must assume the stores into `v` might write the table, which pins the second ldrsh after
 * them and permutes the whole block. See codegen-cracks.md.
 *
 * `func_02023eb4(d + 1) + lo` keeps the addend as a real add (the RNG returns long long), which is
 * the ROM's `add r2, r5, r0`. See deferred-ties.md.
 *
 * Three more spellings are load-bearing, so do not tidy them:
 *  - the two bare `goto fail` early-outs share the one `return 0` epilogue the ROM already needs
 *    for the `q == -1` test. Written as plain `return 0` mwcc inlines each one (+8 B). The two
 *    returns that FIRST write -1 stay inline, as the ROM has them.
 *  - the `sum` local. `ctx[0x13] += func_02023eb4(d + 1) + lo;` in one statement is correct but
 *    allocates the result over the sum's register; splitting it lets ctx[0x13]'s own register take
 *    the result, which is the ROM's `add r1, r1, r2`.
 *  - `v.x / v.y / v.z` in that order even though the ROM stores y first. mwcc reorders these
 *    freely; writing them in store order permutes the registers instead. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Only used for the queued-move slot in the validation pass, where the SAME address is both read
 * (ldrsb, which must split 0x1c7 into a base + 0xc7) and written. Spelled as a cast the address
 * becomes a common subexpression and mwcc builds a second partial base for the store; as a struct
 * field each access picks its own addressing mode, and the store folds 0x1c7 straight into the
 * strb (12-bit range) as the ROM does. The unconditional stores above are plain casts because they
 * share no address with a load. */
typedef struct {
    char pad0[0x1c7];
    signed char queued;
} Owner;

extern int func_02023eb4();
extern int func_ov266_020cf3fc(int *ctx, int a);
extern int func_ov266_020cf8e0(int *ctx);
extern int func_ov266_020cf42c(int *ctx, int a);
extern void func_ov266_020cf3dc(int *ctx, int a);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_01ff8d18(const VecFx32 *v, VecFx32 *unit);
extern void func_01ffa724(int scale, const VecFx32 *src, VecFx32 *dst);
extern int func_01fff920(int a, const VecFx32 *b, const VecFx32 *c);
extern int func_01fff8e8(int a, const VecFx32 *b, const VecFx32 *c, int d, int e);
extern const short data_0203d210[];

int func_ov266_020cfb00(int self, int dist) {
    int *ctx;
    int roll;
    VecFx32 v;
    int other;
    int lo;
    int d;
    int sum;
    int q;
    Owner *owner;
    unsigned int idx;

    ctx = *(int **)(self + 4);
    if (ctx[0x13] > 0) {
        goto fail;
    }

    roll = func_02023eb4(0x64);
    ctx[0x13] = 0;

    if (func_ov266_020cf3fc(ctx, 1) != 0 && func_ov266_020cf8e0(ctx) == 0 &&
        (unsigned int)func_02023eb4(0x64) < 0x14) {
        ctx[0x11] = *(int *)(*(int *)self + 0x2c);
        *(signed char *)(ctx[0] + 0x1c7) = 5;
    } else if (func_ov266_020cf42c(ctx, 1) != 0 && (unsigned int)func_02023eb4(0x64) < 5) {
        ctx[0x11] = *(int *)(*(int *)self + 0x2c);
        *(signed char *)(ctx[0] + 0x1c7) = 5;
    } else if (dist < 0x3000) {
        if (roll < 0) {
            *(signed char *)(ctx[0] + 0x1c7) = 6;
        } else if (roll < 0x5a) {
            if (func_ov266_020cf3fc(ctx, 1) != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xb;
            }
        } else if (roll < 0x64) {
            *(signed char *)(ctx[0] + 0x1c7) = 9;
        }
    } else if (dist < 0x10000) {
        if (roll < 0x37) {
            *(signed char *)(ctx[0] + 0x1c7) = 6;
        } else if (roll < 0x50) {
            *(signed char *)(ctx[0] + 0x1c7) = 9;
        } else if (func_ov266_020cf42c(ctx, 1) != 0 && ctx[0x11] >= 0xf000) {
            func_ov266_020cf3dc(ctx, 1);
            ctx[0x13] += 0x1100;
            *(signed char *)(ctx[0] + 0x1c7) = 2;
        }
    } else if (roll < 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 6;
    } else if (roll < 0x46) {
        *(signed char *)(ctx[0] + 0x1c7) = 9;
    } else if (func_ov266_020cf42c(ctx, 1) != 0 && ctx[0x11] >= 0xf000) {
        func_ov266_020cf3dc(ctx, 1);
        ctx[0x13] += 0x1100;
        *(signed char *)(ctx[0] + 0x1c7) = 2;
    }

    owner = (Owner *)ctx[0];
    q = owner->queued;
    if (q == -1) {
        goto fail;
    }
    if (q == 6) {
        other = *(int *)((int)owner + 4);
        if (ctx[0x1a] == 0) {
            owner->queued = -1;
            return 0;
        }
        if (*(int *)((int)owner + 0x5a8) != 0) {
            v = *(VecFx32 *)(*(int *)((int)owner + 0x5a8) + 0x190);
            v.y = v.y + *(int *)(ctx[0] + 0x80);
            VEC_Subtract(&v, (const VecFx32 *)(ctx[0] + 0x74), &v);
            func_01ff8d18(&v, &v);
        } else {
            idx = (unsigned short)(((long long)ctx[0xd] * 0x28be60db9391LL + 0x80000000000LL) >>
                                   44) >>
                  4;
            v.x = data_0203d210[idx * 2];
            v.y = 0;
            v.z = data_0203d210[idx * 2 + 1];
        }
        func_01ffa724(dist + (*(int *)(ctx[0] + 0x80) << 1), &v, &v);
        if (func_01fff920(*(int *)(other + 0x7c), (const VecFx32 *)(ctx[0] + 0x74), &v) != 0 ||
            func_01fff8e8(*(int *)(other + 0x7c), (const VecFx32 *)(ctx[0] + 0x74), &v,
                          *(int *)(ctx[0] + 0x80), 0) != 0) {
            *(signed char *)(ctx[0] + 0x1c7) = -1;
            return 0;
        }
    }

    lo = *(int *)(ctx[0] + 0x224);
    d = *(int *)(ctx[0] + 0x228) - lo;
    if (d < 0) {
        d = -d;
    }
    sum = func_02023eb4(d + 1) + lo;
    ctx[0x13] += sum;
    return 1;
fail:
    return 0;
}
