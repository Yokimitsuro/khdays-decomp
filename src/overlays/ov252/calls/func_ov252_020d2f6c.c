/* Shot flight tick: the part's +0x5c bit 1 clears, the +0x20 timer accumulates the frame rate and
 * the +8 position advances by the +0x14 velocity. While the owner (+4) is active (+0x50 == 1) a 0.75
 * sphere there sweeps the actor list: every entity in it is pushed 0.5 away horizontally (kind 0);
 * on acceptance reaction 0x148 mode 7 fires at the shot and the owner's +0x57a bit of this shot's
 * slot (+0x24) toggles. Hitting the owner's +4 +0x7c grid (01fff920) or its 0.75 sweep (01fff948)
 * toggles it too. The +0x7c part follows the shot (0203ca30). Past 1.0, or once its bit is set,
 * the bit toggles, the owner spawns effect 0 at the shot, the slot's +0x640 entry clears and the
 * node is released (0203c640). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;

extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_01fff920(int grid, void *pos, void *vel);
extern int func_01fff948(int grid, void *pos, void *vel, int radius);
extern void func_0203ca30(int srt, void *pos);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c640(int *node);

void func_ov252_020d2f6c(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    Sphere sphere;
    Vec3 push;
    int owner;
    signed char i;
    int n;

    *(int *)(*state + 0x5c) &= ~2;
    state[8] += *(int *)(node[0] + 0x2c);
    VEC_Add(state + 2, state + 5, state + 2);
    if (*(int *)(state[1] + 0x50) == 1) {
        sphere.center = *(Vec3 *)(state + 2);
        sphere.nRadius = 0xc00;
        n = func_ov107_020c8eb8(state[1], &sphere, hits);
        for (i = 0; i < n; i++) {
            VEC_Subtract((void *)(hits[i] + 0x190), state + 2, &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], state[1], state[1], 0, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c5af8(state[1], 0x148, 7, state + 2);
            *(u16 *)(state[1] + 0x57a) ^= 1 << *((signed char *)state + 0x24);
        }
    }
    owner = *(int *)(state[1] + 4);
    if (func_01fff920(*(int *)(owner + 0x7c), state + 2, state + 5) != 0) {
        *(u16 *)(state[1] + 0x57a) ^= 1 << *((signed char *)state + 0x24);
    }
    if (func_01fff948(*(int *)(owner + 0x7c), state + 2, state + 5, 0xc00) != 0) {
        *(u16 *)(state[1] + 0x57a) ^= 1 << *((signed char *)state + 0x24);
    }
    func_0203ca30(*state + 4, state + 2);
    if (state[8] < 0x1000 && (*(u16 *)(state[1] + 0x57a) & (1 << *((signed char *)state + 0x24))) != 0) {
        return;
    }
    *(u16 *)(state[1] + 0x57a) ^= 1 << *((signed char *)state + 0x24);
    func_ov107_020c0b90(state[1], 0, *(Vec3 *)(state + 2), 0);
    *(int *)(state[1] + (*((signed char *)state + 0x24) + 0x13) * 8 + 0x640) = 0;
    func_0203c640(node);
}
