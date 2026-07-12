/* Unless the predicate holds, kick anim 6, clear +0x28/+0x42/+0x40, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov245_020cce48(int);
extern int func_ov245_020ce448(int);
void func_ov245_020ce3f4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov245_020cce48(*(int *)owner) != 0) return;
    func_ov107_020c9264(*(int *)owner, 6, 0);
    *(int *)(owner + 0x28) = 0;
    *(signed char *)(owner + 0x42) = 0;
    *(signed char *)(owner + 0x40) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020ce448);
}
