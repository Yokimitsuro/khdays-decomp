extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *value);

struct ov155_Hw60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
};

struct ov155_LowByteFlags {
    unsigned bits : 8;
};

void func_ov155_020d5518(int *node) {
    int *state = (int *)node[1];
    ((struct ov155_Hw60 *)(*state + 0x60))->hi &= ~1;

    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    }

    *(unsigned short *)(*state + 0x1ae) |= 3;
    ((struct ov155_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    func_ov107_020c5af8(*state, 0, 0x4b, state[2]);
    *(signed char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
