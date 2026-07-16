/* func_ov008_0206d064 -- draw a string, optionally with a 1px drop shadow (param_5) one colour
 * darker. Flags are fixed at 0x411.
 *
 * PROVENANCE: byte-identical twin of func_ov025_020a26f8 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void func_020301c8(int dst, int x, int y, int colour, unsigned int flags, int text);

void func_ov008_0206d064(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6) {
    if (param_5 != 0) {
        func_020301c8(param_1, param_2 + 1, param_3 + 1, param_4 - 1, 0x411, param_6);
    }
    func_020301c8(param_1, param_2, param_3, param_4, 0x411, param_6);
}
