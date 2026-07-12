/* Unless busy, arm the 020c5af8 timer, run 020ce36c, kick anim (7, phase 1), then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov212_020ce36c(int);
extern int func_ov212_020cf630(int);
void func_ov212_020cf5d0(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c5af8(*(int *)owner, 0x128, 0xb, *(int *)(owner + 8));
    func_ov212_020ce36c(owner);
    func_ov107_020c9264(*(int *)owner, 7, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov212_020cf630);
}
