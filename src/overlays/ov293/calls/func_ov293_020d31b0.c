struct v3 { int x, y, z; };
struct bit0 { unsigned char b : 1; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov293_020d3210(void);

void func_ov293_020d31b0(int *node) {
    int *state = (int *)node[1];
    state[0xb] -= 0x100;
    *(struct v3 *)((char *)state + 0x1c) = *(struct v3 *)((char *)state + 0x28);
    if (!((struct bit0 *)(*state + 0x17a))->b) return;
    func_ov107_020c9264(*state, 6, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov293_020d3210);
}
