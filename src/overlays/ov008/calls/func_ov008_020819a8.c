/* func_ov008_020819a8 -- switch the 3D character model to pose `pose`.
 * Only acts when the pose actually changes (OBJ+0x94f0 caches the current one): restarts the
 * two tweens at OBJ+0x9574 and OBJ+0x9590 over 300 frames -- one ramping to 0x10000, the other
 * running mode 2 down from 0xa000. Returns 0 if the Mission Mode object is gone.
 *
 * PROVENANCE: byte-identical twin of func_ov006_02055c38 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void func_02035fb0(int *tween, int a, int b, int target, int frames);
extern void func_02035ffc(int tween);
extern int *data_ov008_02090fa4;

int func_ov008_020819a8(int pose) {
    int *obj = data_ov008_02090fa4;
    if (obj == 0) {
        return 0;
    }
    if (*(int *)((char *)obj + 0x94f0) != pose) {
        func_02035fb0((int *)((char *)obj + 0x9574), 0, 0, 0x10000, 300);
        func_02035ffc((int)((char *)data_ov008_02090fa4 + 0x9574));
        func_02035fb0((int *)((char *)data_ov008_02090fa4 + 0x9590), 2, 0xa000, 0, 300);
        func_02035ffc((int)((char *)data_ov008_02090fa4 + 0x9590));
        *(int *)((char *)data_ov008_02090fa4 + 0x94f0) = pose;
    }
    return 1;
}
