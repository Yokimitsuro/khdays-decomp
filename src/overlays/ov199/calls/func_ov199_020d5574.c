/* Allocate a 0x3a4-byte object, link it back to this owner (+0x390),
 * install the 020d55a8 callback (+0x18c), init via 020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov199_020d55a8(int);
int func_ov199_020d5574(int param_1) {
    int obj = func_0203d15c(0x3a4);
    *(int *)(obj + 0x390) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov199_020d55a8;
    func_ov107_020c6624(obj, 0);
    return obj;
}
