/* func_ov240_020cf6e0: ported from a matched sibling family (same shape, constants and offsets adjusted). */
extern void func_ov107_020c9264();
extern void VEC_Subtract();
extern int func_020050b4();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov240_020cf74c(void);
void func_ov240_020cf6e0(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 0x3, 0);
    if (state[0x10] != 0) {
        int buf[3];
        int a;
        VEC_Subtract(state[0x10] + 0x190, state[2], buf);
        a = func_020050b4(buf[0], buf[2]);
        state[4] = a;
        state[3] = a;
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov240_020cf74c);
}
