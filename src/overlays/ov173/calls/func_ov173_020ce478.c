extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *dst, void *src);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);

struct vec3 { int a, b, c; };
extern struct vec3 data_02041dc8;

void func_ov173_020ce478(int *node) {
    int *state = (int *)node[1];
    *(struct vec3 *)(state + 0xb) = data_02041dc8;
    if (state[4] != 0) {
        VEC_Subtract((void *)(*state + 0x74), (void *)(state[4] + 0x74), state + 0xb);
        state[0xc] = 0;
    }
    func_01ff8d18(state + 0xb, state + 0xb);
    func_01ffa724(0x800, state + 0xb, state + 0xb);
    func_ov107_020c9264(*state, 6, 0);
    func_ov107_020c5af8(*state, 0x141, 8, state[2]);
    state[0x16] = 0x6000;
    *(signed char *)(*state + 0x1c7) = 0xb;
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
