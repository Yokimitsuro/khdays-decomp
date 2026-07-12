/* Unless the child gate is set, kick anim 0x1c and the +0x3a8 sub-anim 0x15, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov235_020cd6c4(int);
void func_ov235_020cd66c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 0xc)) != 0) return;
    func_ov107_020c9264(*(int *)owner, 0x1c, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x3a8), 0x15, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov235_020cd6c4);
}
