extern int func_ov107_020c2b20();
extern int func_ov107_020c7b70();

int func_ov228_020ce390(int *r0, int r1) {
    int i;
    for (i = 0; i < 8; i++) {
        func_ov107_020c2b20(r1, r0[0xf0 + i]);
    }
    return func_ov107_020c7b70(r0, r1);
}
