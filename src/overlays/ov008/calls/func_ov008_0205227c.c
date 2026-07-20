/* Draw every live slot of the block's 4-entry table, scaled by the params.
 *
 * The first entry is deliberately NOT scaled horizontally -- for i == 0 the
 * caller's sx is skipped and the slot's own sx passes through, while sy is
 * applied to every entry including the first.  That asymmetry is real: it shows
 * up as the ROM's `cmp r4, #0` / `bne` and both Ghidra and the disassembly agree.
 *
 * Entries are 8 bytes at block+0x34; the walk stops at the first empty node.
 *
 * CODEGEN NOTES (this shape was parked once as a double tie -- both blockers
 * turned out to be spellings, so the notes are worth keeping):
 *  - `block + i * sizeof(DrawSlot)` with +0x34 as a PER-ACCESS displacement.
 *    Folding the 0x34 into the base (`((DrawSlot *)(block + 0x34))[i]`) makes it
 *    a clean array, mwcc strength-reduces it to a walking pointer and burns an
 *    extra callee-saved register.  The displacement is what keeps the ROM's
 *    `add r1, r8, r4, lsl #3`.
 *  - sx/sy hoisted BY HAND into ints, DECLARED AFTER `i`.  Note this is the OPPOSITE of the sibling
 *    family at 96 bytes (OvNNN_ApplyToLiveSlots), where hand-hoisting cost 12
 *    bytes and mwcc had to be left to do it.  Two hoists that are both reused
 *    across the loop pay for themselves; one does not.  Don't generalise either
 *    way -- try both.
 *  - `volatile` on the guard only, because the ROM loads the node twice (once to
 *    test, once as the argument) and mwcc otherwise CSEs the pair.  It is a
 *    codegen device here, not a claim that the field is volatile.
 *  - reading the fields through a DrawSlot * instead of byte offsets is prettier
 *    and DOES NOT MATCH -- it perturbs the register allocation at 0x0c.
 */
typedef struct { void *node; unsigned short sx, sy; } DrawSlot;   /* 8 bytes */
typedef struct { char pad00[0x20]; unsigned short sx, sy; } DrawParams;

extern void func_ov008_02051df8(void *ctx, void *node, unsigned int sx, unsigned int sy, int flag);
extern void func_ov008_020520d4(DrawParams *p, void *block);

void func_ov008_0205227c(void *ctx, DrawParams *p, char *block, int flag) {
    int i;
    int sx = p->sx;
    int sy = p->sy;

    for (i = 0; i < 4; i++) {
        char *row = block + i * sizeof(DrawSlot);
        if (*(void * volatile *)(row + 0x34) == 0) {
            break;
        }
        if (i == 0) {
            func_ov008_02051df8(ctx, *(void **)(row + 0x34),
                              *(unsigned short *)(row + 0x38),
                         sy * *(unsigned short *)(row + 0x3a), flag);
        } else {
            func_ov008_02051df8(ctx, *(void **)(row + 0x34),
                         sx * *(unsigned short *)(row + 0x38),
                         sy * *(unsigned short *)(row + 0x3a), flag);
        }
    }
    func_ov008_020520d4(p, block);
}
