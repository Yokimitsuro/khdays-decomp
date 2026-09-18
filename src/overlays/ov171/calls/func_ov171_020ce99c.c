/* Carry-dash tick of the ov171 enemy (and its byte-identical twins). With a target in reach the
 * +0x20 orientation quaternion is slerped (frame-time * 300 / 100) towards the quaternion turning
 * the shared forward vector onto the direction from the +8 position to the target's +0x190 point,
 * and the +0x30 velocity becomes (0, 0, 0x500) rotated by it. The +0x38c item's own sphere is
 * swept: the first victim that accepts a flat push (mode 0, strength 0x200) gets the item's +0xb0
 * point published (mode 2) and reaction 0x140 mode 6; its +0x74 sphere is copied to +0x10 and its
 * +0x18c rider becomes the +0xc carried target (grabbed with func_ov022_020ad8e0 mode 1, +0x4c
 * timer reset, hand-off to the carry-release tick) or, without a rider, the state ends with
 * sub-state 0. Otherwise the step from the +0x3c origin to the position is cast against the
 * scene (ray, then the second ray cast, then a sphere of the actor's +0x80 radius) unless the
 * +0x17a flags bits 0/1/3 already report a wall; a hit publishes the position (mode 1) with
 * reaction 0x140 mode 7 and ends; else the +0x48 travel accumulates the step length and ends the
 * dash past 0x15000. */
typedef unsigned char u8;

struct Vecx32 { int x, y, z; };
struct Vecx32_4 { int x, y, z, w; };
struct Quat { int a, b, c, d; };
struct Flags17a { u8 b0 : 1, b1 : 1, b2 : 1, b3 : 1; };

extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_0202ed60(struct Quat *dst, const struct Vecx32 *from, const struct Vecx32 *to);
extern void func_0202f55c(struct Quat *dst, int t, const struct Quat *a, const struct Quat *b);
extern void func_0202f384(void *dst, void *quat, void *vec);
extern int func_ov107_020c8eb8(void *item, void *sphere, void *out);
extern int func_ov107_020ca918(void *hit, int actor, void *item, int mode, void *push, int z);
extern void func_ov107_020c0b90(void *item, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_ov022_020ad8e0(int target, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void *func_01fff888(void *world, void *from, void *step, void *z);
extern void *func_01fff8b8(void *world, void *from, void *step, void *z);
extern void *func_01fff8e8(void *world, void *from, void *step, int radius, void *z);
extern int VEC_Mag(const struct Vecx32 *v);
extern const struct Vecx32 data_02042258;
extern void func_ov171_020ced14(int *node);

void func_ov171_020ce99c(int *node)
{
    int actor;
    int *state = (int *)node[1];
    struct Vecx32 step;
    void *hits[4];
    struct Quat turn;
    struct Vecx32 push;
    int i;
    int n;
    int target;
    int scene;
    int wall;
    int hit;

    actor = *state;
    target = func_ov107_020cab14(actor, 0);
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x190), (void *)state[2], &step);
        func_01ff8d18(&step, &step);
        func_0202ed60(&turn, &data_02042258, &step);
        func_0202f55c((struct Quat *)(state + 8), *(int *)(*node + 0x2c) * 300 / 100, (struct Quat *)(state + 8), &turn);
        state[0xc] = 0;
        state[0xd] = 0;
        state[0xe] = 0x500;
        func_0202f384(state + 0xc, state + 8, state + 0xc);
    }
    n = func_ov107_020c8eb8(*(void **)(*state + 0x38c), (void *)(actor + 0x74), hits);
    i = 0;
    if (n > 0) {
        do {
            VEC_Subtract((char *)hits[i] + 0x74, (void *)(actor + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(void **)(*state + 0x38c), 0, &push, 0x200) != 0) {
                char *item = *(char **)(*state + 0x38c);
                func_ov107_020c0b90(item, 2, *(struct Vecx32 *)(item + 0xb0), 0);
                func_ov107_020c5af8(*state, 0x140, 6, (void *)state[2]);
                *(struct Vecx32_4 *)(state + 4) = *(struct Vecx32_4 *)((char *)hits[i] + 0x74);
                target = *(int *)((char *)hits[i] + 0x18c);
                state[3] = target;
                if (target != 0) {
                    func_ov022_020ad8e0(target, 1);
                    state[0x13] = 0;
                    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov171_020ced14);
                    return;
                }
                *(u8 *)(*state + 0x1c7) = 0;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            i++;
        } while (i < n);
    }
    VEC_Subtract((void *)state[2], state + 0xf, &step);
    actor = *state;
    wall = hit = 1;
    if (((struct Flags17a *)(actor + 0x17a))->b0 == 0 && ((struct Flags17a *)(actor + 0x17a))->b1 == 0) {
        wall = 0;
    }
    if (wall == 0 && ((struct Flags17a *)(actor + 0x17a))->b3 == 0) {
        hit = 0;
    }
    if (state[0x12] == 0) {
        scene = *(int *)(actor + 4);
        if (hit == 0) {
            hit = (int)func_01fff888(*(void **)(scene + 0x7c), state + 0xf, &step, 0);
        }
        if (hit == 0) {
            hit = (int)func_01fff8b8(*(void **)(scene + 0x7c), state + 0xf, &step, 0);
        }
        if (hit == 0) {
            hit = (int)func_01fff8e8(*(void **)(scene + 0x7c), state + 0xf, &step, *(int *)(*state + 0x80), 0);
        }
    }
    *(struct Vecx32 *)(state + 0xf) = *(struct Vecx32 *)state[2];
    if (hit != 0) {
        func_ov107_020c0b90(*(void **)(*state + 0x38c), 1, *(struct Vecx32 *)state[2], 0);
        func_ov107_020c5af8(*state, 0x140, 7, (void *)state[2]);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x12] += VEC_Mag(&step);
    if (state[0x12] < 0x15000) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
