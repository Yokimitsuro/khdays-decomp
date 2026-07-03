extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov047_020b327c(int a);
extern void func_ov047_020b3864(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov047_020b3234(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov047_020b327c(param);
    func_ov047_020b3864(obj);
    func_ov022_020a4798(obj, 0x52, 0xd4);
    return (void *)func_ov022_0209fb24;
}
