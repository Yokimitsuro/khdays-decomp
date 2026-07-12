/* Tick the +0x14 timer down, spawn the child; once present and expired mark state 0xa. */
extern int func_0203c634(int, int, void *);
extern int func_ov107_020cab14(int, int);
void func_ov236_020d4438(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x14) = *(int *)(owner + 0x14) - *(int *)(a + 0x2c);
    int child = func_ov107_020cab14(*(int *)owner, 0);
    *(int *)(owner + 4) = child;
    if (child == 0) return;
    if (*(int *)(owner + 0x14) > 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 0xa;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
