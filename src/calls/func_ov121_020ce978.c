extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov121_020cea5c(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct ov121_LowByteFlags { unsigned bits : 8; };

void func_ov121_020ce978(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct ov121_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    state[0x10] = 0;
    func_ov107_020c5af8(*state, 0x11a, 6, state[3]);
    func_ov107_020c5af8(*state, 0, 0x48, state[3]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov121_020cea5c);
}
