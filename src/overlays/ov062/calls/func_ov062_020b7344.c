/* Set +0x11c to 4 then tail-call the ov062 handler with mode 2. */
extern int func_ov062_020b7360(int, int);
int func_ov062_020b7344(int param_1, int param_2) {
    *(int *)(param_2 + 0x11c) = 4;
    return func_ov062_020b7360(param_2, 2);
}
