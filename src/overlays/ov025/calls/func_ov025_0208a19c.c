extern int func_ov025_02089884();
extern int func_ov025_0208a028();
extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_0208a19c(int arg0) {
    func_ov025_02089884(arg0);
    func_ov025_0208a028(arg0);
    int p = *(int *)(arg0 + 0x14);
    if (p == 0) {
        return;
    }
    NNSi_FndFreeFromDefaultHeap(p);
    *(int *)(arg0 + 0x14) = 0;
}
