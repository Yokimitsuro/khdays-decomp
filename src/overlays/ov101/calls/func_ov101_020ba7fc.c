extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov101_020bafb4(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov101_020bc0e0;
void func_ov101_020ba7fc(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov101_020bafb4(obj);
    func_ov022_0209fab4(obj);
    data_ov101_020bc0e0 = 0;
}
