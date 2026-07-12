struct w3 { int a, b, c; };
/* Store the +0x18 vector and mark sub-state 1. */
void func_ov245_020d15a4(int param_1, int param_2) {
    *(struct w3 *)(param_1 + 0x18) = *(struct w3 *)param_2;
    *(signed char *)(*(int *)param_1 + 0x1c7) = 1;
}
