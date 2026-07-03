extern int NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a7dc(int a);
extern void func_ov100_020bb718(int a);
extern void func_ov022_0209fab4(int a);
extern int data_ov100_020bc1c0;
void func_ov100_020ba7fc(void) {
    int obj = NNSi_FndGetCurrentRootHeap();
    if (*(int *)(obj + 0x2c2c) != 0) {
        func_0202a7dc(obj + 0x2c30);
        *(int *)(obj + 0x2c2c) = 0;
    }
    func_ov100_020bb718(obj);
    func_ov022_0209fab4(obj);
    data_ov100_020bc1c0 = 0;
}
