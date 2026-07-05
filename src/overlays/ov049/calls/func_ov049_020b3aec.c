extern void func_ov022_02091228(int p);
extern void NNSi_FndFreeFromDefaultHeap(int p);
extern void func_0202a7dc(int p);
extern int data_ov049_020b4d00;

void func_ov049_020b3aec(int this_) {
    char *base = (char *)(data_ov049_020b4d00 + 0x2cfc);
    func_ov022_02091228(*(int *)(this_ + 0x2644));
    NNSi_FndFreeFromDefaultHeap(*(int *)(this_ + 0x2644));
    func_0202a7dc((int)(base + 4));
}
