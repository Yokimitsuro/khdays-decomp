/* func_ov006_0205028c -- title: tear the title scene down.
 * Stops the renderer (heap+4), releases the sub-object at heap+0x60, drops the text engine
 * (slot 0x1e) and the title input state, destroys the scene object held in heap[0], and
 * clears the scene slot. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_020362e8(int *p);
extern void func_ov006_0204d57c(int *p);
extern void func_02033fec(int a, int b);
extern void func_ov006_0204fb24(void);
extern void WM_EndKeySharing_0x02023ad0(int *obj);
extern int  data_ov006_02056660;

void func_ov006_0205028c(void) {
    int *heap = (int *)NNSi_FndGetCurrentRootHeap();
    func_020362e8(heap + 1);
    func_ov006_0204d57c(heap + 0x18);
    func_02033fec(0, 0x1e);
    func_ov006_0204fb24();
    if (heap[0] != 0) {
        WM_EndKeySharing_0x02023ad0((int *)heap[0]);
        heap[0] = 0;
    }
    data_ov006_02056660 = 0;
}
