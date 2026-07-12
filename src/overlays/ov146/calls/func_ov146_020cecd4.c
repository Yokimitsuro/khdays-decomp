/* Unless the busy byte at *(child+4)+0xad is set, play the anim (ov107 mode 5,1) and register
 * the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov146_020ced18(int);
void func_ov146_020cecd4(int param_1) {
    int child = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(child + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)child, 5, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020ced18);
}
