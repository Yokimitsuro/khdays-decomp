/* Aim start of the ov283 actor: after the shared step (020ccb48) both headings (+0x38, +0x40) face the
 * target's +0x390 model point, and the body is placed 6.0 back from that point along the heading
 * (vertical part from the aim); the pose settles (020c9264 mode 3), an effect plays at the +8 point,
 * the actor moves to the new spot (020c5c54) and the brain waits on 020ce214. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov283_020ccb48(int *node);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5c54(int owner, const Vec3 *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov283_020ce214(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov283_020ce0bc(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 unit;
    Vec3 back;
    Vec3 target;

    func_ov283_020ccb48(node);
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x390) + 0x190), (Vec3 *)(*state + 0x74), &d);
    func_01ff8d18(&d, &d);
    state[0xe] = state[0x10] = func_020050b4(d.x, d.z);
    target = *(Vec3 *)(*(int *)(*state + 0x390) + 0x190);
    func_01ff8d18(&d, &unit);
    {
        int idx = ANG2IDX(state[0xe]) * 2;

        back.x = data_0203d210[idx];
        back.y = unit.y;
        back.z = data_0203d210[idx + 1];
    }
    func_01ffa724(0x6000, &back, &back);
    VEC_Subtract(&target, &back, &target);
    func_ov107_020c9264(*state, 3, 0);
    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[2], 0);
    func_ov107_020c5c54(*state, &target);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov283_020ce214);
}
