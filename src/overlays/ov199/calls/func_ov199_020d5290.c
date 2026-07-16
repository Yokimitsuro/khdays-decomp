extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov199_020d5330(void);

struct ov147_LowByteFlags { unsigned bits : 8; };

void func_ov199_020d5290(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x46) << 0x18) >> 0x10);
    }

    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct ov147_LowByteFlags *)(*(int *)(*state + 0x38c) + 8))->bits &= ~1;
    func_ov107_020c5af8(*state, 0, 0x49, *state + 0x74);
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov199_020d5330);
}
