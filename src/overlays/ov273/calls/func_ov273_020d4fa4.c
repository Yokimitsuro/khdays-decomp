/* Sweep-pass hit test (called by the sweep pass ticks 020d49cc / 020d4b54): the segment of the
 * actor's +0x390 part (+0x78) is swept over the actor list; every entity whose +2 id bit is clear
 * in the +0x84 mask is pushed 0.375 away from its closest point on the segment (02036304), never
 * downwards, on behalf of the actor's +0x384 rider (kind 2); on acceptance the 14-byte message
 * data_ov273_020d6b6c carries its +0x74 point to the actor's +0x24 hook, its bit is set and the
 * rider's reaction 0x162 mode 7 fires at the +4 point. */
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

typedef long long fx64;

extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_02036304(void *point, Segment *seg, fx64 *outDist);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const Cmd14 data_ov273_020d6b6c;

static inline int FX_MulHigh64(fx64 a, int b)
{
    return (int)((a * b + 0x80000000LL) >> 32);
}

void func_ov273_020d4fa4(int *state)
{
    int obj;
    fx64 dist;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int hits[4];
    Segment seg;
    Vec3 point;
    Vec3 push;
    int n;
    int i;

    seg = *(Segment *)(*(int *)(*state + 0x390) + 0x78);
    n = func_ov107_020c8f44(*state, &seg, hits);
    for (i = 0; i < n; i++) {
        Cmd14 msg;

        obj = hits[i];
        if ((*((u8 *)state + 0x84) & (1 << *(u16 *)(obj + 2))) != 0) {
            continue;
        }
        func_02036304((void *)(obj + 0x74), &seg, &dist);
        point.x = FX_MulHigh64(dist, seg.dir.x);
        point.y = FX_MulHigh64(dist, seg.dir.y);
        point.z = FX_MulHigh64(dist, seg.dir.z);
        VEC_Add(&seg.p0, &point, &point);
        VEC_Subtract((void *)(obj + 0x74), &point, &push);
        if (push.y < 0) {
            push.y = 0;
        }
        func_01ff8d18(&push, &push);
        func_01ffa724(0x600, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 2, &push, 0) == 0) {
            continue;
        }
        msg = data_ov273_020d6b6c;
        PACK(msg, scratchX, *(Fx32 *)(hits[i] + 0x74), 5);
        PACK(msg, scratchY, *(Fx32 *)(hits[i] + 0x78), 8);
        PACK(msg, scratchZ, *(Fx32 *)(hits[i] + 0x7c), 11);
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        *((u8 *)state + 0x84) |= 1 << *(u16 *)(hits[i] + 2);
        func_ov107_020c5af8(*(int *)(state[0] + 0x384), 0x162, 7, (void *)state[1]);
    }
}
