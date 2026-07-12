/* Allocate a 0x3ac-byte object, link it back to this owner (+0x398),
 * install the 020d2674 callback (+0x18c), init via 020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov238_020d2674(int);
int func_ov238_020d2640(int param_1) {
    int obj = func_0203d15c(0x3ac);
    *(int *)(obj + 0x398) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov238_020d2674;
    func_ov107_020c6624(obj, 0);
    return obj;
}
