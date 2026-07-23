/* Publish the finish pose, but only while bit 0 of the hw60 low byte is set: reload the two
 * 16-byte parameter blocks (the canned one at data_020420f8 into state+0x18, then a copy of it
 * into state+8), send the anchor point -- the vector at state[0x11] with y raised by 0xa00 --
 * to the render hook, latch the pending action byte from +0x1c9 into +0x1c7 and hand off.
 *
 * Matched byte-exact 2026-07-23. The anchor is built with the SDK's `static inline VEC_Set`,
 * not with a struct copy: the three arguments are three adjacent loads that mwcc groups into
 * one ldm, and the inline body is three separate stores. Any "copy three words and bump one"
 * spelling emits ldm+stm and then re-loads the middle word.
 *
 * One of four byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { int a, b, c, d; } Ov187Quad;

extern Ov187Quad data_020420f8;
static inline void VEC_Set(VecFx32 *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

extern void func_ov107_020c5c54(int obj, VecFx32 *v);
extern void func_0203c634(void *node, int idx, void *cb);

struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov187_020d5f2c(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;

    if ((((struct hw60 *)(state[0] + 0x60))->lo & 1) == 0) {
        return;
    }
    *(Ov187Quad *)(state + 6) = data_020420f8;
    *(Ov187Quad *)(state + 2) = *(Ov187Quad *)(state + 6);
    { VecFx32 *p = (VecFx32 *)state[0x11];
      VEC_Set(&v, p->x, p->y + 0xa00, p->z); }
    func_ov107_020c5c54(state[0], &v);
    *(char *)(state[0] + 0x1c7) = *(signed char *)(state[0] + 0x1c9);
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
