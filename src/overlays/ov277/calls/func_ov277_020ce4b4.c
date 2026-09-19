/* Leap entry: clears bit 1 of the owner's +0x5c, binds its channels 0 / 2 / 4 / 1 with (0, 0)
 * and re-inits it; the +8 rate is (600.0 - the +0xc actor's +0x384 item's 0203be68 height) x
 * 30 x frame step, the +4 timer and +0x10 latch clear and the node moves to 020ce5a8. */
static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}
extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c7ac(int obj, int a);
extern int func_0203be68(int item, int a, int b);
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov277_020ce5b0(void);

void func_ov277_020ce4b4(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int step;
    *(int *)(node[0] + 0x5c) &= ~2;
    func_0203b9fc(node[0], 0, 0, 0);
    func_0203b9fc(node[0], 2, 0, 0);
    func_0203b9fc(node[0], 4, 0, 0);
    func_0203b9fc(node[0], 1, 0, 0);
    func_0203c7ac(node[0], 0);
    step = *(int *)(*(int *)param_1 + 0x2c) * 30;
    node[2] = FX_Mul(0x1770000 - func_0203be68(*(int *)(node[3] + 0x384), 0, 0), step);
    node[1] = 0;
    *((unsigned char *)node + 0x10) = 0;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov277_020ce5b0);
}
