/* Reach tick of the ov254 arm helper: it stays on the +0x38c owner's +0x414 part (released, +0x60
 * high byte bit 7 cleared) and loops pose 1 once the +4 item's +0xad byte clears. The +0x24 reach
 * timer (0..0x7f8) grows a capsule from that point along the direction to the owner's +0x3dc
 * target (pitch clamped to about +-35 degrees), turned by the owner's +0xa0 pose into the +0xc
 * direction: 25.0 long at full reach, radius 1.46, tested by 020d4458. Until it latched (+0x2d)
 * the tip is traced through the item's world (ground ray, then a swept sphere); on contact or at
 * full reach +0x18 takes the tip, the owner is knocked back there (mode 0) and it latches.
 * Latched, for 0xdd0 more (+0x28) a sphere at +0x18 grows to 10.0 and is tested instead. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[4]; Vec3 trans; int pad[4]; } Srt;
typedef struct { Vec3 a; Vec3 d; int len; int r; } Capsule;
typedef struct { Vec3 p; int r; } Sphere;
typedef struct { void *a; void *b; void *c; int d; } CollisionHit;
struct Hw60 { u16 lo : 8; u16 hi : 8; };

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c5c54(int actor, Vec3 *at);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_0202f384(Vec3 *out, const Srt *m, const Vec3 *in);
extern void func_ov254_020d4458(int *node, Sphere *s, Capsule *c);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern CollisionHit *func_01fff920(void *collision, Vec3 *origin, Vec3 *direction);
extern void func_01ffd144(int factor, Vec3 *in, Vec3 *out);
extern CollisionHit *func_01fff8e8(void *collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov254_020d48bc(int *node)
{
    int *state = (int *)node[1];
    Capsule cap;
    Vec3 anchor;
    Vec3 dir;
    Vec3 flat;
    Vec3 tip;
    Sphere sphere;
    int item;
    CollisionHit *hit;

    anchor = *(Vec3 *)(*(int *)(*(int *)(*state + 0x38c) + 0x414) + 0x14);
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 1, 1);
    }
    state[9] += *(int *)(node[0] + 0x2c);
    state[9] = state[9] > 0x7f8 ? 0x7f8 : (state[9] < 0 ? 0 : state[9]);
    ((struct Hw60 *)(*state + 0x60))->hi &= ~0x80;
    func_ov107_020c5c54(*state, &anchor);
    VEC_Subtract((Vec3 *)(*(int *)(*(int *)(*state + 0x38c) + 0x3dc) + 0x190), &anchor, &dir);
    func_01ff8d18(&dir, &dir);
    if (dir.y < -0x92d) {
        VecSet(&dir, 0, -0x92d, 0xd1b);
    } else if (dir.y > 0x92d) {
        VecSet(&dir, 0, 0x92d, 0xd1b);
    } else {
        VecSet(&flat, dir.x, 0, dir.z);
        VecSet(&dir, 0, dir.y, func_01ff8d18(&flat, &flat));
    }
    func_0202f384((Vec3 *)(state + 3), (Srt *)(*(int *)(*state + 0x38c) + 0xa0), &dir);
    cap.a = anchor;
    cap.d = *(Vec3 *)(state + 3);
    cap.len = state[9] * 0x64000 / 0x7f8;
    cap.r = 0x174c;
    func_ov254_020d4458(node, 0, &cap);
    if (*((unsigned char *)state + 0x2d) == 0) {
        func_01ffa724(cap.len, &cap.d, &tip);
        if (state[9] >= 0x7f8) {
            VEC_Add(&cap.a, &tip, (Vec3 *)(state + 6));
            func_ov107_020c0b90(*state, 0, *(Vec3 *)(state + 6), 0);
            *((unsigned char *)state + 0x2d) = 1;
            return;
        }
        item = *(int *)(*state + 4);
        hit = func_01fff920(*(void **)(item + 0x7c), &cap.a, &tip);
        if (hit != 0 && hit->c == 0) {
            func_01ffd144(hit->d, &tip, &tip);
            VEC_Add(&cap.a, &tip, (Vec3 *)(state + 6));
            func_ov107_020c0b90(*state, 0, *(Vec3 *)(state + 6), 0);
            *((unsigned char *)state + 0x2d) = 1;
            return;
        }
        hit = func_01fff8e8(*(void **)(item + 0x7c), &cap.a, &tip, cap.r, 0);
        if (hit == 0) {
            return;
        }
        if (hit->c != 0) {
            return;
        }
        func_01ffd144(hit->d, &tip, &tip);
        VEC_Add(&cap.a, &tip, (Vec3 *)(state + 6));
        func_ov107_020c0b90(*state, 0, *(Vec3 *)(state + 6), 0);
        *((unsigned char *)state + 0x2d) = 1;
        return;
    }
    if (state[0xa] >= 0xdd0) {
        return;
    }
    state[0xa] += *(int *)(node[0] + 0x2c);
    sphere.p = *(Vec3 *)(state + 6);
    sphere.r = (state[0xa] > 0x7f8 ? 0x7f8 : (state[0xa] < 0 ? 0 : state[0xa])) * 0xa000 / 0x7f8;
    func_ov254_020d4458(node, &sphere, 0);
}
