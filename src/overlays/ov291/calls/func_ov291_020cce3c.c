/* Path-following tick of the ov291 enemy. The +0x394 item's speed and forward vector (rotated by
 * the actor's +0xa0 orientation) drive a three-phase sound cue on the +0x28 byte: the +0x384
 * item's channel-0 progress past 0x4000 fires reaction 0x16f/4, past 0x15000 reaction 0x16f/5,
 * and dropping below 0x15000 rearms it. The direction to the +0x3a0 path node after the +0x24
 * index (from the +0xc position) is normalised; a distance below the speed halves it; the +8
 * yaw aims at it and the +0x10 velocity is the facing (sin, 0, cos) of that yaw scaled by the
 * speed times the (clamped) alignment with the forward vector. The +0x1c turn step is
 * 30 x dt / 25. Within 0x1000 of the node its kind decides: 1/2 clears the +0x384 item's +0xa8
 * flag and hands off to cd100, 3 clears bit 0 of the +0x60 high byte and requests sub-state 0
 * (slot released), otherwise the index advances modulo the path's count. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

struct PathEntry {
    int x;
    int y;
    int z;
    int kind;
};

extern int func_ov107_020c9f48(int item, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *rotation, Vec3 *in);
extern int func_0203bec0(int item, int channel);
extern void func_ov107_020c5af8(int actor, int id, int mode, void *anchor);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_020050b4(int x, int z);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov291_020cd100(int *node);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov291_020cce3c(int *node)
{
    int *state = (int *)node[1];
    Vec3 fwd;
    Vec3 point;
    Vec3 dir;
    int speed;
    int len;
    int dot;
    unsigned int idx;
    int i;
    struct PathEntry *path;
    int kind;

    speed = func_ov107_020c9f48(*(int *)(*state + 0x394), &fwd);
    func_0202f384(&fwd, (void *)(*state + 0xa0), &fwd);
    if (*(u8 *)(state + 0xa) == 0) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x4000) {
            func_ov107_020c5af8(*state, 0x16f, 4, (void *)state[3]);
            *(u8 *)(state + 0xa) = 1;
        }
    } else if (*(u8 *)(state + 0xa) == 1) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x15000) {
            func_ov107_020c5af8(*state, 0x16f, 5, (void *)state[3]);
            *(u8 *)(state + 0xa) = 2;
        }
    } else if (*(u8 *)(state + 0xa) == 2) {
        if (func_0203bec0(*(int *)(*state + 0x384), 0) < 0x15000) {
            *(u8 *)(state + 0xa) = 0;
        }
    }
    point = *(Vec3 *)(*(int *)(*state + 0x3a0) + state[9] * 0x10 + 0x10);
    VEC_Subtract(&point, (Vec3 *)state[3], &dir);
    len = func_01ff8d18(&dir, &dir);
    if (len < speed) {
        speed = len >> 1;
    }
    state[2] = func_020050b4(dir.x, dir.z);
    dot = VEC_DotProduct(&dir, &fwd);
    if (dot < 0) {
        dot = 0;
    }
    idx = ANG2IDX(state[2]);
    fwd.x = data_0203d210[idx * 2];                                       /* FX_SinIdx */
    fwd.y = 0;
    fwd.z = data_0203d210[idx * 2 + 1];                                   /* FX_CosIdx */
    func_01ffa724(FX_MUL(speed, dot), &fwd, (Vec3 *)(state + 4));
    state[7] = *(int *)(*node + 0x2c) * 30 / 25;
    if (len > 0x1000) {
        return;
    }
    i = state[9];
    path = (struct PathEntry *)*(int *)(*state + 0x3a0);
    kind = (u16)path[i].kind;
    if (kind == 1 || kind == 2) {
        *(u8 *)(*(int *)(*state + 0x384) + 0xa8) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov291_020cd100);
        return;
    }
    if (kind == 3) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~1;
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[9] = (i + 1) % path[0].z;
}
