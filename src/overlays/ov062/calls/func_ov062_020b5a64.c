extern int NNSi_FndGetCurrentRootHeap();extern int func_ov062_020b6010();extern void func_ov062_020b6ffc();extern void func_ov062_020b62d0();extern void func_ov022_0209fab4();extern int data_ov062_020b80e0;
void func_ov062_020b5a64(void) {
    int r = NNSi_FndGetCurrentRootHeap();
    func_ov062_020b6010(r);
    func_ov062_020b6ffc(r);
    func_ov062_020b62d0(r);
    func_ov022_0209fab4(r);
    *(int *)&data_ov062_020b80e0 = 0;
}
