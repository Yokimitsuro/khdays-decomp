/* Tally this block's 4 slot entries into the owner's running per-id totals,
 * scaling each entry's two quantities by the params at +0x20/+0x22.
 *
 * This is a tally, not a draw path.  The handler accumulates: it looks the entry's id up in the owner's list, adds the
 * two quantities to that node's running totals (allocating a 0x24-byte node when the
 * id is new) and applies per-id caps.  It compares the id against small integers like
 * 0x59/0x42/0x5a, so slot+0x00 is an ID, not a pointer.  Sibling call sites in this
 * same subsystem are synthesis recipes with ingredients and costs, which is the
 * context to read this in.
 *
 * The first entry is deliberately NOT scaled by the first factor, while the second
 * factor applies to all four.  That asymmetry is the ROM's `cmp r4, #0` / `bne`.
 * The walk stops at the first entry whose id is 0.
 *
 * CODEGEN NOTES (this shape was parked once as a double tie -- both blockers
 * turned out to be spellings, so the notes are worth keeping):
 *  - `block + i * sizeof(TallySlot)` with +0x34 as a PER-ACCESS displacement.
 *    Folding the 0x34 into the base (`((TallySlot *)(block + 0x34))[i]`) makes it
 *    a clean array, mwcc strength-reduces it to a walking pointer and burns an
 *    extra callee-saved register.  The displacement is what keeps the ROM's
 *    `add r1, r8, r4, lsl #3`.
 *  - the two scales hoisted BY HAND into ints, DECLARED AFTER `i`.  This is the
 *    OPPOSITE of the 96-byte sibling OvNNN_TallySlots, where hand-hoisting cost 12
 *    bytes and mwcc had to be left to do it.  Two hoists that are both reused
 *    across the loop pay for themselves; one does not.  Don't generalise either
 *    way -- try both.
 *  - `volatile` on the guard only, because the ROM loads the node twice (once to
 *    test, once as the argument) and mwcc otherwise CSEs the pair.  It is a
 *    codegen device here, not a claim that the field is volatile.
 *  - reading the fields through a TallySlot * instead of byte offsets is prettier
 *    and DOES NOT MATCH -- it perturbs the register allocation at 0x0c.
 */
typedef struct { int id; unsigned short qtyA, qtyB; } TallySlot;   /* 8 bytes */
typedef struct { char pad00[0x20]; unsigned short scaleA, scaleB; } TallyParams;

extern void func_ov069_020b8b98(void *owner, int id, unsigned int qtyA, unsigned int qtyB, int flag);
extern void func_ov069_020b8e74(TallyParams *p, void *block);

void func_ov069_020b901c(void *owner, TallyParams *p, char *block, int flag) {
    int i;
    int scaleA = p->scaleA;
    int scaleB = p->scaleB;

    for (i = 0; i < 4; i++) {
        char *row = block + i * sizeof(TallySlot);
        if (*(int volatile *)(row + 0x34) == 0) {
            break;
        }
        if (i == 0) {
            func_ov069_020b8b98(owner, *(int *)(row + 0x34),
                              *(unsigned short *)(row + 0x38),
                         scaleB * *(unsigned short *)(row + 0x3a), flag);
        } else {
            func_ov069_020b8b98(owner, *(int *)(row + 0x34),
                         scaleA * *(unsigned short *)(row + 0x38),
                         scaleB * *(unsigned short *)(row + 0x3a), flag);
        }
    }
    func_ov069_020b8e74(p, block);
}
