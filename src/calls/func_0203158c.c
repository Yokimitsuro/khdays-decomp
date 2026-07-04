extern void func_02031130(int a);
extern void func_01fffac0(int a);
extern int *data_0204c230;

void func_0203158c(int param_1) {
    int *ctx = data_0204c230;
    if (*ctx != 0) return;
    func_02031130(param_1);
    func_01fffac0(ctx[1] + param_1 * 0x20);
}
