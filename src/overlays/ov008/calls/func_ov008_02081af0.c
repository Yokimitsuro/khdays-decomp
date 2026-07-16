/* func_ov008_02081af0 -- start tween number `slot` (0..4) on the scene object.
 * Each tween lives at OBJ+0x9614 + slot*0x1c; `val` is the Q12 target. Returns 0 if the
 * Mission Mode object is gone or the slot is out of range.
 *
 * PROVENANCE: byte-identical twin of func_ov006_02055d80 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void func_02035fb0(int *tween, int a, int b, int target, int mode);
extern void func_02035ffc(int tween);
extern int *data_ov008_02090fa4;

int func_ov008_02081af0(int val, unsigned int slot, int mode) {
    if (data_ov008_02090fa4 == 0) {
        return 0;
    }
    if (slot > 4) {
        return 0;
    }
    func_02035fb0((int *)((char *)data_ov008_02090fa4 + 0x9614 + slot * 0x1c),
                  0, 0, val << 12, mode);
    func_02035ffc((int)((char *)data_ov008_02090fa4 + 0x9614 + slot * 0x1c));
    return 1;
}
