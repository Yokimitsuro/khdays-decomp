/* Allocate, link owner (+0x384), install callback (+0x18c), init with arg and return. */
extern int func_0203d15c(int a);
extern void func_ov107_020c6624(int a, int b);
extern void func_ov253_020ce50c(int);
int func_ov253_020ce4d4(int param_1, int param_2) {
    int obj = func_0203d15c(0x3c4);
    *(int *)(obj + 0x384) = param_1;
    *(int *)(obj + 0x18c) = (int)&func_ov253_020ce50c;
    func_ov107_020c6624(obj, param_2);
    return obj;
}
