/* Place a trailing marker in world space (x4: ov049 + 3 twins). Only while bit 0 of the
 * actor's +0x694 flags is set, and only for message kinds 2..5. Take the emitter's base
 * point (ov022_020ad44c) and, unless the message already carries a fixed offset (+0x118),
 * offset it by the constant local vector {-0x6f, 0x1768, 0x29} rotated by the actor's
 * heading. Publish the heading at msg+0x80, raise flag 0x20 and hand the world point in at
 * msg+0xa8.
 *
 * ★ `biased` is the load-bearing spelling and it is also the honest one. The heading is
 * stored as a signed-ish halfword but the sin/cos table is indexed by an UNSIGNED 16-bit
 * angle, so the code works in the biased domain throughout: it converts once, before the
 * call, keeps that, and reconstructs the original for the store with `+ 0x8000`. Reading
 * the raw angle and biasing it later where it is used is one instruction SHORT -- and it
 * hides what the 0x8000 is for. (The two are identical mod 65536, which is why either
 * compiles at all.)
 *
 * The rotation feeds MTX_RotY33_ with NEGATED sin and cos, i.e. it rotates by -heading:
 * the offset is expressed in the actor's local frame and is being brought into world.
 *
 * Case order from tools/switchorder.py: {2,3,4,5} share one body, {0,1} share the
 * default's -- only the first group is written. */
struct vec3 { int x, y, z; };
struct b1 { unsigned char b0 : 1; };

extern void func_ov022_020ad44c(struct vec3 *out, int self);
extern void MTX_RotY33_(int *m, int s, int c);
extern void MTX_MultVec33(struct vec3 *v, int *m, struct vec3 *out);
extern void VEC_Add(struct vec3 *a, struct vec3 *b, struct vec3 *out);
extern void func_0202aa9c(void *p);
extern short data_0203d210[];

void func_ov087_020b8ce0(int self, signed char *msg) {
    struct vec3 out;
    struct vec3 v;
    int m[9];
    unsigned short biased;
    unsigned int idx;

    if (((struct b1 *)(self + 0x694))->b0 == 0) {
        return;
    }
    switch (*msg) {
    case 2:
    case 3:
    case 4:
    case 5:
        biased = *(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000;
        func_ov022_020ad44c(&out, self);
        if (*(int *)(msg + 0x118) == 0) {
            idx = biased >> 4;
            v.x = -0x6f;
            v.y = 0x1768;
            v.z = 0x29;
            MTX_RotY33_(m, -data_0203d210[idx * 2], -data_0203d210[idx * 2 + 1]);
            MTX_MultVec33(&v, m, &v);
            VEC_Add(&out, &v, &out);
        }
        *(unsigned short *)(msg + 0x80) = biased + 0x8000;
        *(unsigned short *)(msg + 4) |= 0x20;
        *(struct vec3 *)(msg + 0xa8) = out;
        func_0202aa9c(msg + 4);
        break;
    }
}
