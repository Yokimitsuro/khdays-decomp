/* Kick anim 0, clear the child bit, arm the 020c5af8 timer, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cf430(int);
void func_ov146_020cf3d4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0, 0);
    *(int *)(*(int *)(owner + 8) + 0x5c) &= ~2;
    func_ov107_020c5af8(*(int *)owner, 0x125, 7, *(int *)(owner + 4) + 0xb0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cf430);
}
