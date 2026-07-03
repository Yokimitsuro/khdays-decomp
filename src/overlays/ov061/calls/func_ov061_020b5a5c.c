extern int NNSi_FndGetCurrentRootHeap();extern void func_ov061_020b65b8();extern void func_ov022_0209fab4();extern int data_ov061_020b7000;
void func_ov061_020b5a5c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov061_020b65b8(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov061_020b7000 = 0;
}
