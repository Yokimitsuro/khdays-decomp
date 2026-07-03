extern int NNSi_FndGetCurrentRootHeap();extern void func_ov038_020b327c();extern void func_ov038_020b3820();extern void func_ov022_020a4798();extern void func_ov022_0209fb24(void);
int func_ov038_020b3234(int p) {
    int r = NNSi_FndGetCurrentRootHeap(p);
    func_ov038_020b327c(p);
    func_ov038_020b3820(r);
    func_ov022_020a4798(r, 0x49, 0xc8);
    return (int)func_ov022_0209fb24;
}
