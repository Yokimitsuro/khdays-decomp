/* Store param_2 at +0x2c, then (re)initialize the object via func_ov002_02050d38. */
extern void func_ov002_02050d38(int a, int b, int c, int d);

void func_ov002_02050d28(int param_1, int param_2, int param_3) {
    *(int *)(param_1 + 0x2c) = param_2;
    func_ov002_02050d38(param_1, 0, param_3, 0);
}
