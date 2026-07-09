typedef struct { int a, b, c; } T3_0208484c;
void func_ov022_0208484c(int *arg0, int arg1, int arg2, T3_0208484c *arg3) {
    *(T3_0208484c *)(arg0 + 7) = *arg3;
    arg0[1] = 1;
    arg0[2] = arg1;
    arg0[3] = arg2;
    *arg0 |= 2;
}
