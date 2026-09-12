extern int func_ov107_020c2b38();
extern int func_ov107_020c7c1c();

int func_ov227_020d02e4(int *r0, int r1)
{
    int i;

    for (i = 0; i < 10; i++) {
        int v = r0[i + 0xfb];
        if (v) {
            func_ov107_020c2b38(r1, v);
        }
    }
    return func_ov107_020c7c1c(r0, r1);
}
