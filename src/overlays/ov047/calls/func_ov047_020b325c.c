extern int NNSi_FndGetCurrentRootHeap();extern void func_ov047_020b38b4();extern void func_ov022_0209fab4();extern int data_ov047_020b4380;
void func_ov047_020b325c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov047_020b38b4(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov047_020b4380 = 0;
}
