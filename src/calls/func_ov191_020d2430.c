extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov191_020d2518(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct ov191_LowByteFlags { unsigned bits : 8; };
struct vec3 { int a, b, c; };

void func_ov191_020d2430(int *node) {
    int *state = (int *)node[1];
    state[0x10] = 0;
    state[9] = 0;
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x9c;
    ((struct ov191_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits |= 1;
    *(struct vec3 *)(state + 5) = *(struct vec3 *)(*state + 0x394);
    func_01ffa724(0x500, state + 5, state + 2);
    state[8] = 0x500;
    func_ov107_020c5af8(*state, 0x133, 4, state[1]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov191_020d2518);
}
