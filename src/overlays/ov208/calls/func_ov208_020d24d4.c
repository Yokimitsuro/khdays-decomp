/* Set bit 0 of the halfword at (*child)+0x1ae, play the anim (ov107 mode 5), reset the
 * timer (+0x2c) and mode byte (+0x49), then register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov208_020d2528(int);
void func_ov208_020d24d4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(unsigned short *)(*(int *)child + 0x1ae) |= 1;
    func_ov107_020c9264(*(int *)child, 5, 0);
    *(int *)(child + 0x2c) = 0;
    *(signed char *)(child + 0x49) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov208_020d2528);
}
