extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov034_020b510c(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov034_020b5660;
void func_ov034_020b3268(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov002_02051fc8(obj + 0x2c80, obj + 0x910);
    func_ov034_020b510c(obj);
    func_ov022_0209fab4(obj);
    data_ov034_020b5660 = 0;
}
