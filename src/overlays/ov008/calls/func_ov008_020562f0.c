/* Tail-call the shared dispatcher func_ov008_02056268, supplying func_ov008_02055ff8
 * as the per-variant handler (4th arg). */
extern int func_ov008_02056268(int a, int b, int c, int handler);
extern void func_ov008_02055ff8(void);

int func_ov008_020562f0(int param_1, int param_2, int param_3) {
    return func_ov008_02056268(param_1, param_2, param_3, (int)&func_ov008_02055ff8);
}
