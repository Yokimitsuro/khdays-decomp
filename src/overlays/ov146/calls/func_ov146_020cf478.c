/* Kick anim 2, clear bit 1 of the child's +0x5c flags, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cf4bc(int);
void func_ov146_020cf478(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 2, 0);
    *(int *)(*(int *)(owner + 8) + 0x5c) &= ~2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cf4bc);
}
