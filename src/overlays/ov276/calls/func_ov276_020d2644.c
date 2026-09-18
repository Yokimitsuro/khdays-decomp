/* Charge tick of the ov276 enemy: the +0x4c timer accumulates the frame-time and, past 0x550,
 * reaction 0x164 mode 0x10 fires once (+0x61) at the +0xc position. Once the +4 item's +0xad
 * byte clears, animation 0x14 plays (looped), the timer takes the +0x58 value and the tick
 * hands off to d275c; otherwise the +0x10 velocity is the +0x470 item's +0x2c vector turned by
 * the +0x40 yaw. */
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov276_020d275c(int *node);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov276_020d2644(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    unsigned int idx;

    state[0x13] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)((char *)state + 0x61) == 0 && state[0x13] >= 0x550) {
        func_ov107_020c5af8(*state, 0x164, 0x10, (void *)state[3]);
        *(unsigned char *)((char *)state + 0x61) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0x14, 1);
        state[0x13] = state[0x16];
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov276_020d275c);
        return;
    }
    idx = ANG2IDX(state[0x10]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x470) + 0x2c), &mtx, (Vec3 *)(state + 4));
}
