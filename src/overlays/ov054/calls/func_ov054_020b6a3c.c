extern void func_ov022_02091228(int a);
extern void NNSi_FndFreeFromDefaultHeap(int a);
void func_ov054_020b6a3c(int this) {
    func_ov022_02091228(*(int *)(this + 0x2644));
    func_ov022_02091228(*(int *)(this + 0x2644) + 0x30);
    NNSi_FndFreeFromDefaultHeap(*(int *)(this + 0x2644));
}
