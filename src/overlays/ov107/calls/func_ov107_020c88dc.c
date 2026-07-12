struct w3 { int a, b, c; };
/* Store the +0x2fc vector and the +0x308 field. */
void func_ov107_020c88dc(int param_1, int param_2, int param_3) {
    *(struct w3 *)(param_1 + 0x2fc) = *(struct w3 *)param_2;
    *(int *)(param_1 + 0x308) = param_3;
}
