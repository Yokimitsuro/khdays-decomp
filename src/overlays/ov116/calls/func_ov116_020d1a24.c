extern void func_ov107_020c9264(int v, int a, int b);
extern void func_0203c634(void *a, int b, void *cb);
extern void func_ov116_020d1a60(void);

void func_ov116_020d1a24(char *a) {
    char *p = *(char **)(a + 0x4);
    func_ov107_020c9264(*(int *)p, 1, 1);
    *(int *)(p + 0x48) = 0;
    func_0203c634(a, *(signed char *)(a + 0x20), func_ov116_020d1a60);
}
