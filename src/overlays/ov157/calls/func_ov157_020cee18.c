extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(void *dst, void *m, int v);
extern void func_0202ed60(void *dst, void *m, int v);
extern void func_0202ef54(void *dst, void *a, void *b);
extern void func_0203c9d0(void *dst, void *m);
extern int data_02042264[];

void func_ov157_020cee18(int *node) {
    int *state = (int *)node[1];
    struct { int mtx0[4], mtx1[4]; } f;
    if ((*(unsigned char *)(*state + 0x1c4) & 2) == 0) {
        state[4] = func_0203d040(state[4], state[5], state[0xc], 0);
    }
    func_0202f188(f.mtx0, data_02042264, state[4]);
    func_0202ed60(f.mtx1, data_02042264, *state + 0x124);
    func_0202ef54(f.mtx1, f.mtx1, f.mtx0);
    func_0203c9d0((void *)(*state + 0xa0), f.mtx1);
    if (state[0xd] < 0) return;
    state[0xd] = state[0xd] - *(int *)(node[0] + 0x2c);
}
