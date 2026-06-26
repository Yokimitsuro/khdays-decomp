extern int func_02032710();

void func_ov008_02054ba4(int a, int *b, int c) {
    unsigned int x;
    int i;
    for (i = 0; i < 2; i++) {
        int v = b[i + 5];
        if (v != -1) {
            func_02032710(a, v, c);
        }
    }
    x = ((c != 0) ? 1u : 0u) << 31;
    b[33] = (((unsigned int)b[33]) & ~2u) | (x >> 30);
}
