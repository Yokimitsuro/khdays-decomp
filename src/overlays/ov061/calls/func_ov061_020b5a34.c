extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov061_020b5a7c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov061_020b6534(int a);
extern void func_ov022_0209fb24(void);
void *func_ov061_020b5a34(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov061_020b5a7c(param);
    func_ov022_020a4798(obj, 0x4e, 0xc7);
    func_ov061_020b6534(obj);
    return (void *)func_ov022_0209fb24;
}
