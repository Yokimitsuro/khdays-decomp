extern void func_0203c634(void *a, int b, void *cb);
extern void func_ov144_020cd450(void);

void func_ov144_020cd41c(char *a) {
    char *p = *(char **)a;
    char *q = *(char **)(a + 4);
    int delta = *(int *)(q + 0x40) - *(int *)(p + 0x2c);
    *(int *)(q + 0x40) = delta;
    if (delta > 0) return;
    func_0203c634(a, *(signed char *)(a + 0x20), func_ov144_020cd450);
}
