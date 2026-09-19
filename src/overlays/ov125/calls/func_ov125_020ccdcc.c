/* Publish the landing pose: only while bit 0 of the hw60 low byte is set, send the anchor point
 * -- the vector at state[8] with y doubled from (y + 0xe00) -- to the render hook and latch the
 * pending action byte from +0x1c9 into +0x1c7.
 *
 * The anchor is built with the SDK's
 * `static inline VEC_Set`, not with three field assignments: the three arguments are three
 * adjacent loads that mwcc groups into one ldm, and the inline body is three separate stores.
 * Written as three field assignments the loads stay split. */
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
static inline void VEC_Set(struct vec3 *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

extern void func_ov107_020c5c54(int obj, struct vec3 *v);
extern void func_0203c634(int self, int idx, int cb);

void func_ov125_020ccdcc(int *self) {
    int *state = (int *)self[1];
    struct vec3 v;

    if ((((struct hw60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    { struct vec3 *p = (struct vec3 *)state[8];
      VEC_Set(&v, p->x, (p->y + 0xe00) * 2, p->z); }
    func_ov107_020c5c54(*state, &v);
    *(char *)(*state + 0x1c7) = *(signed char *)(*state + 0x1c9);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
