extern int NNSi_FndGetCurrentRootHeap();extern void func_ov077_020b8810();extern void func_ov022_0209fab4();extern int data_ov077_020b9b80;
void func_ov077_020b813c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov077_020b8810(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov077_020b9b80 = 0;
}
