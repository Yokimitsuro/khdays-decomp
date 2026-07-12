/* Set bit 0 of the halfword at (*child)+0x1ae, play the anim (ov107 mode 7) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov274_020d2a54(int);
void func_ov274_020d2a00(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    func_ov107_020c9264(*(int *)child, 7, 0);
    *(int *)(child + 0x24) = 0;
    *(signed char *)(child + 0x52) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov274_020d2a54);
}
