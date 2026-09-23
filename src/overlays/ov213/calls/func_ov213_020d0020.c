/* Tail-sweep tick: the owner's +0x3ec part is the sweeping limb. Until the +0x6a flag is set the
 * +0x70 timer accumulates the frame rate and at 0.8 the flag is set and reaction 0x122 mode 0xe fires
 * at the part point (+0x14). The +0x1c timer accumulates the frame rate; between 0.77 and 0.97 a
 * 1.4-long, 1.0-thick segment from the part point along the part's +4 rotation (data_02042258) is
 * swept over the actor list: every entity whose +2 id bit is clear in the +0x69 mask is pushed 1.0
 * away from the owner, never downwards (kind 0); on acceptance the 14-byte message
 * data_ov213_020d2eac carries its +0x74 point to the owner's +0x24 hook, its bit is set and
 * reaction 0x122 mode 7 fires there. Once the +8 idle byte clears, pose 5 is requested. */
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

extern const Vec3 data_02042258;
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov213_020d2eac;

void func_ov213_020d0020(int *node)
{
    int obj;
    int *state = (int *)node[1];
    int part = *(int *)(*state + 0x3ec);
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int hits[4];
    Segment seg;
    Vec3 push;
    int n;
    int i;

    if (*((u8 *)state + 0x6a) == 0) {
        state[0x1c] += *(int *)(node[0] + 0x2c);
        if (state[0x1c] >= 0xccc) {
            *((u8 *)state + 0x6a) = 1;
            func_ov107_020c5af8(*state, 0x122, 0xe, (void *)(part + 0x14));
        }
    }
    state[7] += *(int *)(node[0] + 0x2c);
    n = state[7];
    if (n > 0xc44 && n < 0xf77) {
        seg.p0 = *(Vec3 *)(part + 0x14);
        func_0202f384(&seg.dir, (void *)(part + 4), &data_02042258);
        seg.nLength = 0x1666;
        seg.nRadius = 0x1000;
        n = func_ov107_020c8f44(*state, &seg, hits);
        for (i = 0; i < n; i++) {
            Cmd14 msg;

            obj = hits[i];
            if ((*((u8 *)state + 0x69) & (1 << *(u16 *)(obj + 2))) != 0) {
                continue;
            }
            VEC_Subtract((void *)(obj + 0x74), (void *)(*state + 0x74), &push);
            if (push.y < 0) {
                push.y = 0;
            }
            func_01ff8d18(&push, &push);
            func_01ffa724(0x1000, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 0, &push, 0) == 0) {
                continue;
            }
            msg = data_ov213_020d2eac;
            PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
            PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
            PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            *((u8 *)state + 0x69) |= 1 << *(u16 *)(hits[i] + 2);
            func_ov107_020c5af8(*state, 0x122, 7, (void *)(obj + 0x74));
        }
    }
    if (*(u8 *)state[2] != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 5;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
