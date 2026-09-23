/* Flight tick of the ov208 enemy's item (x3 with ov209/ov268). Plays animation 1 (looping) once
 * the +4 animator is free and scales the +0x18 direction by 0.25 into the +0xc step. An oriented
 * box at the item's +0x74 point (axes: up x direction, up, direction; half-extents +0x80, 0.75,
 * 0.75) is swept over the owner's (+0x394) list: every entity is pushed along the flattened unit
 * direction from the item (kind 3, from the owner) and, on acceptance, the owner spawns effect 1
 * at the +8 point and reaction 0/0x53 fires there. The move from the +0x24 previous point to +8
 * is then checked against the world's (+4 -> +0x7c) collision: a wall hit, or a floor hit of
 * radius 0.1875 whose surface has no +8 owner, bursts the item (effect 1, reaction 0/0x53,
 * animation 2) and hands over to func_ov208_020d4754; otherwise the travelled length accumulates
 * in +0x40 and past 15.0 the item bursts silently. */
typedef struct { int x, y, z; } Vec3;
struct Obb { Vec3 center; Vec3 axisX; Vec3 axisY; Vec3 axisZ; int extent[3]; };

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8df0(int actor, struct Obb *query, int *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void *func_01fff920(void *collision, Vec3 *origin, Vec3 *dir);
extern int *func_01fff8e8(void *collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern int VEC_Mag(const Vec3 *v);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042264;
extern void func_ov208_020d4754(int *node);

void func_ov208_020d442c(int *node)
{
    int *state = (int *)node[1];
    int world = *(int *)(*state + 4);
    int hits[4];
    struct Obb query;
    Vec3 delta;
    Vec3 push;
    int i;
    int n;
    int *floor;

    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 1, 1);
    }
    func_01ffa724(0x400, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
    query.center = *(Vec3 *)(*state + 0x74);
    query.axisY = data_02042264;
    query.axisZ = *(Vec3 *)(state + 6);
    VEC_CrossProduct(&query.axisY, &query.axisZ, &query.axisX);
    query.extent[0] = *(int *)(*state + 0x80);
    query.extent[1] = 0xc00;
    query.extent[2] = 0xc00;
    n = func_ov107_020c8df0(*(int *)(*state + 0x394), &query, hits);
    i = 0;
    if (n > 0) {
        do {
            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x394), 3, &push, 0) != 0) {
                func_ov107_020c0b90(*(int *)(*state + 0x394), 1, *(Vec3 *)state[2], 0);
                func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
            }
        } while (++i < n);
    }
    VEC_Subtract((void *)state[2], (void *)(state + 9), &delta);
    *(Vec3 *)(state + 9) = *(Vec3 *)state[2];
    if (func_01fff920(*(void **)(world + 0x7c), (Vec3 *)state[2], &delta) != 0) {
        func_ov107_020c0b90(*(int *)(*state + 0x394), 1, *(Vec3 *)state[2], 0);
        func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
        func_ov107_020c9264(*state, 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov208_020d4754);
        return;
    }
    floor = func_01fff8e8(*(void **)(world + 0x7c), (Vec3 *)state[2], &delta, 0x300, 0);
    if (floor != 0 && floor[2] == 0) {
        func_ov107_020c0b90(*(int *)(*state + 0x394), 1, *(Vec3 *)state[2], 0);
        func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
        func_ov107_020c9264(*state, 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov208_020d4754);
        return;
    }
    state[0x10] += VEC_Mag(&delta);
    if (state[0x10] <= 0xf000) {
        return;
    }
    func_ov107_020c0b90(*(int *)(*state + 0x394), 1, *(Vec3 *)state[2], 0);
    func_ov107_020c9264(*state, 2, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov208_020d4754);
}
