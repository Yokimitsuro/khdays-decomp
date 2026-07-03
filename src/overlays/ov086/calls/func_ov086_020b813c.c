extern int NNSi_FndGetCurrentRootHeap();extern void func_ov086_020b88d4();extern void func_ov022_0209fab4();extern int data_ov086_020b9a60;
void func_ov086_020b813c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov086_020b88d4(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov086_020b9a60 = 0;
}
