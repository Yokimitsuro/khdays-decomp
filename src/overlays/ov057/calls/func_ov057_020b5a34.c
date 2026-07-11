extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov057_020b5a7c(void *obj);
extern void func_ov057_020b6020(void *heap);
extern void func_ov022_020a4798(void *heap, int x, int y);
extern void func_ov022_0209fb24(void);

int func_ov057_020b5a34(void *obj) {
    void *h = NNSi_FndGetCurrentRootHeap();
    func_ov057_020b5a7c(obj);
    func_ov057_020b6020(h);
    func_ov022_020a4798(h, 0x49, 0xc8);
    return (int)func_ov022_0209fb24;
}
