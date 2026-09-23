/* Hop tick of the ov260 actor: once the partner holds no queued move pose 0x1a plays, its +0x428
 * part takes motion 0xf, it turns to the +0x420 target (+0x64 / +0x68 heading) and the +0x2c velocity
 * becomes the flat direction to it at half the distance in body radii (capped at 1.0) with a 0.5 lift;
 * +0x70 and the +0x7b flag clear and the node moves on to 020cf2d4. Until then the +0x70 timer runs
 * and the cue fires once at 0xcc0 (020cd04c 2). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int y);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov260_020cd04c(int actor, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cf2d4(void);

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov260_020cf17c(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    if (*(u8 *)(state[1] + 0xad) == 0) {
        int t;

        func_ov107_020c9264(*state, 0x1a, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x428), 0xf, 0);
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x420) + 0x190), (Vec3 *)state[4], &d);
        state[0x19] = state[0x1a] = func_020050b4(d.x, d.z);
        d.y = 0;
        t = FX_Inv(func_01ff8d18(&d, &d), *(int *)(*state + 0x80));
        if (t > 0x1000) {
            t = 0x1000;
        }
        func_01ffa724(FX_MUL(t, 0x800), &d, &d);
        VecSet((Vec3 *)(state + 0xb), d.x, 0x800, d.z);
        state[0x1c] = 0;
        *((u8 *)state + 0x7b) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf2d4);
    } else {
        state[0x1c] += *(int *)(node[0] + 0x2c);
        if ((*((u8 *)state + 0x7b) & 1) == 0 && state[0x1c] >= 0xcc0) {
            *((u8 *)state + 0x7b) |= 1;
            func_ov260_020cd04c(*state, 2);
        }
    }
}
