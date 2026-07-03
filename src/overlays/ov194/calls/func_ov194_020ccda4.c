struct hw60 { unsigned short lo : 8, hi : 8; };
extern int func_ov107_020cab14(void *obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov194_020cce6c(void);

void func_ov194_020ccda4(int *node) {
    int a = node[0];
    int *state = (int *)node[1];
    int buf[3];
    int v = state[0xc] + *(int *)(a + 0x2c);
    state[0xc] = v;
    if (v < 0x6ee) return;
    {
        int r = func_ov107_020cab14(*state, 0);
        state[2] = r;
        if (r != 0) {
            int ang;
            VEC_Subtract((void *)(r + 0x74), (void *)state[0x10], buf);
            ang = func_020050b4(buf[0], buf[2]);
            state[4] = ang;
            state[3] = ang;
        }
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x82;
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov194_020cce6c);
}
