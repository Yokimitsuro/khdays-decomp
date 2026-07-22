/* func_ov026_0208e658 -- is this id one of the four that the ov008 scene treats specially?
 * Set = {1, 0x1a0, 0x1c8, 0x1c9}.
 *
 * Parked as a "proven tie (membership-test codegen)": the ROM hand-rolls a nested
 * binary-search form (split at 0x1a0, then a range check over {0x1c8,0x1c9}) and a flat
 * `a == 1 || a == 0x1a0 || ...` collapses to a cmp/cmpne chain half the size. It is not a tie
 * and the ROM is not hand-rolled -- that IS mwcc's SWITCH layout. Four fall-through `case`
 * labels with a shared body reproduce it exactly, pool entry included. When a membership test
 * comes out too short and the ROM bisects the value range, write the switch. */
int func_ov026_0208e658(int param_1) {
    switch (param_1) {
    case 1:
    case 0x1a0:
    case 0x1c8:
    case 0x1c9:
        return 1;
    }
    return 0;
}
