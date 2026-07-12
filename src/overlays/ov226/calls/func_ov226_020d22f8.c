/* Set anim (1 if child+0x78 else 3), set +0x5c = 0x1000, then dispatch. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov226_020d2340(void);
void func_ov226_020d22f8(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, *(int *)(child + 0x78) != 0 ? 1 : 3, 0);
    *(int *)(child + 0x5c) = 0x1000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov226_020d2340);
}
