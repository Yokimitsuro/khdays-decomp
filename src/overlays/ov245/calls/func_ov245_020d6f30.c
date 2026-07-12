/* Count the +0x40 timer up; past 0x3000 clear the child gate and dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov245_020d6f70(int);
void func_ov245_020d6f30(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    int t = *(int *)(owner + 0x40) + *(int *)(a + 0x2c);
    *(int *)(owner + 0x40) = t;
    if (t <= 0x3000) return;
    *(signed char *)(*(int *)(owner + 4) + 0xa8) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020d6f70);
}
