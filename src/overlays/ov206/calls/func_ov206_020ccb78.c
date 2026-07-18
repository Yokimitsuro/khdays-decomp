extern int func_0203bc78();

struct S { int x[11]; };

int func_ov206_020ccb78(int *a, int b) {
    char *p = *(char **)((char *)a + 0x84);
    p = *(char **)p;
    p = *(char **)(p + 0x3d8);
    *(struct S *)((char *)a + 0x30) = *(struct S *)(p + 0x4);
    return func_0203bc78(a, b);
}
