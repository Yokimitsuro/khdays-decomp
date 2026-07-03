extern int NNSi_FndGetCurrentRootHeap();extern void func_ov048_020b39f4();extern void func_ov022_0209fab4();extern int data_ov048_020b4b80;
void func_ov048_020b325c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov048_020b39f4(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov048_020b4b80 = 0;
}
