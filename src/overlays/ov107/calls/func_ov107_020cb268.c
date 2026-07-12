/* Allocate a 0x44-byte object, initialise it (with this owner) via 020cb28c and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020cb28c(int a, int b);
int func_ov107_020cb268(int param_1) {
    int obj = func_0203d15c(0x44);
    func_ov107_020cb28c(obj, param_1);
    return obj;
}
