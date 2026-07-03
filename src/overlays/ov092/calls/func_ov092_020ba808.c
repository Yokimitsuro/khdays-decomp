extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_ov092_020bbf5c(int a);
extern void func_ov002_02051fc8(int a, int b);
extern void func_ov092_020bae84(int a);
extern void func_ov092_020bc1d4(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov092_020bc4e0;
void func_ov092_020ba808(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    func_ov092_020bbf5c(obj);
    func_ov002_02051fc8(obj + 0x2c2c, obj + 0x910);
    func_ov092_020bae84(obj);
    func_ov092_020bc1d4(obj);
    func_ov022_0209fab4(obj);
    data_ov092_020bc4e0 = 0;
}
