extern void func_ov022_02091228(int a);
extern void NNSi_FndFreeFromDefaultHeap(int a);
extern void func_0202a7dc(int a);
extern int data_ov050_020b75c0;

void func_ov050_020b615c(int param_1, int param_2, int param_3, int param_4) {
    int base = data_ov050_020b75c0 + 0x2c2c;
    int i;
    func_ov022_02091228(*(int *)(param_1 + 0x2644));
    func_ov022_02091228(*(int *)(param_1 + 0x2644) + 0x30);
    func_ov022_02091228(*(int *)(param_1 + 0x2644) + 0x60);
    NNSi_FndFreeFromDefaultHeap(*(int *)(param_1 + 0x2644));
    base += 0x14;
    i = 0;
    do {
        func_0202a7dc(base);
        i++;
        base += 0x118;
    } while (i < 2);
}
