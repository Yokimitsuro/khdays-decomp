/* Allocate, link owner (+0x398), store arg (+0x390 byte), install callback (+0x18c), init, return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov256_020d03c4(int);
int func_ov256_020d0388(int param_1, int param_2) {
    int obj = func_0203d15c(0x39c);
    *(int *)(obj + 0x398) = param_1;
    *(signed char *)(obj + 0x390) = param_2;
    *(int *)(obj + 0x18c) = (int)&func_ov256_020d03c4;
    func_ov107_020c6624(obj, 0);
    return obj;
}
