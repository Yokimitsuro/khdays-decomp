/* 0 when param_1 is null, else whether func_ov024_020859d4(param_1) reports state 1. */
extern int func_ov024_020859d4(int arg);
int func_ov024_02085038(int param_1) {
    if (param_1 == 0) return 0;
    return func_ov024_020859d4(param_1) == 1;
}
