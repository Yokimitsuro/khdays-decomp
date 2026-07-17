/* func_ov222_020d2b40 -- the move CHOOSER for ov221's family: pick the next move and re-arm the
 * think timer. Returns 1 if a move ended up queued at ctx[0]+0x1c7, 0 if not.
 *
 * One of a 4-member shape family; the twins live in ov221/ov224/ov226 and are byte-identical
 * modulo relocs (matched here, fanned out with dedupprop).
 *
 * Two hard early-outs return 0 without touching anything: the busy byte at *(ctx[0]+0x384)+0xad,
 * and a think timer at ctx[0x1a] that has not run down yet.
 *
 * Then it rolls a d100 once and gathers four facts, all of which only gate WHICH move is picked:
 *   charged  bit 0 of the byte at ctx[0]+0x17a
 *   clear    no live entry in the 4-slot table at ctx[0]+0x3ec (an entry counts only if the slot
 *            is non-null AND its +0x38c is non-zero) -- i.e. nothing is already in flight
 *   below    the thing at ctx[0]+0x3e8 sits lower than ctx[2][1] (its +0x194 minus ours is < 0)
 *   thrA/thrB two thresholds keyed off func_ov002_0207298c: == 2 gives (0x64, 0), else (0xa, 0xa).
 *            0x64 makes the `roll < thrA` test always true, so mode 2 forces the charged branch.
 *
 * The tree then splits on ctx[0x1e] (has a target) and on `dist` against 0x7000 -- so there are
 * four decision tables, each a `roll < K` ladder gated by one of the flags, falling back to move 9:
 *
 *   target, near : <30 move 0x10 | <40 && clear move 8 | <70 && below move 0xb | move 9
 *   target, far  : mode 8 -> (<0x42 && below move 0xb | move 9)
 *                  else     <thrB move 5 | <thrB+0x28 && clear move 8
 *                           | <thrB+0x41 && below move 0xb | move 9
 *   none,   near : <thrA && charged move 0xc | <thrA+0x23 move 0x10 | move 9
 *   none,   far  : <thrA && charged move 0xc | <thrA+0x28 && clear move 8 | move 9
 *
 * Every path then re-arms the timer with a uniform value between the two bounds at ctx[0]+0x224
 * and +0x228 (ctx[0x1a] = lo + rand(|hi - lo| + 1)) and reports whether +0x1c7 is no longer -1.
 *
 * `charged` uses a 1-bit bitfield: the ROM's `lsl #0x1f ; lsr #0x1f` is the bitfield extract, and
 * `& 1` would emit `and #1` instead (codegen-cracks.md).
 *
 * `func_02023eb4(d + 1) + lo` is why the ROM emits `add r0, r5, r0` after the call rather than
 * folding: the RNG returns long long, so the addend survives as a real add. Same mechanism as the
 * `+ (v - v)` copy artifact (deferred-ties.md). */

typedef struct {
    unsigned char b0 : 1;
    unsigned char rest : 7;
} Bits8;

extern int func_02023eb4();
extern int func_ov002_0207298c(void);

int func_ov222_020d2b40(int self, int dist) {
    int *ctx;
    int roll;
    int charged;
    int clear;
    int below;
    int thrA;
    int thrB;
    int i;
    int p;
    int q;
    int lo;
    int d;

    ctx = *(int **)(self + 4);
    if (*(unsigned char *)(*(int *)(ctx[0] + 0x384) + 0xad) != 0) {
        goto fail;
    }
    if (ctx[0x1a] > 0) {
        goto fail;
    }

    roll = func_02023eb4(0x64);
    charged = ((Bits8 *)(ctx[0] + 0x17a))->b0;
    clear = 1;
    below = 0;
    thrA = (func_ov002_0207298c() == 2) ? 0x64 : 0xa;
    thrB = (func_ov002_0207298c() == 2) ? 0 : 0xa;

    /* Indexed off ctx[0] (0x3ec / 4 == 0xfb), NOT `*(int *)(ctx[0] + 0x3ec + i * 4)`: the latter
     * gets strength-reduced to a walking pointer (+1 instruction). The array-index form keeps i as
     * the only induction variable and folds 0x3ec into the load's immediate, as the ROM does. */
    for (i = 0; i < 4; i++) {
        p = ((int *)ctx[0])[i + 0xfb];
        if (p != 0 && *(int *)(p + 0x38c) != 0) {
            break;
        }
    }
    clear &= (i >= 4);

    q = *(int *)(ctx[0] + 0x3e8);
    if (q != 0) {
        if (*(int *)(q + 0x194) - *(int *)(ctx[2] + 4) < 0) {
            below = 1;
        }
    }

    if (ctx[0x1e] != 0) {
        if (dist < 0x7000) {
            if (roll < 0x1e) {
                *(signed char *)(ctx[0] + 0x1c7) = 0x10;
            } else if (roll < 0x28 && clear != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            } else if (roll < 0x46 && below != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xb;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 9;
            }
        } else if (func_ov002_0207298c() != 8) {
            /* Guard written `!= 8` so the mode-8 block lands OUT OF LINE at the end and this
             * ladder stays inline, matching the ROM's `beq` forward branch. */
            if (roll < thrB) {
                *(signed char *)(ctx[0] + 0x1c7) = 5;
            } else if (roll < thrB + 0x28 && clear != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            } else if (roll < thrB + 0x41 && below != 0) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xb;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 9;
            }
        } else if (roll < 0x42 && below != 0) {
            *(signed char *)(ctx[0] + 0x1c7) = 0xb;
        } else {
            *(signed char *)(ctx[0] + 0x1c7) = 9;
        }
    } else if (dist < 0x7000) {
        if (roll < thrA && charged != 0) {
            *(signed char *)(ctx[0] + 0x1c7) = 0xc;
        } else if (roll < thrA + 0x23) {
            *(signed char *)(ctx[0] + 0x1c7) = 0x10;
        } else {
            *(signed char *)(ctx[0] + 0x1c7) = 9;
        }
    } else if (roll < thrA && charged != 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 0xc;
    } else if (roll < thrA + 0x28 && clear != 0) {
        *(signed char *)(ctx[0] + 0x1c7) = 8;
    } else {
        *(signed char *)(ctx[0] + 0x1c7) = 9;
    }

    lo = *(int *)(ctx[0] + 0x224);
    d = *(int *)(ctx[0] + 0x228) - lo;
    if (d < 0) {
        d = -d;
    }
    ctx[0x1a] = func_02023eb4(d + 1) + lo;

    if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
        return 1;
    }
fail:
    return 0;
}
