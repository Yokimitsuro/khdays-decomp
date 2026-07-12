/* Allocate a 0x1ec-byte object, initialise it (with this owner) via ov107_020cac24 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020cac24(int a, int b);
int func_ov107_020ca900(int param_1) {
    int obj = func_0203d15c(0x1ec);
    func_ov107_020cac24(obj, param_1);
    return obj;
}
