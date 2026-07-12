/* Unless the predicate holds, advance the +0x28 timer; past 0x1000 run 020cce28 and dispatch. */
extern int func_0203c634(int, int, void *);
extern int func_ov245_020cce48(int);
extern int func_ov245_020cce28(int);
extern int func_ov245_020cdf00(int);
void func_ov245_020ce0d8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov245_020cce48(*(int *)owner) != 0) return;
    int t = *(int *)(owner + 0x28) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(owner + 0x28) = t;
    if (t < 0x1000) return;
    func_ov245_020cce28(*(int *)owner);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020cdf00);
}
