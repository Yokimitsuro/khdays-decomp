/* Rise-and-strike entry of the ov210 enemy (x3 with ov211/ov282): raises bits 3 and 6 of the
 * owner's +0x60 high byte and bit 0 of +0x1ae, clears bit 0 of the +0x3b0 body's +8 low byte and
 * plays animation 0x19. The +0x2c/+0x30 timers clear, the overlay's 14-byte message
 * (data_ov210_020d470a, flag 2) carries the +4 point raised 6.0, then the third 4-byte command of
 * data_ov210_020d46ec (kind 5, command 7) goes to the owner's +0x24 hook. Reaction 0x117 mode 6
 * fires at the +4 point with the +0x64 byte raised around it and the tick hands over to
 * func_ov210_020d2230. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 h[7]; } Cmd14;

struct w8 { unsigned int lo : 8, rest : 24; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const u16 data_ov210_020d46ec[];
extern const Cmd14 data_ov210_020d470a;
extern void func_ov210_020d2230(int *node);

void func_ov210_020d203c(int *node)
{
    int *state = (int *)node[1];
    Vec3 raw;
    Cmd14 msg;
    u16 cmd[2];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    u16 v;

    v = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 0x48) << 0x18) >> 0x10));
    *(u16 *)(*state + 0x1ae) |= 1;
    ((struct w8 *)(*(int *)(*state + 0x3b0) + 8))->lo &= ~1;
    func_ov107_020c9264(*state, 0x19, 0);
    state[0xb] = 0;
    state[0xc] = 0;
    msg = data_ov210_020d470a;
    raw = *(Vec3 *)state[1];
    raw.y += 0x6000;
    PACK(msg, scratchX, *(Fx32 *)&raw.x, 5);
    PACK(msg, scratchY, *(Fx32 *)&raw.y, 8);
    PACK(msg, scratchZ, *(Fx32 *)&raw.z, 11);
    ((u8 *)&msg)[4] = 2;
    if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
    }
    {
        u16 *p = cmd;
        p[1] = data_ov210_020d46ec[5];
        p[0] = data_ov210_020d46ec[4];
        if (*(void (**)(int, u16 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, u16 *, int))(*state + 0x24))(*state, p, 4);
        }
    }
    *(u8 *)((char *)state + 0x64) = 1;
    func_ov107_020c5af8(*state, 0x117, 6, (void *)state[1]);
    *(u8 *)((char *)state + 0x64) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov210_020d2230);
}
