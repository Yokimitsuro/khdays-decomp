struct w3 { int a, b, c; };
/* Store the +0x1c vector and mark sub-state 3. */
void func_ov256_020d13e0(int param_1, int param_2) {
    *(struct w3 *)(param_1 + 0x1c) = *(struct w3 *)param_2;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 3;
}
