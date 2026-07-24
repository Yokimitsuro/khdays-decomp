/*
 * Enter the "advance" phase: kick animation mode 6, convert a fresh atan2 (func_02023f08) to a
 * sin/cos facing in node[5..7], copy the constant offset vector data_02041dc8 and publish it to the
 * owner via modes 2 and 4, clear the one-shot bytes and phase timers, seed the reach at +0x5c to
 * 0x5000, and chain to the next state func_ov216_020cdf28.
 *
 * `const short data_0203d210[]` is load-bearing: without const mwcc must assume the node stores
 * could write the sin/cos table, which reorders a table load; const is the aliasing fact that
 * matches. One of a 5-member family (family); only the chained-state symbol differs.
 */
struct Vec3 { int x, y, z; };
extern void func_ov107_020c9264(int owner, int mode, int b);
extern int func_02023f08(void);
extern const short data_0203d210[];
extern struct Vec3 data_02041dc8;
extern void func_ov107_020c0b90(int owner, int mode, struct Vec3 v, int c);
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov216_020cdf28(void);

void func_ov216_020cdde8(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int idx;
    struct Vec3 v;
    func_ov107_020c9264(*node, 6, 0);
    idx = (int)(((unsigned)(((long long)func_02023f08() * 0x28be60db9391LL + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    node[5] = data_0203d210[idx * 2];
    node[6] = 0;
    node[7] = data_0203d210[idx * 2 + 1];
    v = data_02041dc8;
    func_ov107_020c0b90(*node, 2, v, 0);
    func_ov107_020c0b90(*node, 4, v, 0);
    *(char *)((char *)node + 0x70) = 0;
    *(char *)((char *)node + 0x71) = 0;
    *(char *)((char *)node + 0x73) = 0;
    *(char *)((char *)node + 0x6e) = 0;
    *(char *)((char *)node + 0x6f) = func_02023eb4(0xb) + 0x14;
    *(char *)((char *)node + 0x74) = 0;
    *(int *)((char *)node + 0x58) = 0;
    *(int *)((char *)node + 0x78) = 0;
    *(int *)((char *)node + 0x5c) = 0x5000;
    *(int *)((char *)node + 0x60) = 0;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov216_020cdf28);
}
