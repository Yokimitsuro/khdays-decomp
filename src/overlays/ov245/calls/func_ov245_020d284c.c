/* Allocate, seed +0x390 from *(owner+0x3c8), install callback (+0x18c), init and return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov245_020d2884(int);
int func_ov245_020d284c(int param_1) {
    int obj = func_0203d15c(0x3ac);
    *(int *)(obj + 0x390) = *(int *)(param_1 + 0x3c8);
    *(int *)(obj + 0x18c) = (int)&func_ov245_020d2884;
    func_ov107_020c6624(obj, 0);
    return obj;
}
