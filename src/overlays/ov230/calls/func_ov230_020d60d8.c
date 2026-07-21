/* If the "can retarget" hw60 bit 0 is set, roll a new random turn duration into node[4], enter the
 * turn state (1) and register the think callback. */
struct hw60 { unsigned short lo : 8, hi : 8; };
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, int cb);

void func_ov230_020d60d8(int param_1) {
    int *node = *(int **)(param_1 + 4);
    if ((((struct hw60 *)(*node + 0x60))->lo & 1) == 0) {
        return;
    }
    node[4] = func_02023eb4(0xc00);
    *(char *)(*node + 0x1c7) = 1;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
