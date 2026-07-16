/* func_ov008_0207ba08 -- is the highlighted menu entry already the active one?
 * True while the scene is locked out (obj+0x4e8 set). Otherwise compares the current
 * selection (obj+0x4e4) against the entry id of the cursor row (obj+0x4b0, stride 6);
 * row 0 always counts as a match.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0204fc78 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern int func_02030788(void);
extern int data_ov008_02090f24;

#define OBJ (*(int **)&data_ov008_02090f24)

int func_ov008_0207ba08(void) {
    unsigned short row;
    int *obj;
    int same;
    if (OBJ[0x13a] != 0) {
        return 1;
    }
    row = (unsigned short)func_02030788();
    obj = OBJ;
    same = 1;
    if (*(unsigned short *)((char *)obj + 0x4e4) !=
            *(unsigned short *)((char *)obj + row * 6 + 0x4b0) && row != 0) {
        same = 0;
    }
    return same;
}
