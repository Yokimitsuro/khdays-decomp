/* Wait out the wind-up, then re-acquire: once the timer passes 0x6ee, ask the target tracker for
 * a fresh target and, if there is one, face it with FX_Atan2 into both the current and the goal
 * heading. Either way, drop 0x82 from the hw60 high byte, stop the animation and continue.
 *
 * Matched byte-exact 2026-07-23, first compile. One of three byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern void *func_ov107_020cab14(void *obj, int a);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov153_020cd990(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov153_020cd8c4(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    VecFx32 d;
    int t;
    int h;

    t = state[7] + *(int *)((int)owner + 0x2c);
    state[7] = t;
    if (t < 0x6ee) {
        return;
    }
    state[6] = (int)func_ov107_020cab14((void *)state[0], 0);
    if (state[6] != 0) {
        VEC_Subtract((void *)(state[6] + 0x74), (void *)(state[0] + 0x74), &d);
        h = func_020050b4(d.x, d.z);
        state[5] = h;
        state[4] = h;
    }
    ((struct hw60 *)(state[0] + 0x60))->hi &= ~0x82;
    func_ov107_020c9264(state[0], 0, 0);
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov153_020cd990);
}
