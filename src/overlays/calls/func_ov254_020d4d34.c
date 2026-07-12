/* When ready (+0x50 == 1) forward the handle at +0x214 to func_ov254_020d4f14 and return its
 * result; otherwise return param_1. */
extern int func_ov254_020d4f14(int arg);
int func_ov254_020d4d34(int param_1) {
    if (*(int *)(param_1 + 0x50) == 1) {
        return func_ov254_020d4f14(*(int *)(param_1 + 0x214));
    }
    return param_1;
}
