/* Idle entry: plays pose 0 (looping), rolls a random turn direction into +0x18, sets the
 * +0x48 rate to 30/10 of the frame step and, if the +0x6c wait is spent, re-rolls it between
 * the actor's +0x224/+0x228 bounds; then moves the node to 020cdde4. */
extern void func_ov107_020c9264(int owner, int a, int b);
extern int func_02023eb4();  /* K&R decl: needed for the rand `+ (v - v)` copy artifact */
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov213_020cdde4(void);
void func_ov213_020cdd40(int *node) {
    int *state = (int *)node[1];
    int v;
    func_ov107_020c9264(*state, 0, 1);
    /* +(v-v) forces `adds r0,r0,#0` (rand result copied+tested); +0 would fold away */
    state[6] = (func_02023eb4(2) + (v - v)) != 0 ? -1 : 1;
    state[0x12] = *(int *)(node[0] + 0x2c) * 30 / 10;
    if (state[0x1b] <= 0) {
        int lo = *(int *)(*state + 0x224);
        int d = *(int *)(*state + 0x228) - lo;
        if (d < 0) d = -d;
        state[0x1b] = lo + func_02023eb4(d + 1);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov213_020cdde4);
}
