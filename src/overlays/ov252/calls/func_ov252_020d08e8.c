/* Advance +0x54 by 0x3244, kick anim 0xd and the +0x574 sub-anim 0x12, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_ov107_020c9ee8(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov252_020d0940(int);
void func_ov252_020d08e8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x54) += 0x3244;
    func_ov107_020c9264(*(int *)owner, 0xd, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)owner + 0x574), 0x12, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov252_020d0940);
}
