extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov176_020d2484(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct ov176_LowByteFlags { unsigned bits : 8; };
struct vec3 { int a, b, c; };

void func_ov176_020d23a8(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c5af8(*state, 0x142, 5, state[1]);
    state[8] = 0;
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x8c;
    ((struct ov176_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits |= 1;
    *(struct vec3 *)(state + 5) = *(struct vec3 *)(*state + 0x390);
    func_01ffa724(0x600, state + 5, state + 2);
    func_0203c634(node, *(signed char *)(node + 8), func_ov176_020d2484);
}
