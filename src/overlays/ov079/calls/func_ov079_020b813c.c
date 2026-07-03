extern int NNSi_FndGetCurrentRootHeap();extern void func_ov079_020b8848();extern void func_ov022_0209fab4();extern int data_ov079_020b9a00;
void func_ov079_020b813c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov079_020b8848(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov079_020b9a00 = 0;
}
