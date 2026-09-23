/* Rise entry of the ov210 enemy (x3 with ov211/ov282): raises bits 2, 3 and 6 of the owner's
 * +0x60 high byte and bit 0 of +0x1ae, clears bit 0 of the +0x3b0 body's +8 low byte, plays
 * animation 6, clears the +0x2c/+0x30 timers and keeps the +4 point at +0x34. The overlay's
 * 14-byte message (data_ov211_020d657e, flag 2) carries the point packed as 24-bit values to the
 * owner's +0x24 hook; the +0x60 timer and the +0x66 byte clear and the tick hands over to
 * func_ov211_020d5948. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 h[7]; } Cmd14;

struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov211_020d657e;
extern void func_ov211_020d5948(int *node);

void func_ov211_020d57a0(int *node)
{
    int *state = (int *)node[1];
    Cmd14 msg;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 *pPos;
    u16 v;

    v = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x4c) << 0x18) >> 0x10));
    *(u16 *)(*state + 0x1ae) |= 1;
    ((struct w8 *)(*(int *)(*state + 0x3b0) + 8))->lo &= ~1;
    func_ov107_020c9264(*state, 6, 0);
    state[0xb] = 0;
    state[0xc] = 0;
    *(Vec3 *)(state + 0xd) = *(Vec3 *)state[1];
    msg = data_ov211_020d657e;
    pPos = (Fx32 *)state[1];
    PACK(msg, scratchX, pPos[0], 5);
    PACK(msg, scratchY, pPos[1], 8);
    PACK(msg, scratchZ, pPos[2], 11);
    ((u8 *)&msg)[4] = 2;
    if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
    }
    state[0x18] = 0;
    *(u8 *)((char *)state + 0x66) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov211_020d5948);
}
