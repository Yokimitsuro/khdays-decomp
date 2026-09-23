/* Warp start of the ov283 actor: after the shared step (020ccb48) both headings (+0x38, +0x40) face
 * the target's +0x390 model point and the landing spot is picked past the target along the heading
 * (by both radii, vertical part from the aim); the floor is probed ahead of the target (twice the +0x80
 * range, radius 0x100). With the floor clear the warp is dropped: the +0x50 clock resets, +0x34
 * rerolls (1.57 to 3.14; +0x7c = past 2.36, +0x3c cleared) and the next move is 4. Otherwise an
 * effect plays at the +8 point, the actor moves to the spot at the target's height (020c5c54) and the
 * brain waits on 020ce620. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov283_020ccb48(int *node);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_01fff8e8(int collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern int func_02023e80(int bound);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5c54(int owner, const Vec3 *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov283_020ce620(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov283_020ce328(int *node)
{
    int *state = (int *)node[1];
    Vec3 fwd;
    Vec3 d;
    Vec3 unit;
    Vec3 off;
    Vec3 target;
    Vec3 probe;
    int world;
    int hit;

    func_ov283_020ccb48(node);
    world = *(int *)(*state + 4);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        fwd.x = data_0203d210[idx];
        fwd.y = 0;
        fwd.z = data_0203d210[idx + 1];
    }
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x390) + 0x190), (Vec3 *)(*state + 0x74), &d);
    func_01ff8d18(&d, &d);
    state[0xe] = state[0x10] = func_020050b4(d.x, d.z);
    target = *(Vec3 *)(*(int *)(*state + 0x390) + 0x190);
    func_01ff8d18(&d, &unit);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        off.x = data_0203d210[idx];
        off.y = unit.y;
        off.z = data_0203d210[idx + 1];
    }
    func_01ffa724(*(int *)(*(int *)(*state + 0x390) + 0x80) + *(int *)(*state + 0x80), &off, &off);
    VEC_Add(&target, &off, &target);
    probe = target;
    VEC_Add(&probe, &off, &probe);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        fwd.x = data_0203d210[idx];
        fwd.y = 0;
        fwd.z = data_0203d210[idx + 1];
    }
    func_01ffa724(*(int *)(*state + 0x80) * 2, &fwd, &d);
    hit = func_01fff8e8(*(int *)(world + 0x7c), (Vec3 *)(*(int *)(*state + 0x390) + 0x74), &d, 0x100, 0);
    target.y = *(int *)(*(int *)(*state + 0x390) + 0x194);
    if (hit != 0 && *(int *)(hit + 8) == 0) {
        state[0x14] = 0;
        state[0xd] = func_02023e80(0x1922) + 0x1922;
        state[0x1f] = state[0xd] > 0x25b3;
        state[0xf] = 0;
        *(signed char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[2], 0);
    func_ov107_020c5c54(*state, &target);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020ce620);
}
