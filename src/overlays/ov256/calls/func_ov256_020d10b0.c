/* Allocate, link owner (+0x3ac), store arg (+0x394 byte), install callback (+0x18c), init, return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov256_020d10ec(int);
int func_ov256_020d10b0(int param_1, int param_2) {
    int obj = func_0203d15c(0x3b0);
    *(int *)(obj + 0x3ac) = param_1;
    *(signed char *)(obj + 0x394) = param_2;
    *(int *)(obj + 0x18c) = (int)&func_ov256_020d10ec;
    func_ov107_020c6624(obj, 0);
    return obj;
}
