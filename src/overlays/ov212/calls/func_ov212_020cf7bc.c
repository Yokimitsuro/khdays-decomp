/* Ease the +0x57c value toward 0; once within threshold run 020ce404, kick anim 8 and dispatch. */
extern int func_ov212_020ce404(int);
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov212_020cf830(int);
void func_ov212_020cf7bc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int v = *(int *)(*(int *)owner + 0x57c);
    *(int *)(*(int *)owner + 0x57c) = v + (-v * 0x180) / 0x1000;
    if (*(int *)(*(int *)owner + 0x57c) > 0x1b3) return;
    func_ov212_020ce404(owner);
    func_ov107_020c9264(*(int *)owner, 8, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020cf830);
}
