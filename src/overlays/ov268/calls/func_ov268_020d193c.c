/* Set the target rate (+0x60 = owner_rate*30/30); unless the busy byte at *(child+4)+0xad
 * is set, pose the main node (ov107 mode 2,1) and the sub-node at (*child)+0x3ac (mode 0,1),
 * then register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov268_020d19c0(int);
void func_ov268_020d193c(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x60) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 30;
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)child, 2, 1);
    func_ov107_020c9ee8(*(int *)(*(int *)child + 0x3ac), 0, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov268_020d19c0);
}
