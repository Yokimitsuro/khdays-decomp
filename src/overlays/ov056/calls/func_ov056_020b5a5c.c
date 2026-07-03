extern int NNSi_FndGetCurrentRootHeap();extern void func_ov056_020b61ec();extern void func_ov056_020b6444();extern void func_ov022_0209fab4();extern int data_ov056_020b7620;
void func_ov056_020b5a5c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov056_020b61ec(r);
    func_ov056_020b6444(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov056_020b7620 = 0;
}
