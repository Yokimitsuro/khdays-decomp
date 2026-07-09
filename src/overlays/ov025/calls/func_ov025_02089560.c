extern void func_ov025_0208951c();
extern void func_ov025_02089544();

void func_ov025_02089560(int arg0, int arg1, unsigned short arg2, unsigned short arg3) {
    short v1 = *(short *)(arg1 + 2);
    short v2 = *(short *)(arg1 + 4);
    func_ov025_0208951c(arg0, arg1, arg2, arg3);
    func_ov025_02089544(arg0, arg1);
    func_ov025_0208951c(arg0, arg1, v1, v2);
}
