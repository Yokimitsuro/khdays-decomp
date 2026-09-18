/* Walk tick of the ov241 enemy (x3: ov241/242/243): the +0x40 latch flips to 1 with reaction
 * 0x13a/4 at the +0xc position once the +0x384 item's animation passes 22.0, and back to 0 when
 * it drops under it. The +0x390 resource's forward vector (scaled speed) is rotated by the
 * actor's +0xa0 placement; the offset from the +0xc position to the +0x1c waypoint gives the +8
 * heading and, normalised, the walk: the step (+0x10) is the forward vector scaled by
 * min(1.5 x speed, dist / 2) times the (clamped) dot with the offset; +0x28 is 30 x dt / 25.
 * Arriving inside the actor's +0x80 radius requests sub-state 2 and releases the slot. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203bec0(int item, int a);
extern void func_ov107_020c5af8(int actor, int id, int mode, void *anchor);
extern int func_ov107_020c9f48(int resource, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int node, int slot, void *cb);

void func_ov243_020d4504(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 d;
    Vec3 fwd;
    int dist;
    int limit;
    int dot;
    int speed;

    if (*(unsigned char *)(state + 0x10) == 0) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x8000) {
            func_ov107_020c5af8(*state, 0x13b, 4, (void *)state[3]);
            *(unsigned char *)(state + 0x10) = 1;
        }
    } else if (*(unsigned char *)(state + 0x10) == 1) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x12000) {
            func_ov107_020c5af8(*state, 0x13b, 5, (void *)state[3]);
            *(unsigned char *)(state + 0x10) = 2;
        }
    } else if (*(unsigned char *)(state + 0x10) == 2) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) < 0x12000) {
            *(unsigned char *)(state + 0x10) = 0;
        }
    }
    speed = func_ov107_020c9f48(*(int *)(*state + 0x390), &fwd);
    limit = (int)(((long long)speed * 0x1800 + 0x800) >> 12);
    func_0202f384(&fwd, (void *)(*state + 0xa0), &fwd);
    VEC_Subtract((Vec3 *)state[7], (Vec3 *)state[3], &d);
    dist = func_01ff8d18(&d, &d);
    if (dist < limit) {
        limit = dist >> 1;
    }
    state[2] = func_020050b4(d.x, d.z);
    dot = VEC_DotProduct(&d, &fwd);
    if (dot < 0) {
        dot = 0;
    }
    func_01ffa724((int)(((long long)limit * dot + 0x800) >> 12), &fwd, (Vec3 *)(state + 4));
    state[0xa] = *(int *)(*(int *)node + 0x2c) * 30 / 25;
    if (dist > *(int *)(*state + 0x80)) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
