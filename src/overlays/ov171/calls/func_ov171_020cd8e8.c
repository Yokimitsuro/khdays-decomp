extern void func_ov107_020c9264();
extern int func_02023eb4(int bound);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov171_020cd958(void);
void func_ov171_020cd8e8(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 1, 1);
    state[0x18] = (func_02023eb4(2) == 0) ? -1 : 1;
    {
        int lo = *(int *)(*state + 0x224);
        int d = *(int *)(*state + 0x228) - lo;
        if (d < 0) d = -d;
        state[0x17] = lo + func_02023eb4(d + 1);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov171_020cd958);
}
