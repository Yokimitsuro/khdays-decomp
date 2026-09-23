/* Retreat decision of the ov252 actor: when an attack is queued (+0xa0) pose 3 and partner motion
 * 2 play and the node moves on to 020cfa28. Otherwise, with the +8 track more than 30.0 from the
 * origin or a clear line ahead along the +0x54 heading (swept sphere of the +0x80 radius), the
 * retreat mode (+0x579) comes from 020ce42c towards the origin and +0x18 becomes the home point
 * (3.375, 0, 7.25); far from the aim target (020cdfe8) with a +0x4e4 target it heads for that
 * target's +0x190 point instead; else the mode clears and 020cdef4 may end the node. A rider
 * (+0x78) forces mode 5. Mode 0 plays pose 2 / partner motion 1 and moves on to 020cf7d8; other
 * modes play pose 3m+1 (partner motion 3 or 6 for modes 1 / 2), clear +0x64 and move on to
 * 020cf6a0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { void *a; void *b; void *c; int d; } CollisionHit;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern CollisionHit *func_01fff8e8(void *collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern u8 func_ov252_020ce42c(int *state, Vec3 to);
extern int func_ov252_020cdfe8(int *node, Vec3 *to, int b);
extern int func_ov252_020cdef4(int *node);
extern void func_ov252_020cfa28(void);
extern void func_ov252_020cf7d8(void);
extern void func_ov252_020cf6a0(void);
extern const short data_0203d210[];
extern const Vec3 data_ov252_020d43a4;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov252_020cf3b8(int *node)
{
    int *state = (int *)node[1];
    int item = *(int *)(*state + 4);
    Vec3 toOrigin;
    Vec3 fwd;
    Vec3 home = data_ov252_020d43a4;
    CollisionHit *hit;
    unsigned int idx;
    int dist;

    if (state[0x28] != 0) {
        func_ov107_020c9264(*state, 3, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cfa28);
        return;
    }
    VecSet(&toOrigin, -((Vec3 *)state[2])->x, 0, -((Vec3 *)state[2])->z);
    dist = func_01ff8d18(&toOrigin, &fwd);
    idx = ANG2IDX(state[0x15]);
    VecSet(&fwd, data_0203d210[idx * 2], 0, data_0203d210[idx * 2 + 1]);
    hit = func_01fff8e8(*(void **)(item + 0x7c), (Vec3 *)state[2], &fwd, *(int *)(*state + 0x80), 0);
    if ((hit != 0 && hit->c == 0) || dist > 0x1e000) {
        *(u8 *)(*state + 0x579) = func_ov252_020ce42c(state, toOrigin);
        *(Vec3 *)(state + 6) = home;
    } else if (func_ov252_020cdfe8(node, &toOrigin, 0) > 0x1e000 && *(int *)(*state + 0x4e4) != 0) {
        *(u8 *)(*state + 0x579) = func_ov252_020ce42c(state, toOrigin);
        *(Vec3 *)(state + 6) = *(Vec3 *)(*(int *)(*state + 0x4e4) + 0x190);
    } else {
        *(u8 *)(*state + 0x579) = 0;
        if (func_ov252_020cdef4(node) != 0) {
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state[0x1e] != 0) {
        *(u8 *)(*state + 0x579) = 5;
    }
    if (*(u8 *)(*state + 0x579) == 0) {
        *((u8 *)state + 0x84) = 2;
        func_ov107_020c9264(*state, *((u8 *)state + 0x84), 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 1, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cf7d8);
        return;
    }
    *((u8 *)state + 0x84) = *(u8 *)(*state + 0x579) * 3 + 1;
    func_ov107_020c9264(*state, *((u8 *)state + 0x84), 0);
    switch (*(u8 *)(*state + 0x579)) {
    case 1:
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 3, 0);
        break;
    case 2:
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 6, 0);
        break;
    }
    state[0x19] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020cf6a0);
}
