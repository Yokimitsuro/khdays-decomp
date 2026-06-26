extern int func_020326cc();

void func_ov009_02051acc(int a, int *b) {
    int i;
    int v;
    for (i = 0; i < 2; i++) {
        v = b[i + 5];
        if (v != -1) {
            func_020326cc(a, v);
        }
    }
}
