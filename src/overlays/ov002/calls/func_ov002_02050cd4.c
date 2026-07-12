/* Resolve param_2 (mode 0xf) into the +0x2c slot, then start the object with
 * func_ov002_02050d38; always returns 1. */
extern int func_0201ef9c(int a, int b);
extern void func_ov002_02050d38(int a, int b, int c, int d);

int func_ov002_02050cd4(int param_1, int param_2) {
    *(int *)(param_1 + 0x2c) = func_0201ef9c(param_2, 0xf);
    func_ov002_02050d38(param_1, 1, 1, 0);
    return 1;
}
