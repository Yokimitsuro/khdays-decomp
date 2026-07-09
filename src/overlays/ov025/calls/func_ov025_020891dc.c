extern int func_0201ef9c();
extern void func_ov025_02088b3c();
extern void func_ov025_02088b7c();
extern void func_ov025_02088be4();
extern void NNSi_FndFreeFromDefaultHeap();

void func_ov025_020891dc(int arg0, char *arg1, int arg2, int arg3) {
    int *p = (int *)func_0201ef9c(arg1, 0xe, arg2, arg3);
    int b = p[2];
    int a = p[1];
    func_ov025_02088b3c(arg0, (int)p + *p);
    func_ov025_02088b7c(arg0, (int)p + a);
    func_ov025_02088be4(arg0, (int)p + b);
    if (p != (int *)0) NNSi_FndFreeFromDefaultHeap(p);
}
