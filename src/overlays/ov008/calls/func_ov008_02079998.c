/* func_ov008_02079998 -- drive the ov105 sound state from the scene state.
 * State 0 (still booting) arms the "intro jingle started" latch at obj+0x49c once the
 * sound engine reports ready; states 1 and 3 are quiet; 9 and 10 fade out; every other
 * state stops the sound outright.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0204db2c -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern int  func_02001030(void);
extern void func_ov105_020bf90c(void);
extern int  func_ov105_020bf5a8(void);
extern void func_ov105_020bf928(void);
extern int  data_ov008_02090f24;

#define OBJ (*(int **)&data_ov008_02090f24)

void func_ov008_02079998(void) {
    switch (func_02001030()) {
    case 9:
    case 10:
        func_ov105_020bf90c();
        return;
    case 0:
        if (OBJ[0x127] != 0) {
            return;
        }
        if (func_ov105_020bf5a8() == 0) {
            return;
        }
        OBJ[0x127] = 1;
        return;
    case 1:
        break;
    case 3:
        break;
    default:
        func_ov105_020bf928();
        return;
    }
}
