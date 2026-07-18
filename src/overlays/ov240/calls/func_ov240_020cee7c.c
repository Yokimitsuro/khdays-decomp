extern void func_ov107_020c9264();
extern void func_ov240_020ce8d4();
extern int func_02023eb4(int);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov240_020ceee0(void);

void func_ov240_020cee7c(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 2, 1);
    func_ov240_020ce8d4(*state, 0);
    {
        int lo = *(int *)(*state + 0x224);
        int hi = *(int *)(*state + 0x228);
        int d = hi - lo;
        if (d < 0) d = -d;
        state[0xe] = lo + func_02023eb4(d + 1);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov240_020ceee0);
}
