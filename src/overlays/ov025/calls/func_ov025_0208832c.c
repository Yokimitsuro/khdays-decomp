extern int func_0201ef9c();
extern void func_ov025_020882ec();
extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_0208832c(int *arg0, char *arg1, int arg2, int arg3) {
    int *p = (int *)func_0201ef9c(arg1, 0xe, arg2, arg3);
    func_ov025_020882ec(arg0, p, arg2);
    if (p != (int *)0) NNSi_FndFreeFromDefaultHeap(p);
}
