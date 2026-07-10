extern int *NNSi_FndGetCurrentRootHeap(void);
extern int OS_IsThreadAvailable_0x02023650(void);
extern void func_0202362c(int mode);
extern void func_0202f9ec(int *obj);
extern void func_0202f818(int *obj);
extern void NNSi_FndFreeFromDefaultHeap(int ptr);
extern void func_02003948(int result);

/* Tear down the ov010 root-heap work area: swap the active list slot out, and if
 * a buffer is allocated free its sub-objects and the buffer itself, then restore
 * the slot and signal completion (-2). */
void func_ov010_0204cd80(void) {
    int *root = NNSi_FndGetCurrentRootHeap();
    int saved = OS_IsThreadAvailable_0x02023650();

    func_0202362c(0);
    if (*root != 0) {
        func_0202f9ec(root + 6);
        func_0202f818(root + 3);
        NNSi_FndFreeFromDefaultHeap(*root);
        *root = 0;
    }
    func_0202362c(saved);
    func_02003948(-2);
}
