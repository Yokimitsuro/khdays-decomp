extern int func_0203257c();

void func_ov008_02054858(int a, int *b, int c) {
    int i;
    for (i = 0; i < 2; i++) {
        int v = b[i + 5];
        if (v != -1) {
            func_0203257c(a, v, c);
        }
    }
}
