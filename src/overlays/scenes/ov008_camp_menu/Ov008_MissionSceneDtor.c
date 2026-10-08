/* Ov008_MissionSceneDtor -- tear the scene down.
 * Stops the renderer (heap+4), releases the sub-object at heap+0x60, drops the text engine
 * (slot 0x1e) and the Mission Mode input state, destroys the scene object held in heap[0], and
 * clears the scene slot.
 *
 * PROVENANCE: byte-identical twin of Ov006_MissionSceneDtor -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void ConstReturn1_2(int *p);
extern void Ov008_FreeResourceRecordBuffer(int *p);
extern void Table_TailCallWithEntry(int a, int b);
extern void Ov008_ReleaseMissionLobby(void);
extern void VeneerTo_Obj_Destroy(int *obj);
extern int  data_ov008_02090fa0;

void Ov008_MissionSceneDtor(void) {
    int *heap = (int *)NNSi_FndGetCurrentRootHeap();
    ConstReturn1_2(heap + 1);
    Ov008_FreeResourceRecordBuffer(heap + 0x18);
    Table_TailCallWithEntry(0, 0x1e);
    Ov008_ReleaseMissionLobby();
    if (heap[0] != 0) {
        VeneerTo_Obj_Destroy((int *)heap[0]);
        heap[0] = 0;
    }
    data_ov008_02090fa0 = 0;
}
