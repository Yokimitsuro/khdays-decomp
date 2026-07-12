/* Kick anim (0, phase 1), latch +0x3ec, then dispatch via c634. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d2aec(int);
void func_ov253_020d2aac(int param_1) {
    int owner = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)owner, 0, 1);
    *(int *)(*(int *)owner + 0x3ec) = 0x1e000;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d2aec);
}
