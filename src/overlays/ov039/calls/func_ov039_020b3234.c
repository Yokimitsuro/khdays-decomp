extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov039_020b329c(int a);
extern void func_ov039_020b3d30(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov039_020b3234(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov039_020b329c(param);
    func_ov039_020b3d30(obj);
    func_ov022_020a4798(obj, 0x4d, 0xcd);
    return (void *)func_ov022_0209fb24;
}
