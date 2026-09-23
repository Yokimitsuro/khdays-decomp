/* Charge tick of the ov210 enemy (x3 with ov211/ov282). The +0x14 step is the +0x44 direction
 * scaled 0.8125; the +0x3b4 body's +0x78 segment moved by it is swept over the actor list. Every
 * entity whose +0x1b4 kind bit is clear in the +0x67 mask is pushed 0.5 along the flattened unit
 * direction from the body's +4 point (kind 1); on acceptance the overlay's 14-byte message
 * (data_ov211_020d6562, low nibble of byte 4 = 6, high nibble cleared) carries the entity's +0x74
 * point to the owner's +0x24 hook, reaction 0/0x51 fires there and the bit is set. The +0x2c
 * timer accumulates the rate; once the owner reports contact (+0x17a bits 0, 1 or 3) or the
 * timer reaches 1.0, bit 6 of the +0x60 high byte clears, animation 9 plays and the tick hands
 * over to func_ov211_020d3d34. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
struct Nib { u8 lo : 4, hi : 4; };
typedef struct { u16 id; u8 kind; u8 cmd; struct Nib flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

struct hw60 { unsigned short lo : 8, hi : 8; };
struct Bits17a { u8 b0 : 1, b1 : 1, b2 : 1, b3 : 1; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov211_020d6562;
extern void func_ov211_020d3d34(int *node);

void func_ov211_020d3a24(int *node)
{
    int *state = (int *)node[1];
    Segment seg;
    int hits[4];
    Vec3 push;
    Cmd14 msg;
    Cmd14 tmpl;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int n;
    int i;

    func_01ffa724(0xd00, (Vec3 *)(state + 0x11), (Vec3 *)(state + 5));
    seg = *(Segment *)(*(int *)(*state + 0x3b4) + 0x78);
    VEC_Add(&seg.p0, (Vec3 *)(state + 5), &seg.p0);
    n = func_ov107_020c8f44(*state, &seg, hits);
    i = 0;
    if (n > 0) {
        tmpl = data_ov211_020d6562;
        do {
            if (((*(u8 *)((char *)state + 0x67) >> *(u8 *)(hits[i] + 0x1b4)) & 1) == 0) {
                VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*(int *)(*state + 0x3b4) + 4), &push);
                push.y = 0;
                func_01ff8d18(&push, &push);
                func_01ffa724(0x800, &push, &push);
                if (func_ov107_020ca918(hits[i], *state, *state, 1, &push, 0) != 0) {
                    msg = tmpl;
                    PACK(msg, scratchX, *(Fx32 *)(hits[i] + 0x74), 5);
                    PACK(msg, scratchY, *(Fx32 *)(hits[i] + 0x78), 8);
                    PACK(msg, scratchZ, *(Fx32 *)(hits[i] + 0x7c), 11);
                    msg.flag.lo = 6;
                    msg.flag.hi = 0;
                    if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
                    }
                    func_ov107_020c5af8(*state, 0, 0x51, (void *)(hits[i] + 0x74));
                    *(u8 *)((char *)state + 0x67) |= 1 << *(u8 *)(hits[i] + 0x1b4);
                }
            }
        } while (++i < n);
    }
    state[0xb] += *(int *)(*node + 0x2c);
    if (((struct Bits17a *)(*state + 0x17a))->b0 != 0 || ((struct Bits17a *)(*state + 0x17a))->b1 != 0
        || ((struct Bits17a *)(*state + 0x17a))->b3 != 0 || state[0xb] >= 0x1000) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
        func_ov107_020c9264(*state, 9, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov211_020d3d34);
    }
}
