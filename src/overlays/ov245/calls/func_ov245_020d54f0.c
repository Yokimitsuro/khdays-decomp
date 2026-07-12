/* Allocate, link owner (+0x3cc), set +0x19c=4, install callback (+0x18c), init with arg, set
 * +0x220=0x1000 and return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov245_020d5538(int);
int func_ov245_020d54f0(int param_1, int param_2) {
    int obj = func_0203d15c(0x3d0);
    *(int *)(obj + 0x3cc) = param_1;
    *(signed char *)(obj + 0x19c) = 4;
    *(int *)(obj + 0x18c) = (int)&func_ov245_020d5538;
    func_ov107_020c6624(obj, param_2);
    *(int *)(obj + 0x220) = 0x1000;
    return obj;
}
