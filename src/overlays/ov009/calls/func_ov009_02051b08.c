extern int func_020325ec();

void func_ov009_02051b08(int r0, int *r1, int r2) {
    int i;
    int v;
    for (i = 0; i < 2; i++) {
        v = r1[i + 5];
        if (v != -1) {
            func_020325ec(r0, v, r2);
        }
    }
}
