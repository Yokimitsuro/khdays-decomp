/* Slam tick of the ov276 enemy: the +0x4c timer accumulates the frame-time, the +0x10 velocity
 * is the +0x470 item's +0x2c vector turned by the +0x40 yaw and, past 0xff0, reaction 0x164 mode
 * 0xf fires once (+0x61) at the +0xc position. Between 0x2a8 and 0x440 the +0x474 sphere,
 * enlarged 1.375 times and pushed that far along the facing of the yaw, is swept: every entity
 * whose id bit is clear in the +0x62 mask gets the bit set and receives a 0xa8 hit packet whose
 * normal points from the +0x474 point to it (flattened) through its +0x1c4 handler. Once the +4
 * item's +0xad byte clears, sub-state 6 (roll below 80) or 2 is requested and the state ends. */
typedef unsigned char u8;
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { int m[9]; } Mtx33;

struct HitPacket40 {
    int nKind;
    Vec3 vNormal;
    int w[6];
};

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern int func_ov107_020c8eb8(int actor, Sphere *sphere, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int func_02023eb4(int range);
extern void func_0203c634(int *node, int slot, void *cb);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov276_020d1ee4(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    Vec3 facing;
    Sphere sphere;
    int hits[4];
    unsigned int idx;
    long i;
    long n;
    unsigned int mask;

    state[0x13] += *(int *)(*node + 0x2c);
    idx = ANG2IDX(state[0x10]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x470) + 0x2c), &mtx, (Vec3 *)(state + 4));
    if (*(u8 *)((char *)state + 0x61) == 0 && state[0x13] >= 0xff0) {
        func_ov107_020c5af8(*state, 0x164, 0xf, (void *)state[3]);
        *(u8 *)((char *)state + 0x61) = 1;
    }
    if (state[0x13] >= 0x2a8 && state[0x13] <= 0x440) {
        struct HitPacket40 packet = {0};
        packet.nKind = 0xa8;
        sphere = *(Sphere *)(*state + 0x474);
        sphere.radius = FX_MUL(sphere.radius, 0x1600);
        idx = ANG2IDX(state[0x10]);
        facing.y = 0;
        facing.x = data_0203d210[idx * 2];
        facing.z = data_0203d210[idx * 2 + 1];
        func_01ffa724(sphere.radius, &facing, &facing);
        VEC_Add(&facing, &sphere.pos, &sphere.pos);
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        i = 0;
        if (n > 0) {
            do {
                mask = (1 << *(unsigned short *)(hits[i] + 2)) & 0xff;
                if ((*(u8 *)((char *)state + 0x62) & mask) == 0) {
                    *(u8 *)((char *)state + 0x62) |= mask;
                    VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x474), &packet.vNormal);
                    packet.vNormal.y = 0;
                    func_01ff8d18(&packet.vNormal, &packet.vNormal);
                    (*(void (**)(unsigned short, struct HitPacket40 *))(hits[i] + 0x1c4))(*(unsigned short *)(hits[i] + 2), &packet);
                }
            } while (++i < n);
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (func_02023eb4(0x64) < 0x50) {
        *(u8 *)(*state + 0x1c7) = 6;
    } else {
        *(u8 *)(*state + 0x1c7) = 2;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
