/* Play the anim (ov107 mode 8), compute a value from +0x5c/+0x64 (via 020050b4) offset by
 * 0x3244, store it to +0x18/+0x14 and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_020050b4(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov277_020d2f04(int);
void func_ov277_020d2eb4(int param_1) {
    int child = *(int *)(param_1 + 4);
    int v;
    func_ov107_020c9264(*(int *)child, 8, 0);
    v = func_020050b4(*(int *)(child + 0x5c), *(int *)(child + 0x64)) + 0x3244;
    *(int *)(child + 0x18) = v;
    *(int *)(child + 0x14) = v;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov277_020d2f04);
}
