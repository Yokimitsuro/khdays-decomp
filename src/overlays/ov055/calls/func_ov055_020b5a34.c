extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov055_020b5aa4(int a);
extern void func_ov055_020b717c(int a);
extern void func_ov055_020b739c(int a);
extern void func_ov055_020b609c(int a);
extern void func_ov022_020a4798(int a, int b, int c);
extern void func_ov022_0209fb24(void);
void *func_ov055_020b5a34(int param) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov055_020b5aa4(param);
    func_ov055_020b717c(obj);
    func_ov055_020b739c(obj);
    func_ov055_020b609c(obj);
    func_ov022_020a4798(obj, 0x4c, 0xcc);
    return (void *)func_ov022_0209fb24;
}
