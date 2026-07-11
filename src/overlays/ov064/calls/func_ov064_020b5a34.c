extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov064_020b5a98(void *obj);
extern void func_ov064_020b6930(void *heap);
extern void func_ov022_020a4798(void *heap, int x, int y);
extern void func_ov022_0209fb24(void);

int func_ov064_020b5a34(void *obj) {
    void *h = NNSi_FndGetCurrentRootHeap();
    func_ov064_020b5a98(obj);
    func_ov064_020b6930(h);
    func_ov022_020a4798(h, 0x4a, 0xc9);
    return (int)func_ov022_0209fb24;
}
