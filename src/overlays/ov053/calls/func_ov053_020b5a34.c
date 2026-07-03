extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov053_020b5aac(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov053_020b78b4(int a);
extern void func_ov022_0209fb24(void);
void *func_ov053_020b5a34(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    *(int *)(obj + 0x2e1c) = 0;
    func_ov053_020b5aac(param);
    func_ov022_020a4798(obj, 0x45, 0xc6);
    func_ov053_020b78b4(obj);
    return (void *)func_ov022_0209fb24;
}
