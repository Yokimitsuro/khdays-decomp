struct w3 { int a, b, c; };
/* Mark sub-state 1 and store the +0x18 vector. */
void func_ov237_020d0cac(int param_1, int param_2) {
    *(signed char *)(*(int *)param_1 + 0x1c7) = 1;
    *(struct w3 *)(param_1 + 0x18) = *(struct w3 *)param_2;
}
