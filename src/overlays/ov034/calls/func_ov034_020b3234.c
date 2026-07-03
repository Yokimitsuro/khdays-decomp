extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov034_020b32ac(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov034_020b50b4(int a);
extern void func_ov022_0209fb24(void);
void *func_ov034_020b3234(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    *(int *)(obj + 0x2e1c) = 0;
    func_ov034_020b32ac(param);
    func_ov022_020a4798(obj, 0x45, 0xc6);
    func_ov034_020b50b4(obj);
    return (void *)func_ov022_0209fb24;
}
