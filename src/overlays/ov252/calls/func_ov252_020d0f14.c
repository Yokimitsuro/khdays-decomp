/* Leap tick of the ov252 actor: +0x64 accumulates the frame rate. While airborne (+0x88) the +0x3c
 * direction points at the target on the ground plane and the +0x58 heading follows it. After 4.0 the
 * landing spot is picked once (020d0a8c into +0x48, 020c5c54), a retreat is marked, pose 0x18 and effect
 * 0x32 play and the landing flags (+0x9c, actor +0x584) are set. In stage 2 after 6.0 bits 3-4 of the
 * +0x60 high byte are set and the stage drops; in stage 1 it lands at the spot: poses 0x31/0x35, effects
 * 0xa and 0x32 and sound 0x148/0xa there, and unguarded the guard flag (+0x60 bit 0) is set, the
 * +0x93 piece's shape shows and the next move is 5. On the ground it clears bit 4 after 1.5, steers
 * along +0x3c at 0.25 (double speed while retreating, rising at 0.5) and its body sphere (radius 6.5)
 * hits kind-2 targets with sound 0/0x53. Once grounded, idle, past 1.49 and with the +0x17a bit 3 set,
 * pose 0x19 plays, the velocity rests and the node moves on to 020d1350. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;
typedef struct { unsigned f : 8; } B8;
typedef struct { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; } Bits8;
struct Ov252Armour { char pad[0x4e8]; int shapes[16]; };

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int z);
extern Vec3 func_ov252_020d0a8c(int *node);
extern void func_ov107_020c5c54(int actor, Vec3 *at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern u8 func_ov252_020ce0a8(int *state, int kind, Sphere *sphere, void *cyl, void *box);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d1350(void);
extern const Vec3 data_02041dc8;

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov252_020d0f14(int *node)
{
    int *state = (int *)node[1];
    Sphere body;
    Vec3 v;
    Vec3 to;
    Vec3 spot;

    state[0x19] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x88) != 0) {
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x4e4) + 0x190), (Vec3 *)state[2], &to);
        to.y = 0;
        func_01ff8d18(&to, (Vec3 *)(state + 0xf));
        if (func_01ff8d18(&to, &v) > 0x680) {
            func_01ffa724(0x680, &v, &to);
        }
        state[0x16] = func_020050b4(state[0xf], state[0x11]);
    }
    if (state[0x19] > 0x4000 && state[0x27] == 0) {
        spot = func_ov252_020d0a8c(node);
        *(Vec3 *)(state + 0x12) = spot;
        func_ov107_020c5c54(*state, (Vec3 *)(state + 0x12));
        state[0x29] = 1;
        func_ov107_020c9264(*state, 0x18, 0);
        func_ov107_020c0b90(*state, 0x32, *(Vec3 *)state[2], 0);
        state[0x27] = 1;
        *(int *)(*state + 0x584) = 1;
    }
    if (*((u8 *)state + 0x88) == 2 && state[0x19] >= 0x6000) {
        state[0x19] = 0;
        {
            u16 hw = *(u16 *)(*state + 0x60);
            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 0x18) << 0x18) >> 0x10);
        }
        *((u8 *)state + 0x88) -= 1;
    }
    if (*((u8 *)state + 0x88) == 1) {
        v = *(Vec3 *)(state + 0x12);
        v.y = 0x1c0;
        state[0x19] = 0;
        *((u8 *)state + 0x88) -= 1;
        func_ov107_020c9264(*state, 0x31, 0);
        func_ov107_020c9264(*state, 0x35, 0);
        func_ov107_020c0b90(*state, 0xa, v, 0);
        func_ov107_020c5af8(*state, 0x148, 0xa, &v);
        func_ov107_020c0b90(*state, 0x32, v, 0);
        if (state[0x2b] == 0) {
            {
                u16 hw = *(u16 *)(*state + 0x60);
                *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                    ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
            }
            ((B8 *)(((struct Ov252Armour *)*state)->shapes[*((u8 *)state + 0x93) + 3] + 8))->f |= 1;
            *(u8 *)(*state + 0x1c7) = 5;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state[0x19] >= 0x1800 && *((u8 *)state + 0x88) == 0) {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x10) << 0x18) >> 0x10);
    }
    if (*((u8 *)state + 0x88) == 0) {
        state[0x16] = func_020050b4(state[0xf], state[0x11]);
        func_01ffa724(0x400, (Vec3 *)(state + 0xf), (Vec3 *)(state + 0xf));
        if (state[0x29] != 0) {
            VecSet((Vec3 *)(state + 3), state[0xf] * 2, 0x800, state[0x11] * 2);
        } else {
            VecSet((Vec3 *)(state + 3), state[0xf], 0x800, state[0x11]);
        }
        body = *(Sphere *)(*state + 0x74);
        body.nRadius = 0x6800;
        if (func_ov252_020ce0a8(state, 2, &body, 0, 0) != 0) {
            func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
        }
    }
    if (*((u8 *)state + 0x88) != 0 || *(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x19] < 0x17e8) {
        return;
    }
    if (!((Bits8 *)(*state + 0x17a))->b3) {
        return;
    }
    func_ov107_020c9264(*state, 0x19, 0);
    *(Vec3 *)(state + 3) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d1350);
}
