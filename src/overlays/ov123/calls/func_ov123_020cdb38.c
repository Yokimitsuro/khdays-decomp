extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov123_020cdbf8(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct ov123b_LowByteFlags { unsigned bits : 8; };
struct vec3 { int a, b, c; };

void func_ov123_020cdb38(int *node) {
    int *state = (int *)node[1];
    state[9] = 0;
    state[10] = 0;
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x9c;
    *(unsigned short *)(*state + 0x1ae) &= ~3;
    ((struct ov123b_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits |= 1;
    *(struct vec3 *)(state + 0xb) = *(struct vec3 *)((int *)state[2]);
    func_ov107_020c5af8(*state, 0x115, 4, state[2]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov123_020cdbf8);
}
