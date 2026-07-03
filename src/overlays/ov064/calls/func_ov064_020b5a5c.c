extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a7dc(int a);
extern void func_ov064_020b6978(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov064_020b7420;
void func_ov064_020b5a5c(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    if (*(int *)(obj + 0x2c2c) != 0) {
        func_0202a7dc(obj + 0x2c30);
        *(int *)(obj + 0x2c2c) = 0;
    }
    func_ov064_020b6978(obj);
    func_ov022_0209fab4(obj);
    data_ov064_020b7420 = 0;
}
