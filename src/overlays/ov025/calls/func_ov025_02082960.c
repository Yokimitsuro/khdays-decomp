extern int NNSi_FndGetCurrentRootHeap();
extern void func_ov025_02083e84();
extern int func_ov025_020829cc();
extern int data_ov025_020b5740;

void * func_ov025_02082960(int *arg0) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    func_ov025_02083e84(*arg0);
    *(int **)&data_ov025_020b5740 = h;
    *h = 9;
    return (void *)func_ov025_020829cc;
}
