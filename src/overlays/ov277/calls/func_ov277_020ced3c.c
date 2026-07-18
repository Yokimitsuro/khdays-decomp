extern int func_0203bc78();

struct S { int x[11]; };

int func_ov277_020ced3c(int *a, int b) {
    char *p = *(char **)((char *)a + 0x84);
    p = *(char **)p;
    p = *(char **)(p + 0x3b0);
    *(struct S *)((char *)a + 0x30) = *(struct S *)(p + 0x4);
    return func_0203bc78(a, b);
}
