extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov097_020ba830(int a);
extern void func_ov097_020bad0c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov097_020ba7d4(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov097_020ba830(param);
    func_ov097_020bad0c(obj);
    func_ov022_020a4798(obj, 0x54, 0xd7);
    return (void *)func_ov022_0209fb24;
}
