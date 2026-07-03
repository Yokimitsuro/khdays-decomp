extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov058_020b663c(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov022_0209fab4(int a);
extern int data_ov058_020b7e00;
void func_ov058_020b5a5c(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov058_020b663c(obj);
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov002_02051fc8(obj + 0x2c80, obj + 0x910);
    func_ov022_0209fab4(obj);
    data_ov058_020b7e00 = 0;
}
