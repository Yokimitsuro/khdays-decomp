/* Unless the busy byte at *(child+0x20) is set, play the anim (ov107 mode 9), clear +0x18 and
 * the +0x74 byte and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov278_020d4d38(int);
void func_ov278_020d4ce8(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)*(int *)(child + 0x20) != 0) return;
    func_ov107_020c9264(*(int *)child, 9, 0);
    *(int *)(child + 0x18) = 0;
    *(signed char *)(child + 0x74) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov278_020d4d38);
}
