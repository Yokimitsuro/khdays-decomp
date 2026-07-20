/* Push each live entry of the 4-slot table through the per-entry handler, then
 * run the block's own update.  The table is an array of 8-byte entries whose
 * object pointer sits at +0x34 from the block base; the loop stops at the first
 * empty slot.
 *
 * Three codegen levers were needed, all catalogued:
 *  - `i * sizeof(SlotEntry8)`, not `i * 8`: with the literal, mwcc turns the
 *    index into a byte-stride induction variable and the ROM's
 *    `add r1, r6, r4, lsl #3` disappears.
 *  - DO NOT hoist `p->a` by hand.  mwcc hoists the loop-invariant load itself
 *    and gets the ROM's register count; hoisting it in the source adds a live
 *    value, pushes an extra register and costs 12 bytes.  Same family as
 *    "don't hand-CSE".
 *  - the `1` passed on the stack is a hoisted VARIABLE, not a literal: the ROM
 *    keeps it in sb across the whole loop.
 * The `volatile` on the emptiness test is a codegen device, not a claim about
 * the field: the ROM loads [row,#0x34] twice and mwcc otherwise CSEs the two
 * reads into one.  Same trick as func_ov007_0204ce94, where reading the index
 * through a different expression achieved it without volatile.
 *
 * SEMANTICS (corrected 2026-07-20): this is a TALLY, not a draw path.  The handler
 * looks the entry's id up in the owner's list, adds the quantities to that node's
 * running totals (allocating a 0x24-byte node for a new id) and applies per-id caps;
 * it compares the id against small integers like 0x59/0x42/0x5a, so slot+0x00 is an
 * ID and not a pointer.  Sibling call sites in the same subsystem are synthesis
 * recipes with ingredients and costs.  See OvNNN_TallyScaledSlots, the 152-byte
 * sibling that scales each entry instead of passing the params through.
 */
typedef struct { void *obj; int unk04; } SlotEntry8;
typedef struct { char pad00[0x20]; unsigned short a; unsigned short b; } Params;

extern void func_ov000_02056bac(void *ctx, void *obj, int a, int b, int flag);
extern void func_ov000_02056f90(Params *p, void *block);

void func_ov000_020570d8(void *ctx, Params *p, char *block) {
    int one = 1;
    int i;
    int a = p->a;

    for (i = 0; i < 4; i++) {
        char *row = block + i * sizeof(SlotEntry8);
        if (*(void * volatile *)(row + 0x34) == 0) {
            break;
        }
        func_ov000_02056bac(ctx, *(void **)(row + 0x34), a, p->b, one);
    }
    func_ov000_02056f90(p, block);
}
