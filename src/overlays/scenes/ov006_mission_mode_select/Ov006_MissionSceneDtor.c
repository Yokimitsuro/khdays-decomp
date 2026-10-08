/* Ov006_MissionSceneDtor -- Mission Mode: tear the Mission Mode scene down.
 * Stops the renderer (heap+4), releases the sub-object at heap+0x60, drops the text engine
 * (slot 0x1e) and the Mission Mode input state, destroys the scene object held in heap[0], and
 * clears the scene slot. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void ConstReturn1_2(int *p);
extern void Ov006_FreeResourceRecordBuffer(int *p);
extern void Table_TailCallWithEntry(int a, int b);
extern void Ov006_ReleaseSecondaryResource(void);
extern void VeneerTo_Obj_Destroy(int *obj);
extern int  data_ov006_02056660;

void Ov006_MissionSceneDtor(void) {
    int *heap = (int *)NNSi_FndGetCurrentRootHeap();
    ConstReturn1_2(heap + 1);
    Ov006_FreeResourceRecordBuffer(heap + 0x18);
    Table_TailCallWithEntry(0, 0x1e);
    Ov006_ReleaseSecondaryResource();
    if (heap[0] != 0) {
        VeneerTo_Obj_Destroy((int *)heap[0]);
        heap[0] = 0;
    }
    data_ov006_02056660 = 0;
}
