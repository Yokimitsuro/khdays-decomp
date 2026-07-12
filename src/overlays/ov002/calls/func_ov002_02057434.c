/* Dispatch param_2 to one of two handlers by whether param_1 is zero. */
extern void func_0201e374(int arg);
extern void func_ov002_020637b4(int arg);

void func_ov002_02057434(int param_1, int param_2) {
    if (param_1 != 0) {
        func_0201e374(param_2);
    } else {
        func_ov002_020637b4(param_2);
    }
}
