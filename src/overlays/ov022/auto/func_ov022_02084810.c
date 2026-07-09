typedef struct { int a, b, c; } T3_02084810;
void func_ov022_02084810(int *arg0, int arg1, T3_02084810 *arg2) {
    *(T3_02084810 *)(arg0 + 7) = *arg2;
    arg0[1] = 2;
    arg0[5] = arg1;
    arg0[4] = 0;
    *arg0 |= 2;
}
