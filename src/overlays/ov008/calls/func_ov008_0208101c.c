/* func_ov008_0208101c -- enter menu page 1.
 * Resets the page's resource block at OBJ+8, reloads it from data_ov008_02090d88, rebuilds
 * layer 0 and layer 1, re-applies the current Mission Mode sub-state (OBJ+0x94f4) to the model and
 * the text, and starts the page-1 entry animation.
 *
 * PROVENANCE: byte-identical twin of func_ov006_020552ac -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void func_ov008_020559a8(int *block);
extern void func_ov008_02055534(int block, int desc);
extern void func_ov008_0207fa4c(int layer, int a, int b);
extern void func_ov008_0207f614(int state);
extern void func_ov008_0207dfec(int state);
extern void func_ov008_02080f14(int anim, int a, int b, int c, int d);
extern int *data_ov008_02090fa4;
extern int  data_ov008_02090d88;

void func_ov008_0208101c(void) {
    func_ov008_020559a8((int *)((char *)data_ov008_02090fa4 + 8));
    func_ov008_02055534((int)((char *)data_ov008_02090fa4 + 8), (int)&data_ov008_02090d88);
    func_ov008_0207fa4c(0, 0, 0);
    func_ov008_0207fa4c(1, 0, 0);
    func_ov008_0207f614(*(int *)((char *)data_ov008_02090fa4 + 0x94f4));
    func_ov008_0207dfec(*(int *)((char *)data_ov008_02090fa4 + 0x94f4));
    func_ov008_02080f14(1, 0, 0, 0, 0);
}
