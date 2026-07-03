extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov078_020b8d1c(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov022_0209fab4(int a);
extern int data_ov078_020ba4e0;
void func_ov078_020b813c(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov078_020b8d1c(obj);
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov002_02051fc8(obj + 0x2c80, obj + 0x910);
    func_ov022_0209fab4(obj);
    data_ov078_020ba4e0 = 0;
}
