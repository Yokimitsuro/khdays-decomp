extern int NNSi_FndGetCurrentRootHeap();extern void func_ov081_020b8c98();extern void func_ov022_0209fab4();extern int data_ov081_020b96e0;
void func_ov081_020b813c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov081_020b8c98(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov081_020b96e0 = 0;
}
