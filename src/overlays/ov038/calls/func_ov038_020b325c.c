extern int NNSi_FndGetCurrentRootHeap();extern void func_ov038_020b3930();extern void func_ov022_0209fab4();extern int data_ov038_020b4ca0;
void func_ov038_020b325c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov038_020b3930(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov038_020b4ca0 = 0;
}
