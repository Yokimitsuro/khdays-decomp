extern int *func_01fffde0(int i);

int func_ov017_02080c88(void) {
    int i;
    for (i = 0; i < 4; i++) {
        int *p = func_01fffde0(i);
        if (p) {
            *(unsigned long long *)p |= 0x4000000000000000ULL;
        }
    }
    return 1;
}
