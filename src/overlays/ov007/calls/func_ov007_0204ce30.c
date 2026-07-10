extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov007_0204d364(void *p);
extern void func_0202f9ec(void *p);
extern void func_0202f818(void *p);
extern void func_02032428(void *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_02024fd4(void *p);
extern int data_ov007_0204d3c0;
extern int data_ov007_0204d420;

/* Tear down the ov007 root work area: release its sub-objects and buffers, free
 * the two heap allocations, and reset the two module globals (-1 / 0). */
void func_ov007_0204ce30(void) {
    int root = NNSi_FndGetCurrentRootHeap();

    func_ov007_0204d364((void *)(root + 8));
    func_0202f9ec((void *)(root + 0x30));
    func_0202f818((void *)(root + 0x24));
    func_02032428((void *)(root + 0x107c));
    NNSi_FndFreeFromDefaultHeap(*(void **)(root + 4));
    func_02024fd4(*(void **)root);
    data_ov007_0204d3c0 = -1;
    data_ov007_0204d420 = 0;
}
