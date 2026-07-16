extern int func_020326a8();

void func_ov005_0204e33c(int a, int *b) {
    int i;
    int v;
    for (i = 0; i < 2; i++) {
        v = b[i + 5];
        if (v != -1) {
            func_020326a8(a, v);
        }
    }
}
