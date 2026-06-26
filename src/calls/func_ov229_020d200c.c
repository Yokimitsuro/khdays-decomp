extern int func_ov107_020c2b38();
extern int func_ov107_020c7c1c();

int func_ov229_020d200c(int *r0, int r1) {
    int i;
    for (i = 0; i < 8; i++) {
        func_ov107_020c2b38(r1, r0[i + 0xf0]);
    }
    return func_ov107_020c7c1c(r0, r1);
}
