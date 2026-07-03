extern void func_ov107_020c9264();
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9ee8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov142_020d10dc(void);

void func_ov142_020d1058(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    func_ov107_020c9264(*state, 3, 0);
    {
        int p = state[0xe];
        if (p != 0) {
            int r;
            VEC_Subtract((void *)(p + 0x190), (void *)(*state + 0xb0), buf);
            r = func_020050b4(buf[0], buf[2]);
            state[3] = r;
            state[2] = r;
        }
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x3cc), 0, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov142_020d10dc);
}
