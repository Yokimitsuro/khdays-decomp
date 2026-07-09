typedef struct { int a, b, c; } T3_020ad44c;
extern void func_ov022_02095948(T3_020ad44c *out, int arg1, int arg2, int arg3);
void func_ov022_020ad44c(int *arg0, int arg1, int arg2, int arg3) {
    T3_020ad44c tmp;
    func_ov022_02095948(&tmp, arg1, arg2, arg3);
    *(T3_020ad44c *)arg0 = tmp;
}
