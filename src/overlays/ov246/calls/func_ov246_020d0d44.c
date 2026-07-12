/* Clear the child field at +0x14, set anim state 1, then dispatch via
 * func_0203c634 (handler func_ov246_020d0d80). */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov246_020d0d80(void);
void func_ov246_020d0d44(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x14) = 0;
    func_ov107_020c9264(*(int *)child, 1, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov246_020d0d80);
}
