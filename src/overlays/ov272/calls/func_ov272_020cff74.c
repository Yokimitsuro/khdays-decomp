/* Configure the main spline channel of *(param_1+0x384) with the s16 param_2 and finalize
 * it; then, depending on the sub-state byte (+0x1c6), configure the owner list at *(+0x3a8):
 * channel 0 for state 5, channel 1 (rate 1) for state 6. */
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c7ac(int a, int b);
void func_ov272_020cff74(int param_1, int param_2, int param_3) {
    int s;
    func_0203b9fc(*(int *)(param_1 + 0x384), 0, (short)param_2, param_3);
    func_0203c7ac(*(int *)(param_1 + 0x384), 0);
    s = *(signed char *)(param_1 + 0x1c6);
    if (s == 5) {
        func_0203b9fc(*(int *)*(int *)(param_1 + 0x3a8), 0, 0, 0);
    } else if (s == 6) {
        func_0203b9fc(*(int *)*(int *)(param_1 + 0x3a8), 0, 1, 0);
    }
}
