/* Slam aim tick of the ov225 enemy. The +0x5c timer accumulates the owner's rate and, once it
 * reaches 0x600 with a +0x10 target, the +0x14 leap is the flattened unit direction from the
 * owner's +0x74 to the target's +0x74 scaled 7.5 and turned by a random angle within +-0xc91;
 * a swept cast of the owner's +0x80 radius and a plain ray from the +0xc point both clip it to
 * their first hit, and the target is released. The tick then hands over to
 * func_ov225_020d2a80. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

struct CollisionHit { int pad00; int pad04; int pad08; int nAlong; };

extern int func_02023eb4(int bound);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern struct CollisionHit *func_01fff948(void *collision, void *origin, Vec3 *dir, int radius);
extern void func_01ffd144(int scale, Vec3 *in, Vec3 *out);
extern struct CollisionHit *func_01fff888(void *collision, void *origin, Vec3 *dir, void *ignore);
extern void func_0203c634(int *node, int slot, void *cb);
extern short data_0203d210[];
extern void func_ov225_020d2a80(int *node);

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov225_020d2908(int *node)
{
    int *state = (int *)node[1];
    Mtx33 m;
    Vec3 d;
    int ang;
    unsigned int idx;
    char *coll;
    struct CollisionHit *hit;

    state[0x17] += *(int *)(*node + 0x2c);
    if (state[0x17] < 0x600) {
        return;
    }
    if (state[4] != 0) {
        ang = func_02023eb4(0x1923) - 0xc91;
        coll = *(char **)(*state + 4);
        VEC_Subtract((Vec3 *)(state[4] + 0x74), (Vec3 *)(*state + 0x74), &d);
        d.y = 0;
        func_01ff8d18(&d, &d);
        func_01ffa724(0x7800, &d, &d);
        idx = ANG2IDX(ang);
        MTX_RotY33_(&m, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(&d, &m, (Vec3 *)(state + 5));
        hit = func_01fff948(*(void **)(coll + 0x7c), (void *)state[3], (Vec3 *)(state + 5), *(int *)(*state + 0x80));
        if (hit != 0) {
            func_01ffd144(hit->nAlong, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
        }
        hit = func_01fff888(*(void **)(coll + 0x7c), (void *)state[3], (Vec3 *)(state + 5), 0);
        if (hit != 0) {
            func_01ffd144(hit->nAlong, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
        }
        state[4] = 0;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov225_020d2a80);
}
