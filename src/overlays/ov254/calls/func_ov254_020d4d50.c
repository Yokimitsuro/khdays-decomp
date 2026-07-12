/* When ready (+0x50 == 1) forward the handle at +0x214 and param_2 to func_ov254_020d4f30;
 * otherwise return param_1. */
extern int func_ov254_020d4f30(int a, int b);
int func_ov254_020d4d50(int param_1, int param_2) {
    if (*(int *)(param_1 + 0x50) == 1) {
        return func_ov254_020d4f30(*(int *)(param_1 + 0x214), param_2);
    }
    return param_1;
}
