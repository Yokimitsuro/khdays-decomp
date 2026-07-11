/* Repeatedly invoke func_02013768 (which advances the cursor param_3 in place via the
 * &param_3 pointer, param_4 being its paired second word) and return the maximum result
 * seen, stopping when the cursor reaches 0. */
extern int func_02013768(int *a, int b, int c, void *d);
int func_02013814(int *param_1, int param_2, int param_3, int param_4) {
    int result = 0;
    if (param_3 != 0) {
        do {
            int r = func_02013768(param_1, param_2, param_3, &param_3);
            if (r > result) result = r;
        } while (param_3 != 0);
    }
    return result;
}
