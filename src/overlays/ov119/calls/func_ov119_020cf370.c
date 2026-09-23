/* Carry tick of the ov119 enemy (x3 with ov272/ov279). When the +0x3ac grab partner's +0x4ec
 * owner is flagged 4 (+0x1e4), the partner is released (ov022 020ad8e0), the grab cleared and
 * sub-state 2 requested. Otherwise the owner is placed (c5c54) 0.94 behind the +8 target (its rig
 * yaw turned half a circle) and faces it from the +0x4c point; every 0x155 of the +0x54 timer the
 * target takes a kind-1 hit (0x210). The carried point is the target's +0x190 point plus a nudge:
 * up 1/16 while the carry height (+0x6c) is within 4.0 of the +0x4c point, and a random shake
 * while the target is flagged 0x10; it is pushed out of the world (func_ov119_020ccc48, the
 * target's radius) and given to the partner's +0x20 model and +0x48c point. Once the +0x50 timer
 * reaches 2.0 the owner is set down above it, the partner is released and sub-state 8 requested. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern void func_ov022_020ad8e0(int partner, int flag);
extern void func_ov107_020c5c54(int owner, Vec3 *pos);
extern void func_0203cd7c(int *dst, const Vec3 *a, const Vec3 *b, const void *c);
extern void func_0202ea48(void *dst, const int *src);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, const Vec3 *push, int z);
extern int func_02023eb4(int n);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov119_020ccc48(int world, Vec3 *point, int unused, int radius);
extern void func_0202b450(int model, Vec3 *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

void func_ov119_020cf370(int *node)
{
    int target;
    int *state = (int *)node[1];
    int partner = *(int *)(*state + 0x3ac);
    int mtx[9];
    Vec3 pos;
    Vec3 nudge;
    int yaw;
    int rad;
    int world;
    int done;
    int d;

    world = *(int *)(*state + 4);
    if ((*(int *)(*(int *)(partner + 0x4ec) + 0x1e4) & 4) != 0) {
        func_ov022_020ad8e0(partner, 0);
        *(int *)(*state + 0x3ac) = 0;
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    target = state[2];
    yaw = (*(unsigned short *)(*(int *)(*(int *)(target + 0x18c) + 0x20) + 0x80) - 0x8000) & 0xffff;
    rad = (int)(((long long)yaw * 0x6487f + 0x80000) >> 20);
    pos.x = *(int *)(target + 0x74) + FX_MUL(data_0203d210[ANG2IDX(rad) * 2], 0xf00);
    pos.y = *(int *)(target + 0x78);
    pos.z = *(int *)(target + 0x7c) + FX_MUL(data_0203d210[ANG2IDX(rad) * 2 + 1], 0xf00);
    func_ov107_020c5c54(*state, &pos);
    func_0203cd7c(mtx, (Vec3 *)(target + 0x74), (Vec3 *)state[0x13], &data_02042264);
    func_0202ea48(state + 7, mtx);
    *(Quat *)(state + 3) = *(Quat *)(state + 7);
    state[0x15] += *(int *)(*node + 0x2c);
    if (state[0x15] > 0x155) {
        func_ov107_020ca918(state[2], *state, *state, 1, &data_02041dc8, 0x210);
        state[0x15] = 0;
    }
    nudge = data_02041dc8;
    d = state[0x1b] - *(int *)(state[0x13] + 4);
    if (d < 0) {
        d = -d;
    }
    if (d < 0x4000) {
        nudge.x = 0;
        nudge.y = 0x100;
        nudge.z = 0;
    }
    if ((*(int *)(state[2] + 0x1e4) & 0x10) != 0) {
        state[0x14] += *(int *)(*node + 0x2c);
        nudge.x = func_02023eb4(0x201) - 0x100;
        nudge.y = func_02023eb4(0x41) - 0x40;
        nudge.z = func_02023eb4(0x201) - 0x100;
    }
    VEC_Add((Vec3 *)(state[2] + 0x190), &nudge, &pos);
    state[0x14] += *(int *)(*node + 0x2c);
    done = state[0x14] >= 0x2000;
    func_ov119_020ccc48(world, &pos, rad, *(int *)(state[2] + 0x80));
    partner = *(int *)(*state + 0x3ac);
    func_0202b450(*(int *)(partner + 0x20), &pos);
    *(Vec3 *)(partner + 0x48c) = pos;
    *(int *)(*(int *)(*state + 0x3ac) + 0x58) = 0;
    if (done == 0) {
        return;
    }
    pos.y += *(int *)(state[2] + 0x80) + *(int *)(*state + 0x80);
    func_ov119_020ccc48(world, &pos, rad, *(int *)(*state + 0x80));
    func_ov107_020c5c54(*state, &pos);
    func_ov022_020ad8e0(*(int *)(*state + 0x3ac), 0);
    *(int *)(*state + 0x3ac) = 0;
    *(unsigned char *)(*state + 0x1c7) = 8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
