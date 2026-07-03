extern int NNSi_FndGetCurrentRootHeap();extern void func_ov042_020b3db8();extern void func_ov022_0209fab4();extern int data_ov042_020b4800;
void func_ov042_020b325c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov042_020b3db8(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov042_020b4800 = 0;
}
