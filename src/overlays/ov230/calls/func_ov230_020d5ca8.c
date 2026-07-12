/* Allocate a 0x3a0-byte object, link it back to this owner (+0x388),
 * install the 020d5cdc callback (+0x18c), init via 020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov230_020d5cdc(int);
int func_ov230_020d5ca8(int param_1) {
    int obj = func_0203d15c(0x3a0);
    *(int *)(obj + 0x388) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov230_020d5cdc;
    func_ov107_020c6624(obj, 0);
    return obj;
}
