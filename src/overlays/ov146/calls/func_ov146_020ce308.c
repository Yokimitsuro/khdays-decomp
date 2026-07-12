/* Allocate, link owner (+0x3b4), set +0x19c=0x10, install callback (+0x18c), init and return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov146_020ce344(int);
int func_ov146_020ce308(int param_1) {
    int obj = func_0203d15c(0x3bc);
    *(int *)(obj + 0x3b4) = param_1;
    *(signed char *)(obj + 0x19c) = 0x10;
    *(int *)(obj + 0x18c) = (int)&func_ov146_020ce344;
    func_ov107_020c6624(obj, 0);
    return obj;
}
