extern void func_ov022_02091228(int p);
extern void NNSi_FndFreeFromDefaultHeap(int p);
extern void func_0202a7dc(int p);
extern int data_ov068_020b7500;

void func_ov068_020b62ec(int this_) {
    char *base = (char *)(data_ov068_020b7500 + 0x2cfc);
    func_ov022_02091228(*(int *)(this_ + 0x2644));
    NNSi_FndFreeFromDefaultHeap(*(int *)(this_ + 0x2644));
    func_0202a7dc((int)(base + 4));
}
