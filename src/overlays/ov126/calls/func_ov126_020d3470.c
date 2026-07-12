/* Allocate a 0x39c-byte object, link it back to this owner (+0x38c),
 * install the 020d34a4 callback (+0x18c), init via 020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov126_020d34a4(int);
int func_ov126_020d3470(int param_1) {
    int obj = func_0203d15c(0x39c);
    *(int *)(obj + 0x38c) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov126_020d34a4;
    func_ov107_020c6624(obj, 0);
    return obj;
}
