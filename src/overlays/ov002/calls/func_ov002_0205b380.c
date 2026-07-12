/*
 * Provisionally store param_2 at param_1+0x20, run the classifier func_02013768
 * over (param_2, *(param_1+0x24), param_4); if it returns more than 0x3f, replace
 * the field with param_3 instead.
 */
extern int func_02013768(int a, int b, int c, int d);

void func_ov002_0205b380(int param_1, int param_2, int param_3, int param_4) {
    *(int *)(param_1 + 0x20) = param_2;
    if (func_02013768(param_2, *(int *)(param_1 + 0x24), param_4, 0) > 0x3f) {
        *(int *)(param_1 + 0x20) = param_3;
    }
}
