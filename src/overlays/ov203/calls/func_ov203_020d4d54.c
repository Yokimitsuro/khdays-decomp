/* ⚠ The `+ (v - v)` terms are deliberate and `v` is deliberately uninitialised: they are
 * the documented crack for func_02023eb4's copy artifact (`adds r0,r0,#0` when the result
 * is tested, `add r0,r0,#0` when it is stored). Both forms appear here, one of each.
 * The ternary is `!= 0 ? -1 : 1`, not `== 0 ? 1 : -1` -- the arm order decides which of
 * mvnne/moveq comes first. */
extern int  func_02023eb4();
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov203_020d4dd8(void);

void func_ov203_020d4d54(int *self) {
    int v;
    int *obj = (int *)self[1];

    obj[4] = *(int *)(self[0] + 0x2c) * 0x1e / 10;
    *(signed char *)((int)obj + 0x58) = func_02023eb4(2) + (v - v) != 0 ? -1 : 1;
    obj[0xe] = func_02023eb4(0x81) + (v - v);
    func_ov107_020c9264(*obj, 1, 1);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), &func_ov203_020d4dd8);
}
