/* Unless the child is busy, kick anim (5, phase 1), clear +0x3c and dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov146_020cdbf8(int);
void func_ov146_020cdbac(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    func_ov107_020c9264(*(int *)owner, 5, 1);
    *(int *)(owner + 0x3c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov146_020cdbf8);
}
