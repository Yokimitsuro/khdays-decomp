extern int NNSi_FndGetCurrentRootHeap();extern void func_ov057_020b6130();extern void func_ov022_0209fab4();extern int data_ov057_020b74a0;
void func_ov057_020b5a5c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov057_020b6130(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov057_020b74a0 = 0;
}
