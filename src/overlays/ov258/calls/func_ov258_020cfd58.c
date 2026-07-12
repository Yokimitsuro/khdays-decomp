/* Allocate, link owner (+0x390), store arg (+0x38c byte), install callback (+0x18c), init, return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov258_020cfd94(int);
int func_ov258_020cfd58(int param_1, int param_2) {
    int obj = func_0203d15c(0x394);
    *(int *)(obj + 0x390) = param_1;
    *(signed char *)(obj + 0x38c) = param_2;
    *(int *)(obj + 0x18c) = (int)&func_ov258_020cfd94;
    func_ov107_020c6624(obj, 0);
    return obj;
}
