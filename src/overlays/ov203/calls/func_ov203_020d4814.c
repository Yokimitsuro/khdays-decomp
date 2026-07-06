extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov203_020d48e0(void);

struct ov203_Hw60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
};

struct ov203_LowByteFlags {
    unsigned bits : 8;
};

void func_ov203_020d4814(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    }

    ((struct ov203_Hw60 *)(*state + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct ov203_LowByteFlags *)(*(int *)(*state + 0x38c) + 8))->bits &= ~1;
    func_ov107_020c5af8(*state, 0, 0x48, state[15]);
    state[11] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov203_020d48e0);
}
