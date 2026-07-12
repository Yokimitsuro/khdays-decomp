/* Once 020cce48 clears, retarget the linked node, restart sub-anim 020c9ee8, drive +0x28 to
 * -0x4000, copy the parent's +8 into +0x30 and dispatch 020ce1cc. */
extern int func_ov245_020cce48(int);
extern int func_ov245_020d37b0(int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov245_020ce1cc(int);
void func_ov245_020ce15c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov245_020cce48(*(int *)owner) != 0) return;
    func_ov245_020d37b0(*(int *)(*(int *)owner + 0x434), *(int *)(owner + 0x24));
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x4c8), 0, 1);
    *(int *)(owner + 0x28) = -0x4000;
    *(int *)(owner + 0x30) = *(int *)(*(int *)(owner + 8) + 8);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020ce1cc);
}
