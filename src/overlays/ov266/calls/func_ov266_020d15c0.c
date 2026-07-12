/* Decay the value at *(obj)+0x57c toward 0 by 0x180/0x1000 each frame; once it drops to 0x200
 * or below, run ov266_020d0200, play the anim (ov107 mode 8) and register the handler. */
extern void func_ov266_020d0200(int a);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov266_020d1630(int);
void func_ov266_020d15c0(int param_1) {
    int child = *(int *)(param_1 + 4);
    int obj = *(int *)child;
    int base = *(int *)(obj + 0x57c);
    *(int *)(obj + 0x57c) = base + (-base * 0x180) / 0x1000;
    if (*(int *)(*(int *)child + 0x57c) > 0x200) return;
    func_ov266_020d0200(child);
    func_ov107_020c9264(*(int *)child, 8, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d1630);
}
