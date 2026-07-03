extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov036_020b49bc(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov036_020b38e4(int a);
extern void func_ov036_020b4c34(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov036_020b4f40;
void func_ov036_020b3268(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov036_020b49bc(obj);
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov036_020b38e4(obj);
    func_ov036_020b4c34(obj);
    func_ov022_0209fab4(obj);
    data_ov036_020b4f40 = 0;
}
