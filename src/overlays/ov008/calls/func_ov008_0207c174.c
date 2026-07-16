/* func_ov008_0207c174 -- tear the scene down.
 * Stops the renderer (heap+4), releases the sub-object at heap+0x60, drops the text engine
 * (slot 0x1e) and the Mission Mode input state, destroys the scene object held in heap[0], and
 * clears the scene slot.
 *
 * PROVENANCE: byte-identical twin of func_ov006_0205028c -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_020362e8(int *p);
extern void func_ov008_02055c74(int *p);
extern void func_02033fec(int a, int b);
extern void func_ov008_0207b8a8(void);
extern void WM_EndKeySharing_0x02023ad0(int *obj);
extern int  data_ov008_02090fa0;

void func_ov008_0207c174(void) {
    int *heap = (int *)NNSi_FndGetCurrentRootHeap();
    func_020362e8(heap + 1);
    func_ov008_02055c74(heap + 0x18);
    func_02033fec(0, 0x1e);
    func_ov008_0207b8a8();
    if (heap[0] != 0) {
        WM_EndKeySharing_0x02023ad0((int *)heap[0]);
        heap[0] = 0;
    }
    data_ov008_02090fa0 = 0;
}
