extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov076_020b8160(int param);
extern void func_ov076_020b8a78(int obj);
extern void func_ov022_020a4798(int obj, int tag_a, int tag_b);
extern void func_ov022_0209fb24(void);

void *func_ov076_020b8114(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov076_020b8160(param);
    func_ov076_020b8a78(obj);
    func_ov022_020a4798(obj, 0x46, 0xcf);
    return (void *)func_ov022_0209fb24;
}
