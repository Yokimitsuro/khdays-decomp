extern void func_0203b9fc(void *p, int a, int b, int c);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov131_020cef38(void);

void func_ov131_020ceed8(char *obj) {
    int *state = *(int **)(obj + 4);
    if (*(signed char *)(*state + 0x310) == 10) return;
    func_0203b9fc((void *)state[1], 2, 1, 0);
    func_0203b9fc((void *)state[1], 0, 2, 0);
    func_0203c634(obj, *(signed char *)(obj + 0x20), func_ov131_020cef38);
}
