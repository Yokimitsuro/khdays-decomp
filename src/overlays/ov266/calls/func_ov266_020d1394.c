/* Play the anim (ov107 mode 6), reset the timer (+0x40) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov266_020d13d0(int);
void func_ov266_020d1394(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 6, 0);
    *(int *)(child + 0x40) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d13d0);
}
