extern int NNSi_FndGetCurrentRootHeap();extern void func_ov085_020b8794();extern void func_ov022_0209fab4();extern int data_ov085_020b9260;
void func_ov085_020b813c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov085_020b8794(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov085_020b9260 = 0;
}
