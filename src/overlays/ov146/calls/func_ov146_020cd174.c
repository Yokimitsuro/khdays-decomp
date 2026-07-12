/* Kick anim (1 if +0x58 set else 7, phase 1), then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cd1b4(int);
void func_ov146_020cd174(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, *(int *)(owner + 0x58) != 0 ? 1 : 7, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cd1b4);
}
