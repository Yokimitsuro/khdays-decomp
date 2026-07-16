extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov199_020d5270(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct ov197b_LowByteFlags { unsigned bits : 8; };

void func_ov199_020d51ac(int *node) {
    int *state = (int *)node[1];
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(unsigned short *)(*state + 0x1ae) |= 3;
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    }
    ((struct ov197b_LowByteFlags *)(*(int *)(*state + 0x38c) + 8))->bits &= ~1;
    func_ov107_020c5af8(*state, 0, 0x4b, *state + 0x74);
    func_0203c634(node, *(signed char *)(node + 8), func_ov199_020d5270);
}
