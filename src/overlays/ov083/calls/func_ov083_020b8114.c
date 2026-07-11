extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov083_020b8178(void *obj);
extern void func_ov083_020b9010(void *heap);
extern void func_ov022_020a4798(void *heap, int x, int y);
extern void func_ov022_0209fb24(void);

int func_ov083_020b8114(void *obj) {
    void *h = NNSi_FndGetCurrentRootHeap();
    func_ov083_020b8178(obj);
    func_ov083_020b9010(h);
    func_ov022_020a4798(h, 0x4a, 0xc9);
    return (int)func_ov022_0209fb24;
}
