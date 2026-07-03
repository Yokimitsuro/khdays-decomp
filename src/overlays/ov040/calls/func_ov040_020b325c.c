extern int NNSi_FndGetCurrentRootHeap();extern void func_ov040_020b3968();extern void func_ov022_0209fab4();extern int data_ov040_020b4b20;
void func_ov040_020b325c(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov040_020b3968(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov040_020b4b20 = 0;
}
