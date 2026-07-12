/* Allocate, seed +0x390 from *(owner+0x3dc), install callback (+0x18c), init and return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov245_020d0828(int);
int func_ov245_020d07f0(int param_1) {
    int obj = func_0203d15c(0x3ac);
    *(int *)(obj + 0x390) = *(int *)(param_1 + 0x3dc);
    *(int *)(obj + 0x18c) = (int)&func_ov245_020d0828;
    func_ov107_020c6624(obj, 0);
    return obj;
}
