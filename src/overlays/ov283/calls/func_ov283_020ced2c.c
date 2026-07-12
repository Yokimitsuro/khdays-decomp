/* Kick anim (0, phase 1), set +0x5c/+0x48, clear +0x78, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov283_020ced7c(int);
void func_ov283_020ced2c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0, 1);
    *(int *)(owner + 0x5c) = 0x900;
    *(int *)(owner + 0x48) = 0x27d8;
    *(int *)(owner + 0x78) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov283_020ced7c);
}
