/* Ov279_TickHoldTarget -- hold tick of the ov279 enemy: keeps itself at the point 1.875 in front
 * of the held target (along the target model's yaw), faces it, and drops the hold (owner +0x1c7 =
 * 2) once the target is gone, belongs to another world or is no longer active. If the target
 * drifted more than 1.5 away, is flagged 0x20 at +0x1e4, or its rider is busy or dead, the enemy
 * is pushed out of the world at the target's height (+0x1c7 = 8). Otherwise, once the +0x50 timer
 * reaches 1.0, it releases the target: plays animation 5, clears the grab bits, spawns effect
 * 0x167 at the anchor, hands the rider to 020ad8e0 and moves on to func_ov279_020d2d98. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct lo8 { unsigned int lo : 8; };
typedef struct { char pad[0x464]; unsigned long long flags; char pad2[0x12]; } Rider;

extern void func_ov107_020c5c54(int actor, Vec3 *pos);
extern void func_0203cd7c(int *dst, const Vec3 *a, const Vec3 *b, const void *c);
extern void func_0202ea48(void *dst, const int *src);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int  VEC_Mag(const Vec3 *v);
extern void func_ov279_020d0888(int world, Vec3 *pos, int rad, int height);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov022_020ad8e0(int rider, int n);
extern void func_ov279_020d2d98(int *node);
extern const short data_0203d210[];
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov279_020d2a04(int *node)
{
    int *state = (int *)node[1];
    int mtx[9];
    Vec3 pos;
    Vec3 d;
    int target = state[2];
    int yaw = (*(unsigned short *)(*(int *)(*(int *)(target + 0x18c) + 0x20) + 0x80) - 0x8000) & 0xffff;
    int rad = (int)(((long long)yaw * 0x6487f + 0x80000) >> 20);
    Vec3 *tpos = (Vec3 *)(target + 0x74);
    int rider;

    pos.x = *(int *)(target + 0x74) + FX_MUL(data_0203d210[ANG2IDX(rad) * 2], 0x1e00);
    pos.y = tpos->y;
    pos.z = tpos->z + FX_MUL(data_0203d210[ANG2IDX(rad) * 2 + 1], 0x1e00);
    func_ov107_020c5c54(*state, &pos);
    func_0203cd7c(mtx, tpos, (Vec3 *)state[0x13], &data_02042264);
    func_0202ea48(state + 7, mtx);
    *(Quat *)(state + 3) = *(Quat *)(state + 7);
    if (state[2] == 0 || *(int *)(state[2] + 4) != *(int *)(*state + 4)
        || !(((struct hw60 *)(state[2] + 0x60))->lo & 1)) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((Vec3 *)(state + 0x1d), tpos, &d);
    if (VEC_Mag(&d) > 0x1800 || (*(unsigned int *)(state[2] + 0x1e4) & 0x20)
        || ((rider = *(int *)(state[2] + 0x18c)) != 0
            && ((((Rider *)rider)->flags & 0x8000) != 0 || *(unsigned short *)(rider + 0x12) == 0))) {
        pos = *tpos;
        pos.y += *(int *)(state[2] + 0x80) + *(int *)(*state + 0x80);
        func_ov279_020d0888(*(int *)(*state + 4), &pos, rad, *(int *)(*state + 0x80));
        func_ov107_020c5c54(*state, &pos);
        *(unsigned char *)(*state + 0x1c7) = 8;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x14] += *(int *)(*node + 0x2c);
    if (!(state[0x14] < 0x1000)) {
        func_ov107_020c0b90(*state, 4, data_02041dc8, 0);
        func_ov107_020c9264(*state, 5, 0);
        ((struct hw60 *)(*state + 0x60))->hi &= ~4;
        *(unsigned short *)(*state + 0x1ae) &= ~1;
        ((struct lo8 *)(*(int *)(*state + 0x388) + 8))->lo |= 1;
        func_ov107_020c5af8(*state, 0x167, 7, (void *)state[0x13]);
        *(int *)(*state + 0x3ac) = *(int *)(state[2] + 0x18c);
        func_ov022_020ad8e0(*(int *)(*state + 0x3ac), 1);
        state[0x14] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov279_020d2d98);
        return;
    }
}
