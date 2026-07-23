/* Re-aim the strafe: ask the target tracker for the turn rate, rebuild the local direction
 * from the object's own frame, and slew towards it. Once the busy byte at state[0x12] clears,
 * switch to animation 9, clear the counter at state[0x10], drop the 0x40 bit of the hw60 high
 * byte and hand off to the next step.
 *
 * Matched byte-exact 2026-07-23, first compile. One of three byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern int func_ov107_020c9f48(int a, VecFx32 *out);
extern void func_0202f384(void *dst, void *src, VecFx32 *v);
extern void func_01ffa724(int a, void *b, void *c);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov121_020cfad0(void);

void func_ov121_020cfa14(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;
    int n;

    n = func_ov107_020c9f48(*(int *)(state[0] + 0x3a0), &v);
    func_0202f384(state + 7, (void *)(state[0] + 0xa0), &v);
    func_01ffa724(n, state + 7, state + 7);
    if (*(unsigned char *)state[0x12] != 0) {
        return;
    }
    func_ov107_020c9264(state[0], 9, 1);
    state[0x10] = 0;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw60 << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov121_020cfad0);
}
