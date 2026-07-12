/* Unless the child gate is set, clear +0x1c/+0x20, kick anim (3, phase 1), then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020cde74(int);
void func_ov253_020cde24(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4)) != 0) return;
    *(int *)(owner + 0x1c) = 0;
    *(int *)(owner + 0x20) = 0;
    func_ov107_020c9264(*(int *)owner, 3, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020cde74);
}
