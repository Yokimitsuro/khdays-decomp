/* Play the anim (ov107 mode 0,1), clear the +0x6a byte and the +0x70 field, register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov213_020cfcd0(int);
void func_ov213_020cfc90(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0, 1);
    *(signed char *)(child + 0x6a) = 0;
    *(int *)(child + 0x70) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov213_020cfcd0);
}
