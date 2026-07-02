extern void func_01ff8830(void *p, int a, int b);
extern int *func_0201ef9c(int arg, int b);
void func_ov007_0204d33c(int *out, int arg) {
    int *r;
    int t;
    func_01ff8830(out, 0, 0xc);
    r = func_0201ef9c(arg, 0xe);
    out[0] = (int)r;
    t = r[0];
    out[1] = r[1];
    out[2] = out[0] + t;
}
