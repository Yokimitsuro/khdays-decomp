/* Claw-swipe tick: reads the frame of the actor's +0x384 rider animation 0 (0203bec0). Each of the
 * two claws whose +0x3bc slot is armed sweeps inside its window (claw 0 frames 3..12, claw 1 frames
 * 21..32): the segment of the claw's part (+0x3b0 slot, +0x78) with a doubled radius is swept over
 * the actor list and every entity in it is pushed 1.0 away from the claw's +4 point, lifted by
 * 1/16 (kind 4, on behalf of the +0x394 object); on acceptance the 14-byte message
 * data_ov278_020d63d4 carries its +0x74 point raised by 0.5 and its +0x1b4 byte to the +0x394
 * object's +0x24 hook, and reaction 0x166 mode 0xd fires at that raised point. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern int func_0203bec0(int part, int channel);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const Cmd14 data_ov278_020d63d4;

void func_ov278_020d33f4(int *node)
{
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int hits[4];
    Segment seg;
    Vec3 push;
    Vec3 raw;
    int frame;
    int k;
    int n;
    int i;

    frame = func_0203bec0(*(int *)(*state + 0x384), 0);
    for (k = 0; k < 2; k++) {
        if (((short *)*state)[0x1de + k] == 0) {
            continue;
        }
        if (!((k == 0 && frame >= 0x3000 && frame <= 0xc000) || (k == 1 && frame >= 0x15000 && frame <= 0x20000))) {
            continue;
        }
        seg = *(Segment *)(*(int *)((int *)*state)[0xec + k] + 0x78);
        n = seg.nRadius;
        seg.nRadius = n << 1;
        n = func_ov107_020c8f44(*state, &seg, hits);
        for (i = 0; i < n; i++) {
            Cmd14 msg;

            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*(int *)((int *)*state)[0xec + k] + 4), &push);
            func_01ff8d18(&push, &push);
            func_01ffa724(0x1000, &push, &push);
            push.y = 0x100;
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x394), 4, &push, 0) == 0) {
                continue;
            }
            msg = data_ov278_020d63d4;
            raw = *(Vec3 *)(hits[i] + 0x74);
            raw.y += 0x800;
            PACK(msg, scratchX, *(Fx32 *)&raw.x, 5);
            PACK(msg, scratchY, *(Fx32 *)&raw.y, 8);
            PACK(msg, scratchZ, *(Fx32 *)&raw.z, 11);
            msg.flag = *(u8 *)(hits[i] + 0x1b4);
            if (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x394) + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x394) + 0x24))(*(int *)(*state + 0x394), &msg, 0xe);
            }
            func_ov107_020c5af8(*state, 0x166, 0xd, &raw);
        }
    }
}
