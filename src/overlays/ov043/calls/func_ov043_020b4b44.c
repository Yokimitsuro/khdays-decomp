/* Set +0x11c to 4 then tail-call the ov043 handler with mode 2. */
extern int func_ov043_020b4b60(int, int);
int func_ov043_020b4b44(int param_1, int param_2) {
    *(int *)(param_2 + 0x11c) = 4;
    return func_ov043_020b4b60(param_2, 2);
}
