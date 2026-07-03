extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov065_020b6214(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov065_020b7340;
void func_ov065_020b5a5c(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov065_020b6214(obj);
    func_ov022_0209fab4(obj);
    data_ov065_020b7340 = 0;
}
