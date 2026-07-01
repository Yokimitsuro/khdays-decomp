extern void func_0203c634(void *a, int b, int c);

void func_ov163_020cf340(char *a) {
    char *p = *(char **)(a + 4);
    if (**(char **)(p + 0x58) != 0) return;
    (*(char **)p)[0x1c7] = 9;
    func_0203c634(a, *(signed char *)(a + 0x20), 0);
}
