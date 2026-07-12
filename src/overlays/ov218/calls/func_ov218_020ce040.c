/* Allocate, link owner (+0x390), set +0x19c=0x30, install callback (+0x18c), init and return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov218_020ce07c(int);
int func_ov218_020ce040(int param_1) {
    int obj = func_0203d15c(0x3b8);
    *(int *)(obj + 0x390) = param_1;
    *(signed char *)(obj + 0x19c) = 0x30;
    *(int *)(obj + 0x18c) = (int)&func_ov218_020ce07c;
    func_ov107_020c6624(obj, 0);
    return obj;
}
