/* Scale the tick into +0x18, kick anim (2, phase 1), clear +0x40, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov245_020d64ac(int);
void func_ov245_020d6448(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x18) = *(int *)(*(int *)param_1 + 0x2c) * 30 / 10;
    func_ov107_020c9264(*(int *)owner, 2, 1);
    *(int *)(owner + 0x40) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020d64ac);
}
