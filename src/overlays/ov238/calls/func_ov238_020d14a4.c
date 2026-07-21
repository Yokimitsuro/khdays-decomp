/* Enter the taunt: unless a queued cancel is pending (node[0xd], which it consumes), cancel the
 * current action (mode 0xe), play the taunt sub-animation (func_ov107_020c9ee8 on *node+0x3e0),
 * and seed a random taunt duration (3 + d1) at +0x2d; then register the think callback. */
extern void func_ov107_020c9264(int owner, int mode, int b);
extern void func_ov107_020c9ee8(int obj, int a, int b);
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov238_020d1510(void);

void func_ov238_020d14a4(int param_1) {
    int *node = *(int **)(param_1 + 4);
    if (node[0xd] == 0) {
        func_ov107_020c9264(*node, 0xe, 0);
        func_ov107_020c9ee8(*(int *)(*node + 0x3e0), 4, 0);
        *(char *)((char *)node + 0x2d) = func_02023eb4(2) + 3;
    } else {
        node[0xd] = 0;
    }
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov238_020d1510);
}
