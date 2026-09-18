/* Approach tick of the ov291 enemy: the +0x394 part's motion step gives the speed and, rotated
 * by the actor's +0xa0 orientation, the forward vector; the +0x28 phase fires reaction 0x16f
 * mode 4 once the +0x384 item's animation passes 0x4000, mode 5 past 0x15000 and resets below
 * it. The +0x3a0 waypoint selected by +0x24 (16 bytes each, +0x10) minus the +0xc position gives
 * the +8 heading and the distance, which halves the speed when shorter; the +0x10 velocity is
 * the forward vector at half the speed scaled by the (clamped) alignment, +0x1c clears and,
 * once the +0x20 busy byte clears, animation 3 plays, the part runs action 2, the phase resets
 * and the tick hands off to cd2d0. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203bec0(int item, int a);
extern void func_ov107_020c5af8(int actor, int id, int mode, void *anchor);
extern int func_ov107_020c9f48(int resource, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c9ee8(void *part, int a, int b);
extern void func_ov291_020cd2d0(void);
extern int func_020050b4(int x, int z);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int node, int slot, void *cb);

void func_ov291_020cd100(int node)
{
    int *state = *(int **)(node + 4);
    Vec3 fwd;
    Vec3 at;
    Vec3 d;
    int dist;
    int limit;
    int dot;
    int speed;

    speed = func_ov107_020c9f48(*(int *)(*state + 0x394), &fwd);
    func_0202f384(&fwd, (void *)(*state + 0xa0), &fwd);
    if (*(unsigned char *)(state + 0xa) == 0) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x4000) {
            func_ov107_020c5af8(*state, 0x16f, 4, (void *)state[3]);
            *(unsigned char *)(state + 0xa) = 1;
        }
    } else if (*(unsigned char *)(state + 0xa) == 1) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x15000) {
            func_ov107_020c5af8(*state, 0x16f, 5, (void *)state[3]);
            *(unsigned char *)(state + 0xa) = 2;
        }
    } else if (*(unsigned char *)(state + 0xa) == 2) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) < 0x15000) {
            *(unsigned char *)(state + 0xa) = 0;
        }
    }
    at = *(Vec3 *)(*(int *)(*state + 0x3a0) + (state[9] << 4) + 0x10);
    VEC_Subtract(&at, (Vec3 *)state[3], &d);
    dist = func_01ff8d18(&d, &d);
    limit = speed;
    if (dist < limit) {
        limit = dist >> 1;
    }
    state[2] = func_020050b4(d.x, d.z);
    dot = VEC_DotProduct(&d, &fwd);
    if (dot < 0) {
        dot = 0;
    }
    func_01ffa724((int)(((long long)limit * dot + 0x800) >> 12) >> 1, &fwd, (Vec3 *)(state + 4));
    state[7] = 0;
    if (*(unsigned char *)state[8] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 3, 0);
    func_ov107_020c9ee8(*(void **)(*state + 0x394), 2, 0);
    *(unsigned char *)(state + 0xa) = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov291_020cd2d0);
}
