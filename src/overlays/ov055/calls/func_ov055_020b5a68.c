extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov055_020b71bc(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov055_020b60e4(int a);
extern void func_ov055_020b7434(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov055_020b7740;
void func_ov055_020b5a68(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov055_020b71bc(obj);
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov055_020b60e4(obj);
    func_ov055_020b7434(obj);
    func_ov022_0209fab4(obj);
    data_ov055_020b7740 = 0;
}
