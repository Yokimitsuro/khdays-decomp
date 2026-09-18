/* func_ov173_020cd200: ported from the matched ov166 sibling (same enemy family, constants adjusted). */
extern void func_ov107_020c9264();
extern int func_02023eb4(int bound);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov173_020cd28c(void);
void func_ov173_020cd200(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 1, 1);
    state[0x18] = (func_02023eb4(2) == 0) ? -1 : 1;
    state[0x13] = func_02023eb4(0x100);
    {
        int lo = *(int *)(*state + 0x224);
        int d = *(int *)(*state + 0x228) - lo;
        if (d < 0) d = -d;
        state[0x17] = lo + func_02023eb4(d + 1);
    }
    state[0x15] = func_02023eb4(0x15) + 0x14;
    func_0203c634(node, *(signed char *)(node + 8), func_ov173_020cd28c);
}
