struct w3 { int a, b, c; };
/* Optionally copy +0x14 vector out; return +0x38. */
int func_ov107_020c9f48(int param_1, int param_2) {
    if (param_2 != 0) *(struct w3 *)param_2 = *(struct w3 *)(param_1 + 0x14);
    return *(int *)(param_1 + 0x38);
}
