extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov093_020ba820(int param);
extern void func_ov093_020bb138(int obj);
extern void func_ov022_020a4798(int obj, int tag_a, int tag_b);
extern void func_ov022_0209fb24(void);

void *func_ov093_020ba7d4(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov093_020ba820(param);
    func_ov093_020bb138(obj);
    func_ov022_020a4798(obj, 0x46, 0xcf);
    return (void *)func_ov022_0209fb24;
}
