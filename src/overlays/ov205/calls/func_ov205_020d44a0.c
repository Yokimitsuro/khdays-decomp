extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov205_020d456c(void);

struct ov205_Hw60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
};

struct ov205_LowByteFlags {
    unsigned bits : 8;
};

void func_ov205_020d44a0(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    }

    ((struct ov205_Hw60 *)(*state + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct ov205_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    func_ov107_020c5af8(*state, 0, 0x48, state[9]);
    state[11] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov205_020d456c);
}
