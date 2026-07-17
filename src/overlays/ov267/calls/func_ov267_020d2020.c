/* func_ov267_020d2020 -- flag all 16 slots as dirty, then hand off.
 *
 * One of a 3-member shape family; the twins live in ov212/ov266 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Sets bit 1 of +0x5c on every one of the 16 entries in the table at ctx[0]+0x38c, then tail-calls
 * func_ov267_020d56ec with the thing at ctx[0]+0x5d4.
 *
 * Two spellings are load-bearing:
 *  - `((int *)ctx[0])[i + 0xe3]` (0x38c / 4), not `*(int *)(ctx[0] + 0x38c + i * 4)`: the array-
 *    index form keeps i as the only induction variable and folds 0x38c into the load's immediate.
 *    The offset form gets strength-reduced to a walking pointer (codegen-cracks.md).
 *  - ctx[0] is re-read INSIDE the loop, which is why it is spelled as an expression rather than
 *    hoisted into a local: the `|= 2` store could alias it, so the ROM reloads every pass.
 *
 * The trailing call is a real tail call (`bx ip`, no frame at all) -- this function pushes nothing. */

extern void func_ov267_020d56ec(int a);

void func_ov267_020d2020(int *ctx) {
    int i;
    int slot;

    for (i = 0; i < 0x10; i++) {
        slot = ((int *)ctx[0])[i + 0xe3];
        *(int *)(slot + 0x5c) |= 2;
    }
    func_ov267_020d56ec(*(int *)(ctx[0] + 0x5d4));
}
