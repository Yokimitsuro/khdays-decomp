extern int NNSi_FndGetCurrentRootHeap();extern void func_ov066_020b60b4();extern void func_ov022_0209fab4();extern int data_ov066_020b6b80;
void func_ov066_020b5a5c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov066_020b60b4(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov066_020b6b80 = 0;
}
