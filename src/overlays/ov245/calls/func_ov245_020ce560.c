/* func_ov245_020ce560 -- landing tick: the +0xc velocity is the negated +0x4c8 anchor direction.
 * While still descending (+0x14 < 0) the actor's +0x3bc query block, moved by the velocity, is
 * swept (020c8df0) and each hit whose +2 slot bit is not in the +0x40 mask is pushed
 * (0, 1.0, -5.0) by the actor itself (020ca918, mode 4, 0x80): a landing hit gets effect 0 at its
 * +0x74 position and its bit set, and any landing fires reaction 0/0x51 at the actor's +0x74.
 * Once landed, every actor of the scene's +0xa8 list in the same scene whose bit is not yet in
 * +0x42 is hit at the origin with mode 7 (when its bit is in the +0x438 owner's +0x3b0 mask) or
 * mode 4 (when in +0x40), 0x218, and marked in +0x42. Once the +4 item's animation is free
 * (+0xad) the owner is released (020d4870), sub-state 2 set and the node slot freed. */
typedef struct { int x, y, z; } Vec3;
struct Ov245Query { Vec3 pos; int w[12]; };

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8df0(int actor, struct Ov245Query *query, int *out);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, const Vec3 *push, int z);
extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern int func_ov245_020d4870(int owner);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;

void func_ov245_020ce560(int *node) {
    int *state = (int *)node[1];
    Vec3 push;
    int hits[4];
    struct Ov245Query query;
    int any;
    int nHits;
    int i;
    unsigned char bit;
    unsigned char mask;
    int scene;
    int *entry;
    int other;
    int actor;

    func_01ffa724(-0x1000, (Vec3 *)(*(int *)(*state + 0x4c8) + 0x2c), (Vec3 *)(state + 3));
    if (state[5] < 0) {
        query = *(struct Ov245Query *)(*state + 0x3bc);
        any = 0;
        VEC_Add(&query.pos, (Vec3 *)(state + 3), &query.pos);
        push.x = 0;
        push.y = 0x1000;
        push.z = -0x5000;
        nHits = func_ov107_020c8df0(*state, &query, hits);
        for (i = 0; i < nHits; i++) {
            bit = 1 << *(unsigned short *)(hits[i] + 2);
            if ((*((unsigned char *)state + 0x40) & bit) == 0) {
                if (func_ov107_020ca918(hits[i], *state, *state, 4, &push, 0x80) != 0) {
                    func_ov107_020c0b90(*state, 0, *(Vec3 *)(hits[i] + 0x74), 0);
                    *((unsigned char *)state + 0x40) |= bit;
                    any = 1;
                }
            }
        }
        if (any != 0) {
            func_ov107_020c5af8(*state, 0, 0x51, (void *)(*state + 0x74));
        }
    } else {
        scene = *(int *)(*state + 4);
        entry = func_01fffd70((void *)(scene + 0xa8));
        other = entry == 0 ? 0 : *entry;
        while (other != 0) {
            mask = 1 << *(unsigned short *)(other + 2);
            if ((*((unsigned char *)state + 0x42) & mask) == 0 && *(int *)(other + 4) == *(int *)(*state + 4)) {
                actor = *state;
                if ((mask & *(unsigned char *)(*(int *)(actor + 0x438) + 0x3b0)) != 0) {
                    func_ov107_020ca918(other, actor, actor, 7, &data_02041dc8, 0x218);
                    *((unsigned char *)state + 0x42) |= mask;
                } else if ((*((unsigned char *)state + 0x40) & mask) != 0) {
                    func_ov107_020ca918(other, actor, actor, 4, &data_02041dc8, 0x218);
                    *((unsigned char *)state + 0x42) |= mask;
                }
            }
            entry = func_01fffd8c((void *)(scene + 0xa8));
            other = entry == 0 ? 0 : *entry;
        }
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov245_020d4870(*(int *)(*state + 0x438));
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
