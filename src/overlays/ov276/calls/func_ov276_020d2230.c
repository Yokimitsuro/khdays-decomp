/* Spin attack tick of the ov276 enemy. The +0x4c timer accumulates the frame-time; until bit 7
 * of +0x61 latches (after 0x110), animation 0xf plays and the timer restarts. Then, before 0xbb1,
 * a negative distance to the target ends the state; up to 0x1fe0 the +0x10 velocity is the
 * facing of the +0x40 yaw at 0x180. Between 0xbb0 and 0x1188 the +0x474 sphere enlarged 1.625
 * times sweeps contacts of kind 0; between 0x15c8 and 0x1a90 the +0x62 mask resets once (bit 2
 * of +0x61) and the sphere pushed its radius ahead along the facing sweeps contacts of kind 5.
 * Reaction 0x164 modes 7 (from 0xbb0) and 8 (from 0x1430) fire once each (bits 0/1) at the
 * +0xc position; once the +4 item's +0xad byte clears sub-state 2 is requested and the state
 * ends. */
typedef unsigned char u8;
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern int func_ov276_020d0cf0(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov276_020d0954(int *state, int kind, Sphere *sphere, void *box);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov276_020d2230(int *node)
{
    int *state = (int *)node[1];
    Sphere sphere;
    Vec3 ahead;
    unsigned int idx;

    sphere = *(Sphere *)(*state + 0x474);
    state[0x13] += *(int *)(*node + 0x2c);
    if ((*(u8 *)((char *)state + 0x61) & 0x80) == 0) {
        if (state[0x13] >= 0x110) {
            *(u8 *)((char *)state + 0x61) |= 0x80;
            state[0x13] = 0;
            func_ov107_020c9264(*state, 0xf, 0);
        }
        return;
    }
    if (state[0x13] <= 0xbb0 && func_ov276_020d0cf0(node) < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x13] <= 0x1fe0) {
        idx = ANG2IDX(state[0x10]);
        state[4] = data_0203d210[idx * 2];
        state[5] = 0;
        state[6] = data_0203d210[idx * 2 + 1];
        func_01ffa724(0x180, (Vec3 *)(state + 4), (Vec3 *)(state + 4));
    }
    if (state[0x13] >= 0xbb0 && state[0x13] <= 0x1188) {
        sphere.radius = FX_MUL(sphere.radius, 0x1a00);
        func_ov276_020d0954(state, 0, &sphere, 0);
    } else if (state[0x13] >= 0x15c8 && state[0x13] <= 0x1a90) {
        if ((*(u8 *)((char *)state + 0x61) & 4) == 0) {
            *(u8 *)((char *)state + 0x61) |= 4;
            *(u8 *)((char *)state + 0x62) = 0;
        }
        idx = ANG2IDX(state[0x10]);
        ahead.x = data_0203d210[idx * 2];
        ahead.y = 0;
        ahead.z = data_0203d210[idx * 2 + 1];
        func_01ffa724(sphere.radius, &ahead, &ahead);
        VEC_Add(&ahead, &sphere.pos, &sphere.pos);
        func_ov276_020d0954(state, 5, &sphere, 0);
    }
    if ((*(u8 *)((char *)state + 0x61) & 1) == 0 && state[0x13] >= 0xbb0) {
        func_ov107_020c5af8(*state, 0x164, 7, (void *)state[3]);
        *(u8 *)((char *)state + 0x61) |= 1;
    }
    if ((*(u8 *)((char *)state + 0x61) & 2) == 0 && state[0x13] >= 0x1430) {
        func_ov107_020c5af8(*state, 0x164, 8, (void *)state[3]);
        *(u8 *)((char *)state + 0x61) |= 2;
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
