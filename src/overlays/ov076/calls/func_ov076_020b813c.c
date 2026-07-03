extern int NNSi_FndGetCurrentRootHeap();extern void func_ov076_020b88cc();extern void func_ov076_020b8b24();extern void func_ov022_0209fab4();extern int data_ov076_020b9d00;
void func_ov076_020b813c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov076_020b88cc(r);
    func_ov076_020b8b24(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov076_020b9d00 = 0;
}
