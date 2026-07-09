typedef struct { int a, b, c; } T3_02089478;
void func_ov022_02089478(int arg0, int arg1, T3_02089478 *arg2) {
    int b = *(int *)(arg0 + 0x20);
    if (arg1 < 0) return;
    b = arg1 * 0x114 + *(int *)(b + 0xc);
    *(T3_02089478 *)(b + 0xa8) = *arg2;
}
