extern unsigned int *NNSi_FndGetCurrentRootHeap(void);
extern short func_02030788(void);
extern void func_ov022_0208981c(void);
extern void func_ov022_02089e20(void);
extern void func_ov022_02089a8c(void);
int func_ov022_02089704(void) {
    unsigned int *p = NNSi_FndGetCurrentRootHeap();
    if (*p & 1) return 0;
    if (func_02030788() == 0) {
        func_ov022_0208981c();
        func_ov022_02089e20();
    }
    func_ov022_02089a8c();
    return 0;
}
