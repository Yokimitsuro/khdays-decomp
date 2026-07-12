/* Allocate a 0x3bc-byte object, link it back to this owner (+0x390),
 * install the 020d0a58 callback (+0x18c), init via 020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov260_020d0a58(int);
int func_ov260_020d0a24(int param_1) {
    int obj = func_0203d15c(0x3bc);
    *(int *)(obj + 0x390) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov260_020d0a58;
    func_ov107_020c6624(obj, 0);
    return obj;
}
