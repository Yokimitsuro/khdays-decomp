/* func_ov008_0207b14c -- commit or cancel the highlighted menu entry.
 * When the scene reports state 1 the entry is accepted: the scene object moves to the
 * accept state (func_ov008_0207ab50), the 0x3ec-byte selection scratch at obj+0x40 is
 * wiped, the pending-transition slot at obj+0x28 is cleared and the sound is silenced.
 * Otherwise it moves to the cancel state (func_ov008_0207aac8) and runs the scene tick.
 * Returns whether the entry was accepted.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0204f3f0 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern int  func_02001030(void);
extern void func_02023a44(int scene, int next);
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern void func_ov105_020bf8c8(int a);
extern void func_ov008_02079998(void);
extern void func_ov008_0207ab50(void);
extern void func_ov008_0207aac8(void);
extern int  data_ov008_02090f24;

#define OBJ   (*(int **)&data_ov008_02090f24)
#define SCENE (*(int *)((int)&data_ov008_02090f24 + 4))

int func_ov008_0207b14c(void) {
    int accepted = 0;
    if (func_02001030() == 1) {
        func_02023a44(SCENE, (int)func_ov008_0207ab50);
        MI_CpuFill8((char *)OBJ + 0x40, accepted, 0x3ec);
        OBJ[0xa] = accepted;
        func_ov105_020bf8c8(accepted);
        accepted = 1;
    } else {
        func_02023a44(SCENE, (int)func_ov008_0207aac8);
        func_ov008_02079998();
    }
    return accepted;
}
