/* Allocate a 0x3d0-byte object, link it back to this owner (+0x384),
 * install the 020d187c callback (+0x18c), init via 020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov255_020d187c(int);
int func_ov255_020d1848(int param_1) {
    int obj = func_0203d15c(0x3d0);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov255_020d187c;
    func_ov107_020c6624(obj, 0);
    return obj;
}
