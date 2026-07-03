extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov066_020b5a7c(int a);
extern void func_ov066_020b6064(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov066_020b5a34(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov066_020b5a7c(param);
    func_ov066_020b6064(obj);
    func_ov022_020a4798(obj, 0x52, 0xd4);
    return (void *)func_ov022_0209fb24;
}
