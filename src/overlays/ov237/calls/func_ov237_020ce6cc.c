/* Kick the primary anim 1 and the +0x3d8 sub-anim 0, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov237_020ce714(int);
void func_ov237_020ce6cc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 1, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x3d8), 0, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov237_020ce714);
}
