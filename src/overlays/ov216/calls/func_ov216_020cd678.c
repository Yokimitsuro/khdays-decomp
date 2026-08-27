extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov216_020cd70c(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov216_020cd678(int *node) {
    int *state = (int *)node[1];
    int t = state[0x14] + *(int *)(*node + 0x2c);
    state[0x14] = t;
    if (t < 0x6ee) return;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    func_ov107_020c9264(*state, 0, 0);
    func_ov107_020c5af8(*state, 0x144, 4, state[4]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov216_020cd70c);
}
