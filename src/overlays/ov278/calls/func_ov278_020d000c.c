/* Tail-sweep tick: the +0x28 timer accumulates the frame rate; the actor's +0x1ae bit 0 clears
 * inside the (0x2111, 0x8d55) window and is set outside it. For the first 0.5 a cylinder at the
 * +0x34 point raised by 0.5 (world axes, radius growing to 5.0 with t) sweeps the actor list: each
 * entity that accepts a kind-3 hit pushed 0.5 away from the centre gets the overlay's 14-byte
 * message (its kind, its +0x74 position with y raised by 0x800) through the actor's +0x24 hook,
 * its slot in the +0x4c hit table and reaction 0/0x53 at that point. Past 0x8d55 reaction
 * 0x166/0x12 fires once at the +0x38 point (+0x51). Once the +4 item's +0xad byte clears the next
 * move is 10 when the +0x3bd flag is up, else 8 (consuming +0x52 bit 1) or 2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis[3]; int radius; int flag; } Cyl;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Msg14 { u16 h[7]; };
struct Bits52 { u8 b0 : 1; u8 b1 : 1; };

struct Ov278Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov278Actor *self, void *msg, int size);
};

extern int FX_Inv(int num, int den);
extern int func_ov107_020c8fd0(int owner, Cyl *cyl, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int a, int id, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const struct Msg14 data_ov278_020d6380;

#define PACK3(msg, base, v) \
    ((u8 *)(msg))[(base)] = (u8)(((u32)(v) >> 0x10 & 0x7f) | ((u32)(v) >> 0x18 & 0x80)); \
    ((u8 *)(msg))[(base) + 1] = (u8)((u32)(v) >> 8); \
    ((u8 *)(msg))[(base) + 2] = (u8)(v)

void func_ov278_020d000c(int *node)
{
    int *state = (int *)node[1];
    Cyl cyl;
    int hits[4];
    Vec3 d;
    Vec3 raw;
    struct Msg14 msg;
    struct Msg14 tmpl;
    FxVec vContact;
    int i;
    int nHits;
    int t;

    state[0xa] += *(int *)(node[0] + 0x2c);
    if (state[0xa] > 0x2111 && state[0xa] < 0x8d55) {
        *(u16 *)(*state + 0x100 + 0xae) &= ~1;
    } else {
        *(u16 *)(*state + 0x100 + 0xae) |= 1;
    }
    if (state[0xa] < 0x800) {
        t = FX_Inv(state[0xa], 0x800);
        if (t > 0x1000) {
            t = 0x1000;
        }
        cyl.pos = *(Vec3 *)state[0xd];
        cyl.pos.y += 0x800;
        cyl.axis[0] = data_02042270;
        cyl.axis[1] = data_02042258;
        cyl.axis[2] = data_02042264;
        cyl.radius = t * 5;
        cyl.flag = 1;
        nHits = func_ov107_020c8fd0(*state, &cyl, hits);
        i = 0;
        if (nHits > 0) {
            tmpl = data_ov278_020d6380;
            do {
                VEC_Subtract((void *)(hits[i] + 0x74), &cyl.pos, &d);
                func_01ff8d18(&d, &d);
                func_01ffa724(0x800, &d, &d);
                if (func_ov107_020ca918(hits[i], *state, *state, 3, &d, 0) != 0) {
                    msg = tmpl;
                    raw = *(Vec3 *)(hits[i] + 0x74);
                    raw.y += 0x800;
                    vContact.x = *(Fx32 *)&raw.x;
                    PACK3(&msg, 5, vContact.x.value);
                    vContact.y = *(Fx32 *)&raw.y;
                    PACK3(&msg, 8, vContact.y.value);
                    vContact.z = *(Fx32 *)&raw.z;
                    PACK3(&msg, 11, vContact.z.value);
                    ((u8 *)&msg)[4] = *(u8 *)(hits[i] + 0x1b4);
                    if (((struct Ov278Actor *)*state)->pfnMessage != 0) {
                        ((struct Ov278Actor *)*state)->pfnMessage((struct Ov278Actor *)*state, &msg, 0xe);
                    }
                    ((u8 *)state + 0x4c)[*(u8 *)(hits[i] + 0x1b4)] = 1;
                    func_ov107_020c5af8(*state, 0, 0x53, &raw);
                }
            } while (++i < nHits);
        }
    }
    if (*((u8 *)state + 0x51) == 0 && state[0xa] >= 0x8d55) {
        *((u8 *)state + 0x51) = 1;
        func_ov107_020c5af8(*state, 0x166, 0x12, (void *)state[0xe]);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*(u8 *)(*state + 0x3bd) != 0) {
        *(signed char *)(*state + 0x1c7) = 10;
    } else if (!((struct Bits52 *)((u8 *)state + 0x52))->b1) {
        *(signed char *)(*state + 0x1c7) = 2;
    } else {
        ((struct Bits52 *)((u8 *)state + 0x52))->b1 = 0;
        *(signed char *)(*state + 0x1c7) = 8;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
