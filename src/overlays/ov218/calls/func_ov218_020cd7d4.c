/* Aim entry: pose 2 plays; with the +0x64 flag reaction 0x135/7 fires at the +8 point; with a
 * +0x44 target the +0xc / +0x10 heading turns towards it. */
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int y);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov218_020cd868(void);

void func_ov218_020cd7d4(int *node) {
    int *state = (int *)node[1];
    int v[3];
    func_ov107_020c9264(*state, 2, 0);
    if (state[0x19] != 0) {
        func_ov107_020c5af8(*state, 0x135, 0x7, state[2]);
    }
    if (state[0x11] != 0) {
        int r;
        VEC_Subtract((void *)(state[0x11] + 0x190), (void *)(*state + 0xb0), v);
        r = func_020050b4(v[0], v[2]);
        state[4] = r;
        state[3] = r;
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov218_020cd868);
}
