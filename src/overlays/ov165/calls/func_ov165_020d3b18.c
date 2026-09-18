/* Bounce tick of the ov163 enemy (x3: ov163/164/165): when the actor's +0x3cc bit 0 is set the
 * state ends with sub-state 8; otherwise the +0x30 timer runs and, while the +0x17a bit-1 flag
 * is set and the timer has passed two frames, the +0x3c heading is reflected against the
 * actor's +0x114 surface normal (v - 2 (v.n) n on the reversed heading), re-normalised and the
 * +0x40/+0x30 counters cleared; the +0x18 velocity is the heading scaled by the +0x38 speed,
 * which then decays to 0x7c6/2000 of itself. */
typedef struct { int x, y, z; } Vec3;
struct Bit0 { int b0 : 1; };
struct Flags17a { unsigned char b0 : 1, b1 : 1; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);

void func_ov165_020d3b18(int *node)
{
    int actor;
    int *state = (int *)node[1];
    Vec3 back;
    Vec3 reflected;

    if (((struct Bit0 *)(*state + 0x3cc))->b0) {
        *(unsigned char *)(*state + 0x1c7) = 8;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0xc] += *(int *)(*node + 0x2c);
    actor = *state;
    if (((struct Flags17a *)(actor + 0x17a))->b1 && state[0xc] >= *(int *)(*node + 0x2c) * 2) {
        func_01ffa724(-0x1000, (Vec3 *)(state + 0xf), &back);
        func_01ffa724(VEC_DotProduct(&back, (Vec3 *)(actor + 0x114)) << 1, (Vec3 *)(actor + 0x114), &reflected);
        VEC_Subtract(&reflected, &back, &reflected);
        func_01ff8d18(&reflected, (Vec3 *)(state + 0xf));
        state[0x10] = 0;
        state[0xc] = 0;
    }
    func_01ffa724(state[0xe], (Vec3 *)(state + 0xf), (Vec3 *)(state + 6));
    state[0xe] = state[0xe] * 0x7c6 / 2000;
}
