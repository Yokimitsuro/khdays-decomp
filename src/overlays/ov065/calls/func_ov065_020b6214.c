extern void func_0202a7dc(int a);
extern void func_ov022_02091228(int a);
extern void NNSi_FndFreeFromDefaultHeap(int a);
extern int data_ov065_020b7340;

void func_ov065_020b6214(int self) {
    int base = *(int *)&data_ov065_020b7340 + 0x2c80;
    int i;
    char *p;
    func_0202a7dc(base + 4);
    p = (char *)(base + 0x12c);
    for (i = 0; i < 6; i++, p += 0x120) {
        func_0202a7dc((int)p);
    }
    func_ov022_02091228(*(int *)(self + 0x2000 + 0x644));
    NNSi_FndFreeFromDefaultHeap(*(int *)(self + 0x2000 + 0x644));
}
