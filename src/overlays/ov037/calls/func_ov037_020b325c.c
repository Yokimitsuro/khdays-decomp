extern int NNSi_FndGetCurrentRootHeap();extern void func_ov037_020b39ec();extern void func_ov037_020b3c44();extern void func_ov022_0209fab4();extern int data_ov037_020b4e20;
void func_ov037_020b325c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov037_020b39ec(r);
    func_ov037_020b3c44(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov037_020b4e20 = 0;
}
