/* For the two records at param_2[5] and param_2[6], forward any that is not -1 to
 * func_0203281c together with param_1 and param_3. */
extern void func_0203281c(int a, int b, int c);

void func_ov009_02051bc4(int param_1, int param_2, int param_3) {
    int i;
    for (i = 0; i < 2; i++) {
        int v = ((int *)param_2)[i + 5];
        if (v != -1) {
            func_0203281c(param_1, v, param_3);
        }
    }
}
