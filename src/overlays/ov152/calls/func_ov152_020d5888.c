extern void func_ov107_020c9264();
extern int func_02023eb4(int bound);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov152_020d5908(void);
void func_ov152_020d5888(int *node) {
    int *state = (int *)node[1];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[4] = v / 5;
    }
    func_ov107_020c9264(*state, 1, 1);
    {
        int lo = *(int *)(*state + 0x224);
        int diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) diff = -diff;
        state[0xd] = lo + func_02023eb4(diff + 1);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov152_020d5908);
}
