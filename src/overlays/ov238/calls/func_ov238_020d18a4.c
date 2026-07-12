/* Reset +0x24/+0x2f; kick the base anim or the stepped anim depending on +0x20, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov238_020d190c(int);
void func_ov238_020d18a4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x24) = 0;
    *(signed char *)(owner + 0x2f) = 0;
    if (*(int *)(owner + 0x20) == 0) {
        func_ov107_020c9264(*(int *)owner, 4, 0);
    } else {
        func_ov107_020c9264(*(int *)owner, *(unsigned char *)(owner + 0x2d) + 8, 0);
        *(unsigned char *)(owner + 0x2d) += 1;
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov238_020d190c);
}
