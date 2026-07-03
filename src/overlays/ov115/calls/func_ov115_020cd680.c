struct hw60 { unsigned short lo : 8, hi : 8; };
struct blk16 { int a, b, c, d; };
extern int func_ov107_020cab14(int a, int b);
extern void func_0203cd7c(int *out, int *m, int *a, int *b);
extern void func_0202ea48(int *dst, int *m);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *obj, int idx, void *value);
extern int data_02042264[];
extern void func_ov115_020cd758(void);
void func_ov115_020cd680(int *node) {
    int buf[9];
    int *obj = (int *)node[0];
    int *state = (int *)node[1];
    int t = state[0x12] + obj[0xb];
    state[0x12] = t;
    if (t < 0x6ee) return;
    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] != 0) {
        int *sub = (int *)state[2];
        func_0203cd7c(buf, (int *)(state[3] + 0x74), sub, data_02042264);
        func_0202ea48(state + 0x1d, buf);
        *(struct blk16 *)(state + 0x19) = *(struct blk16 *)(state + 0x1d);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x82;
    func_ov107_020c9264(*state, 0, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov115_020cd758);
}
