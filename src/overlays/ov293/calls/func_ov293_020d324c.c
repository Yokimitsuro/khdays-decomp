extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov293_020d32b8(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov293_020d324c(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 7, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x39c), 1, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov293_020d32b8);
}
