/* Tail-call the shared dispatcher func_ov008_02056268 with func_ov008_02056230 as handler. */
extern int func_ov008_02056268(int a, int b, int c, int handler);
extern void func_ov008_02056230(void);

int func_ov008_020563f0(int param_1, int param_2, int param_3) {
    return func_ov008_02056268(param_1, param_2, param_3, (int)&func_ov008_02056230);
}
