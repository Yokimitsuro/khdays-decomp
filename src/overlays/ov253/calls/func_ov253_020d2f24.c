/* Arm the 020c5af8 timer on the +0x388 sub-object, kick anim 1, clear +0x1c, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_ov253_020d2f7c(int);
void func_ov253_020d2f24(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c5af8(*(int *)(*(int *)owner + 0x388), 0x16b, 9, *(int *)owner + 0x74);
    func_ov107_020c9264(*(int *)owner, 1, 0);
    *(int *)(owner + 0x1c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d2f7c);
}
