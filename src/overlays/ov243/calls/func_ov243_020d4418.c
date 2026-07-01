extern void func_0203c634(void *a, int b, void *cb);
extern void func_ov243_020d444c(void);

void func_ov243_020d4418(char *a) {
    char *p = *(char **)a;
    char *q = *(char **)(a + 4);
    int delta = *(int *)(q + 0x2c) - *(int *)(p + 0x2c);
    *(int *)(q + 0x2c) = delta;
    if (delta > 0) return;
    func_0203c634(a, *(signed char *)(a + 0x20), func_ov243_020d444c);
}
