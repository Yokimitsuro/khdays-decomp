extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov077_020b815c(void *obj);
extern void func_ov077_020b8700(void *heap);
extern void func_ov022_020a4798(void *heap, int x, int y);
extern void func_ov022_0209fb24(void);

int func_ov077_020b8114(void *obj) {
    void *h = NNSi_FndGetCurrentRootHeap();
    func_ov077_020b815c(obj);
    func_ov077_020b8700(h);
    func_ov022_020a4798(h, 0x49, 0xc8);
    return (int)func_ov022_0209fb24;
}
