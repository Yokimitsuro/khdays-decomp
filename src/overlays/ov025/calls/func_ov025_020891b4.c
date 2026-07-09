extern void func_ov025_020895b8();
extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_020891b4(int *arg0) {
    func_ov025_020895b8(arg0);
    if (arg0[5] != 0) NNSi_FndFreeFromDefaultHeap(arg0[5]);
    if (arg0[4] != 0) NNSi_FndFreeFromDefaultHeap(arg0[4]);
    if (arg0[3] != 0) NNSi_FndFreeFromDefaultHeap(arg0[3]);
}
