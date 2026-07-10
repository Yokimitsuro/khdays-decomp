extern void func_02014e2c(int arg0);
extern void func_0202a7dc(int arg0);
extern void func_0202a440(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern void func_ov022_020929cc(int arg0);

void func_ov022_020929dc(unsigned char *arg0, int arg1, int arg2, int arg3) {
    if ((*arg0 & 1) != 0) {
        func_02014e2c((int)(arg0 + 0x24));
        func_0202a7dc((int)(arg0 + 4));
        func_0202a440((int)(arg0 + 0x10c));
        NNSi_FndFreeFromDefaultHeap(*(int *)(arg0 + 0x130));
        func_ov022_020929cc((int)arg0);
    }
}
