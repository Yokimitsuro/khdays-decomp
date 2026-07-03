extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov080_020b8720(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov080_020b9be0;
void func_ov080_020b813c(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov002_02051fc8(obj + 0x2c30, obj + 0x910);
    func_ov080_020b8720(obj);
    func_ov022_0209fab4(obj);
    data_ov080_020b9be0 = 0;
}
