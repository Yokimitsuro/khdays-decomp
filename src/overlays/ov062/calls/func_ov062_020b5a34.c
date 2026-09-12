extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov062_020b5a90(void *arg0);
extern void func_ov062_020b5fdc(void *heap);
extern void func_ov062_020b6f34(void *heap);
extern void func_ov022_020a4798(void *heap, int nId, int nArg2);
extern void *func_ov022_0209fb24(void);

void *func_ov062_020b5a34(void *arg0) {
    void *heap = NNSi_FndGetCurrentRootHeap();
    func_ov062_020b5a90(arg0);
    func_ov062_020b5fdc(heap);
    func_ov062_020b6f34(heap);
    func_ov022_020a4798(heap, 0x4f, 0xc4);
    return func_ov022_0209fb24;
}
