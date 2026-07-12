/* Reset the timer (+0x24=0), play the anim (ov107 mode 1,1) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov274_020d3230(int);
void func_ov274_020d31f4(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x24) = 0;
    func_ov107_020c9264(*(int *)child, 1, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov274_020d3230);
}
