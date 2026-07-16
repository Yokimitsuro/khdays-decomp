extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov277_020d23a4(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByteFlags { unsigned bits : 8; };

void func_ov277_020d2330(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0xce) << 0x18) >> 0x10);
    }
    ((struct LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    *(int *)(*state + 0x390) = 1;
    func_0203c634(node, *(signed char *)(node + 8), func_ov277_020d23a4);
}
