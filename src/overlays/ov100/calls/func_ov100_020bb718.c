extern void func_ov022_02091228(int p);
extern void NNSi_FndFreeFromDefaultHeap(int p);
extern void func_ov002_02051fc8(int a, int b);
extern void func_0202a7dc(int p);

void func_ov100_020bb718(int this_) {
    func_ov022_02091228(*(int *)(this_ + 0x2644));
    NNSi_FndFreeFromDefaultHeap(*(int *)(this_ + 0x2644));
    func_ov002_02051fc8(this_ + 0x2d38, this_ + 0x910);
    func_ov002_02051fc8(this_ + 0x2d8c, this_ + 0x910);
    func_0202a7dc(this_ + 0x2df4);
}
