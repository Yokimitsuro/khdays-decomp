extern void func_ov107_020c9264();
extern int func_02023eb4(int bound);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov136_020d2880(void);
void func_ov136_020d2800(int *node) {
    int *state = (int *)node[1];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[5] = v / 5;
    }
    func_ov107_020c9264(*state, 1, 1);
    {
        int lo = *(int *)(*state + 0x224);
        int diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) diff = -diff;
        state[0xc] = lo + func_02023eb4(diff + 1);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov136_020d2880);
}
