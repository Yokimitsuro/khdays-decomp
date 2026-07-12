/* PROVEN TIE (membership-test codegen). The ROM hand-rolls a nested binary-search
 * form (split at 0x1a0, range-check {0x1c8,0x1c9}); mwcc build 139 collapses the
 * membership to a tight cmp;cmpne;cmpne;cmpne chain (half the size). No source
 * structure (flat ||, explicit nested ifs) reproduces the verbose original.
 * Kept here so the ov008 blob stays byte-exact. Set = {1, 0x1a0, 0x1c8, 0x1c9}. */
int func_ov008_0208b7a8(int param_1) {
    return param_1 == 1 || param_1 == 0x1a0 || param_1 == 0x1c8 || param_1 == 0x1c9;
}
