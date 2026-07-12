/* Reset +0x48/+0x81, kick anim (1, phase 1), set +0x5c=0x900, clear +0x74, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov283_020cd5a8(int);
void func_ov283_020cd558(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x48) = 0;
    *(signed char *)(owner + 0x81) = 0;
    func_ov107_020c9264(*(int *)owner, 1, 1);
    *(int *)(owner + 0x5c) = 0x900;
    *(int *)(owner + 0x74) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov283_020cd5a8);
}
