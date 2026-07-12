/* Play the anim (ov107 mode 0xb), set +0x50 = 0x3000, kick the secondary anim
 * (ov107_020c9ee8 on *(child)+0x3b8) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov210_020d263c(int);
void func_ov210_020d25ec(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0xb, 0);
    *(int *)(child + 0x50) = 0x3000;
    func_ov107_020c9ee8(*(int *)(*(int *)child + 0x3b8), 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov210_020d263c);
}
