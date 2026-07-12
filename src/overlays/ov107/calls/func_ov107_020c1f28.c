/* Allocate a 0x118-byte object, initialise it (with this owner) via 020c207c and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c207c(int a, int b);
int func_ov107_020c1f28(int param_1) {
    int obj = func_0203d15c(0x118);
    func_ov107_020c207c(obj, param_1);
    return obj;
}
