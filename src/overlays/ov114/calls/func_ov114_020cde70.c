extern void func_ov107_020c9264(int v, int a, int b);
extern void func_0203c634(void *a, int b, void *cb);
extern void func_ov114_020cdeac(void);

void func_ov114_020cde70(char *a) {
    char *p = *(char **)(a + 0x4);
    func_ov107_020c9264(*(int *)p, 5, 0);
    *(int *)(p + 0x44) = 0;
    func_0203c634(a, *(signed char *)(a + 0x20), func_ov114_020cdeac);
}
