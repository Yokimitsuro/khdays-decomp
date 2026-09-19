/* Publish the finish pose, but only while bit 0 of the hw60 low byte is set: send the anchor
 * point -- the vector at state[1] with y raised by 0x1999 -- to the render hook, reload the two
 * 16-byte parameter blocks (the canned one at data_020420f8 into state+0x38, then a copy of it
 * into state+0x28), latch the pending action byte from +0x1c9 into +0x1c7 and hand off. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { int a, b, c, d; } Ov213Quad;

extern Ov213Quad data_020420f8;
static inline void VEC_Set(VecFx32 *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

extern void func_ov107_020c5c54(int obj, VecFx32 *v);
extern void func_0203c634(void *node, int idx, void *cb);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov273_020d1314(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;

    if ((((struct hw60 *)(state[0] + 0x60))->lo & 1) == 0) {
        return;
    }
    { VecFx32 *p = (VecFx32 *)state[1];
      VEC_Set(&v, p->x, p->y + 0x1999, p->z); }
    func_ov107_020c5c54(state[0], &v);
    *(Ov213Quad *)(state + 0xe) = data_020420f8;
    *(Ov213Quad *)(state + 0xa) = *(Ov213Quad *)(state + 0xe);
    *(char *)(state[0] + 0x1c7) = *(signed char *)(state[0] + 0x100 + 0xc9);
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
