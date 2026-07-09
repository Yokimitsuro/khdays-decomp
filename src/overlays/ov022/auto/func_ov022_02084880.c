typedef struct { int a, b, c; } T3_02084880;
void func_ov022_02084880(int *arg0, int arg1, T3_02084880 *arg2) {
    *(T3_02084880 *)(arg0 + 7) = *arg2;
    arg0[4] = 0;
    arg0[1] = 3;
    arg0[6] = arg1;
    *arg0 |= 2;
}
