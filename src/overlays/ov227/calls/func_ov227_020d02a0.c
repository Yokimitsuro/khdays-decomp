extern int func_ov107_020c2b20();
extern int func_ov107_020c7b70();

int func_ov227_020d02a0(int *r0, int r1)
{
    int i;

    for (i = 0; i < 10; i++) {
        int v = r0[i + 0xfb];
        if (v) {
            func_ov107_020c2b20(r1, v);
        }
    }
    return func_ov107_020c7b70(r0, r1);
}
