extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov054_020b5aa0(int a);
extern int func_02020a9c(void);
extern void func_ov054_020b6230(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov054_020b5a34(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov054_020b5aa0(param);
    if (func_02020a9c() != 0x2a)
        func_ov054_020b6230(obj);
    func_ov022_020a4798(obj, 0x47, 0xd3);
    return (void *)func_ov022_0209fb24;
}
