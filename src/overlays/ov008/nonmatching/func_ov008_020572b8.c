/* Remap an animation/state index to its resource slot; unmapped inputs (1, 7, out of range)
 * return 0.
 *
 * NON-MATCHING (equivalent). The value mapping, the dense jump table, and the body layout
 * (case 0, 8, 2, 3, 4, 5, 6) all reproduce byte-exact. The only residue is the jump-table
 * entry for the empty `case 1`: the ROM points it at the redundant `b merge` that trails
 * case 8's body (a double branch), whereas mwcc build 139 collapses every empty-case break
 * to a single direct branch to the merge block. Tried: numeric order, case-1-after-case-8,
 * and case-8-fall-through-into-case-1 -- all collapse identically. Pure switch-lowering
 * version difference; the C is correct. */
int func_ov008_020572b8(int mode) {
    int slot = 0;
    switch (mode) {
    case 0: slot = 6; break;
    case 8: slot = 7; break;
    case 2: slot = 1; break;
    case 3: slot = 2; break;
    case 4: slot = 3; break;
    case 5: slot = 4; break;
    case 6: slot = 5; break;
    case 1: break;
    case 7: break;
    }
    return slot;
}
