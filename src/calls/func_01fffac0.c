/* func_01fffac0 -- flip a node's double buffer: toggle the index at +0x1c and re-point +0x18 at
 * the matching 0xc-byte slot. Does nothing (and reports 0) unless func_01fffaf4 accepts the
 * current buffer.
 *
 * Parked as a "register-colouring tie" after seven source forms: the ROM colours the toggled
 * value r2 and the 0xc multiplier r1, mwcc shifts both down one because "r0 is free after the
 * guard call returns". r0 is NOT free -- the guard's result is this function's RETURN VALUE, so
 * it has to survive to the `pop`, and both exits hand it back (the early one via the `popeq` that
 * already has 0 in r0). Everything shifted down by exactly one register is the fingerprint of a
 * reserved r0; ask whether the function returns something before touching the body. Third park
 * closed on this axis (cf. func_ov010_0204cac0, func_ov022_020aeef8).
 */
extern int func_01fffaf4(int *node);

int func_01fffac0(int p) {
    unsigned int v;
    int ok = func_01fffaf4(*(int **)(p + 0x18));
    if (ok == 0) {
        return ok;
    }
    v = *(unsigned int *)(p + 0x1c) ^ 1;
    *(unsigned int *)(p + 0x1c) = v;
    *(unsigned int *)(p + 0x18) = v * 0xc + p;
    return ok;
}
