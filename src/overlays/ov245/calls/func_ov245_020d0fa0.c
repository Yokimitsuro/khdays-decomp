/* func_ov245_020d0fa0 -- roll tick: on the first frame (bit 7 of the +0x60 low byte, cleared
 * here) effect 1 plays at the +8 anchor. The actor's +0x74 sphere is swept (020c8eb8) and every
 * hit is pushed 0.5 along the flattened direction from the actor through the +0x390 item
 * (020ca918, mode 0): a landing hit plays effect 2 and reaction 0x15a/0xa at the anchor and ends
 * the roll (sub-state 0). Otherwise the step since the last +0x28 position is probed against
 * the scene's +0x7c collision: a wall (01fff920) or a floor probe (01fff8e8, radius 0.1875)
 * that hits nothing solid fires reaction 0x15a/0x10 and ends the roll; else the travelled
 * distance accumulates in +0x24 and past 32.0 the roll ends with effect 2. */
typedef struct { int x, y, z; } Vec3;
struct Sphere { Vec3 centre; int radius; };
typedef unsigned short u16;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern int func_ov107_020c8eb8(int actor, struct Sphere *sphere, int *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_01fff920(int collision, const Vec3 *from, const Vec3 *step);
extern int func_01fff8e8(int collision, const Vec3 *from, const Vec3 *step, int radius, void *ignore);
extern int VEC_Mag(const Vec3 *v);

void func_ov245_020d0fa0(int *node) {
    int *state = (int *)node[1];
    struct Sphere sphere;
    Vec3 step;
    int hits[4];
    Vec3 push;
    int scene = *(int *)(*state + 4);
    int i;
    int nHits;
    int hit;

    if ((((struct hw60 *)(*state + 0x60))->lo & 0x80) != 0) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
        func_ov107_020c0b90(*state, 1, *(Vec3 *)state[2], 0);
    }
    sphere = *(struct Sphere *)(*state + 0x74);
    nHits = func_ov107_020c8eb8(*state, &sphere, hits);
    for (i = 0; i < nHits; i++) {
        VEC_Subtract((Vec3 *)(hits[i] + 0x74), (Vec3 *)(*state + 0x74), &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x800, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x390), 0, &push, 0) != 0) {
            func_ov107_020c0b90(*state, 2, *(Vec3 *)state[2], 0);
            func_ov107_020c5af8(*state, 0x15a, 0xa, (void *)state[2]);
            *(unsigned char *)(*state + 0x1c7) = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    VEC_Subtract((Vec3 *)state[2], (Vec3 *)(state + 10), &step);
    *(Vec3 *)(state + 10) = *(Vec3 *)state[2];
    if (func_01fff920(*(int *)(scene + 0x7c), (Vec3 *)state[2], &step) != 0) {
        func_ov107_020c5af8(*state, 0x15a, 0x10, (void *)state[2]);
    } else {
        hit = func_01fff8e8(*(int *)(scene + 0x7c), (Vec3 *)state[2], &step, 0x300, 0);
        if (hit != 0 && *(int *)(hit + 8) == 0) {
            func_ov107_020c5af8(*state, 0x15a, 0x10, (void *)state[2]);
        } else {
            state[9] += VEC_Mag(&step);
            if (state[9] < 0x20000) {
                return;
            }
        }
    }
    func_ov107_020c0b90(*state, 2, *(Vec3 *)state[2], 0);
    *(unsigned char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
