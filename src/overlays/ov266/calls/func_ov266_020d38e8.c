/* Allocate a 0x38c-byte object, link it back to this owner (+0x384),
 * install the 020d391c callback (+0x18c), init via 020c6624 and return it. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov266_020d391c(int);
int func_ov266_020d38e8(int param_1) {
    int obj = func_0203d15c(0x38c);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov266_020d391c;
    func_ov107_020c6624(obj, 0);
    return obj;
}
