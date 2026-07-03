struct m1 { int m[4]; };
struct v3 { int a, b, c; };
extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(void *dst, void *m, int v);
extern void func_0203c9d0(void *dst, void *m);
extern int data_02042264[];
extern int data_02041dc8[];

void func_ov215_020d1018(int *node) {
    int a = node[0];
    int *state = (int *)node[1];
    struct m1 buf;
    state[0x11] = func_0203d040(state[0x11], state[0x13], *(int *)(a + 0x2c) * 3, 0);
    func_0202f188(&buf, data_02042264, state[0x11]);
    func_0203c9d0((void *)(*state + 0xa0), &buf);
    {
        struct v3 *src = (struct v3 *)(state + 8);
        *(struct v3 *)(*state + 0xf0) = *src;
        *(struct v3 *)(state + 0xb) = *src;
        *src = *(struct v3 *)data_02041dc8;
    }
    if (state[0x15] != 0) {
        if (state[0x15] >= 0x23000) {
            signed char sub = *(signed char *)(*state + 0x1c6);
            if (sub == 2 || sub == 4) {
                *(signed char *)(*state + 0x1c7) = 5;
                state[0x15] = 0;
            }
        } else {
            state[0x15] += *(int *)(node[0] + 0x2c);
        }
    }
}
