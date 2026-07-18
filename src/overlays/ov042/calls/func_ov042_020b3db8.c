extern void func_ov022_02091228(int a);
extern void NNSi_FndFreeFromDefaultHeap(int a);
extern void func_0202a7dc(int a);
extern int data_ov042_020b4800;

void func_ov042_020b3db8(int self) {
    int base = *(int *)&data_ov042_020b4800 + 0x2c + 0x2c00;
    int i;
    func_ov022_02091228(*(int *)(self + 0x2000 + 0x644));
    func_ov022_02091228(*(int *)(self + 0x2000 + 0x644) + 0x30);
    NNSi_FndFreeFromDefaultHeap(*(int *)(self + 0x2000 + 0x644));
    for (i = 0; i < 7; i++) {
        func_0202a7dc(base + 0x18 + i * 0x10c);
    }
}
