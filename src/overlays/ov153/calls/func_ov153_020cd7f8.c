extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov153_020cd8c4(void);

struct ov153_Hw60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
};

struct ov153_LowByteFlags {
    unsigned bits : 8;
};

void func_ov153_020cd7f8(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    }

    ((struct ov153_Hw60 *)(*state + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct ov153_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    func_ov107_020c5af8(*state, 0, 0x48, state[2]);
    state[7] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov153_020cd8c4);
}
