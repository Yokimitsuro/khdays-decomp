extern int func_ov107_020c2b38();
extern int func_ov107_020c7c1c();

void func_ov223_020d02cc(int *a, int b)
{
    int i;
    for (i = 0; i < 4; i++) {
        int v = a[i + 0xfb];
        if (v)
            func_ov107_020c2b38(b, v);
    }
    func_ov107_020c7c1c(a, b);
}
