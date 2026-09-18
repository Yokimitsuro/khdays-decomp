/* Attack wind-up tick of the ov239 enemy: the +0x2c timer accumulates the frame-time and fires
 * reaction 0x138 modes 7 (from 0x88) and 8 (from 0xff0) once each (bits 0/1 of +0x32) at the +8
 * point; the +0x14 velocity is the +0x398 part's +0x2c motion turned by the +0x10 yaw, its y the
 * height of the target's +0x194 above the actor's +0xb4 clamped to +-0x200 (0 without a
 * target). Once the +4 item's +0xad byte clears, bit 0 of the actor's +0x1ae drops, the timer
 * resets and sub-state 6 is configured (part action 2, flag 1) before handing off to cd54c. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_ov239_020cc9f0(int *node, int anim, int action, int flag, void *next);
extern void func_ov239_020cd54c(int *node);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov239_020cd3a0(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    int dy;
    unsigned int idx;

    state[0xb] += *(int *)(*node + 0x2c);
    if ((*(u8 *)((char *)state + 0x32) & 1) == 0 && state[0xb] >= 0x88) {
        func_ov107_020c5af8(*state, 0x138, 7, (void *)state[2]);
        *(u8 *)((char *)state + 0x32) |= 1;
    }
    if ((*(u8 *)((char *)state + 0x32) & 2) == 0 && state[0xb] >= 0xff0) {
        func_ov107_020c5af8(*state, 0x138, 8, (void *)state[2]);
        *(u8 *)((char *)state + 0x32) |= 2;
    }
    idx = ANG2IDX(state[4]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x398) + 0x2c), &mtx, (Vec3 *)(state + 5));
    if (*(int *)(*state + 0x394) != 0) {
        dy = *(int *)(*(int *)(*state + 0x394) + 0x194) - *(int *)(*state + 0xb4);
        state[6] = dy;
        if (dy > 0x200) {
            dy = 0x200;
        } else if (dy < -0x200) {
            dy = -0x200;
        }
        state[6] = dy;
    } else {
        state[6] = 0;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned short *)(*state + 0x1ae) &= ~1;
    state[0xb] = 0;
    func_ov239_020cc9f0(node, 6, 2, 1, func_ov239_020cd54c);
}
