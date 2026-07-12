/* Play the anim (ov107 mode 0xb), reset the timer (+0x24) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov206_020ce0d4(int);
void func_ov206_020ce098(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0xb, 0);
    *(int *)(child + 0x24) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov206_020ce0d4);
}
