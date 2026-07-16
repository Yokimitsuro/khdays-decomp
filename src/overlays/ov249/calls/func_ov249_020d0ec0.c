/* func_ov249_020d0ec0 -- the attack chooser: given the range, roll for what the owner does next.
 * Returns non-zero when a move was actually chosen (i.e. ctx[0]+0x1c7 is no longer -1), which is
 * what func_ov228_020cfc4c tests to decide whether to re-enter.
 *
 * A positive cooldown at +0x54 means "not yet" -- return 0 without touching anything. Otherwise
 * the cooldown is re-rolled into [lo, lo + |hi - lo|] from the pair at ctx[0]+0x224/+0x228.
 *
 * The loop scans the 8 slots at ctx[0]+0x3c0 for the first whose low byte at +0x60 has bit 0
 * clear; finding one (`slotFree`) is a precondition for the 0xb move everywhere below.
 *
 * A queued move at +0x60 short-circuits everything: it is played and the slot cleared to -1.
 * Otherwise there is a flat 20% chance of doing nothing at all, and then the range picks a table:
 *   - under 0x3000: half the time commit (stance 1, cooldown cleared, move 4) and queue a
 *     follow-up by the roll -- 0xb (needs a free slot), 6, 9, 0xa or none;
 *     the other half just play 6 or 8 by the roll.
 *   - under 0x8000: 0xb on a low roll with a free slot, else 0xa or 8.
 *   - beyond:       0xb on a low roll with a free slot, else 0xa.
 *
 * Two shapes worth keeping (both in codegen-cracks.md):
 *   - the +0x60 halfword is read as a bitfield (`lo & 1`), NOT cast to a byte -- an
 *     (unsigned char) cast collapses the ldrh/lsl/lsr into an ldrb;
 *   - the cooldown guard is written the positive way round so `return 0` lands out-of-line at
 *     the end, which is what the ROM's `bgt` does. */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

extern int func_02023eb4(int n);

int func_ov249_020d0ec0(int self, int range) {
    int *ctx;
    int roll;
    int lo;
    int spread;
    int i;
    int slotFree;
    int queued;

    ctx = *(int **)(self + 4);
    if (ctx[0x15] <= 0) {
        roll = func_02023eb4(100);
        lo = *(int *)(ctx[0] + 0x224);
        spread = *(int *)(ctx[0] + 0x228) - lo;
        if (spread < 0) {
            spread = -spread;
        }
        ctx[0x15] = lo + func_02023eb4(spread + 1);

        for (i = 0; i < 8; i++) {
            /* Indexed off ctx[0] with 0x3c0 folded into the load offset (word index 0xf0).
             * `((int *)(ctx[0] + 0x3c0))[i]` hoists the base out of the loop instead, and
             * `*(int *)(ctx[0] + i * 4 + 0x3c0)` gets strength-reduced to a walking pointer. */
            if ((((Hw60 *)(((int *)ctx[0])[i + 0xf0] + 0x60))->lo & 1) == 0) {
                break;
            }
        }
        slotFree = i < 8;

        queued = *(signed char *)((char *)ctx + 0x60);
        if (queued != -1) {
            *(signed char *)(ctx[0] + 0x1c7) = queued;
            *(signed char *)((char *)ctx + 0x60) = -1;
            goto done;
        }

        if ((unsigned int)func_02023eb4(100) < 0x14) {
            goto done;
        }

        if (range < 0x3000) {
            if ((unsigned int)func_02023eb4(100) < 0x32) {
                ctx[0x17] = 1;
                ctx[0x15] = 0;
                *(signed char *)(ctx[0] + 0x1c7) = 4;

                if (roll < 0x14 && slotFree) {
                    *(signed char *)((char *)ctx + 0x60) = 0xb;
                    goto done;
                }
                if (roll < 0x28) {
                    *(signed char *)((char *)ctx + 0x60) = 6;
                    goto done;
                }
                if (roll < 0x3c) {
                    *(signed char *)((char *)ctx + 0x60) = 9;
                    goto done;
                }
                if (roll < 0x50) {
                    *(signed char *)((char *)ctx + 0x60) = 0xa;
                } else {
                    *(signed char *)((char *)ctx + 0x60) = -1;
                }
                goto done;
            }

            /* if/else with a store in each arm, not a ternary: the ternary picks the value with
             * movlt/movge and does ONE strb, where the ROM emits strblt + strbge. */
            if (roll < 0x3c) {
                *(signed char *)(ctx[0] + 0x1c7) = 6;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            }
            goto done;
        }

        if (range < 0x8000) {
            if (roll < 0x21 && slotFree) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xb;
                goto done;
            }
            if (roll < 0x42) {
                *(signed char *)(ctx[0] + 0x1c7) = 0xa;
            } else {
                *(signed char *)(ctx[0] + 0x1c7) = 8;
            }
            goto done;
        }

        if (roll < 0x32 && slotFree) {
            *(signed char *)(ctx[0] + 0x1c7) = 0xb;
            goto done;
        }
        *(signed char *)(ctx[0] + 0x1c7) = 0xa;

    done:
        /* `return X != -1;` would emit movne/moveq/pop. The ROM instead returns 1 and falls into
         * the SAME `mov r0,#0 ; pop` block the cooldown guard branches to, so both zero-returns
         * share one exit. */
        if (*(signed char *)(ctx[0] + 0x1c7) != -1) {
            return 1;
        }
    }

    return 0;
}
