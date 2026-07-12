/* Guarded tail-call: 0 when param_1 is null, else func_ov024_02085878(param_1). */
extern int func_ov024_02085878(int arg);
int func_ov024_02084ffc(int param_1) {
    if (param_1 == 0) return 0;
    return func_ov024_02085878(param_1);
}
