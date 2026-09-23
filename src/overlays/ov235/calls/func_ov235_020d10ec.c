/* Dash tick of an ov235 state: the +0x40 rate is the frame rate x 7.5 and the +0x10 step is the
 * +0x68 direction x 2.0. The segment from the owner's +0x3ac body point (+0x14) along the step is
 * swept over the actor list; every entity whose +0x1b4 kind bit is clear in the +0x63 mask is
 * pushed away from its closest point on the segment (flattened, then raised to 0.5 up, unit
 * length, kind 6). On acceptance the 14-byte message of data_ov235_020d2550 carries the entity's
 * +0x74 point to the owner's +0x24 hook, the entity becomes +0x74, its bit is set and reaction
 * +0x3c8 mode 0xa fires there. The +0x44 timer accumulates the frame rate; past 0.25 the hook
 * receives note 4 of data_ov235_020d24d0, animation 0x21 plays and the tick hands over to
 * func_ov235_020d1484. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef long long fx64;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo; u16 hi; } Cmd4;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_02036304(void *point, Segment *seg, fx64 *outDist);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov235_020d2550;
extern const Cmd4 data_ov235_020d24d0[];
extern void func_ov235_020d1484(int *node);

void func_ov235_020d10ec(int *node)
{
    int obj;
    int *state = (int *)node[1];
    Segment seg;
    int hits[4];
    fx64 t;
    Cmd4 note;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int n;
    int i;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 4;
    func_01ffa724(0x2000, (Vec3 *)(state + 0x1a), (Vec3 *)(state + 4));
    seg.p0 = *(Vec3 *)(*(int *)(*state + 0x3ac) + 0x14);
    seg.nLength = func_01ff8d18((Vec3 *)(state + 4), &seg.dir);
    seg.nRadius = 0xc00;
    n = func_ov107_020c8f44(*state, &seg, hits);
    i = 0;
    if (n > 0) {
        do {
            Vec3 push = {0, 0, 0};
            Vec3 proj;
            Cmd14 msg;

            obj = hits[i];
            if ((*((u8 *)state + 0x63) & (1 << *(u8 *)(obj + 0x1b4))) == 0) {
                func_02036304((void *)(obj + 0x74), &seg, &t);
                proj.x = (int)((t * seg.dir.x + 0x80000000LL) >> 32);
                proj.y = (int)((t * seg.dir.y + 0x80000000LL) >> 32);
                proj.z = (int)((t * seg.dir.z + 0x80000000LL) >> 32);
                VEC_Add(&seg.p0, &proj, &proj);
                VEC_Subtract((void *)(obj + 0x74), &proj, &push);
                push.y = 0;
                func_01ff8d18(&push, &push);
                push.y = 0x800;
                func_01ff8d18(&push, &push);
                func_01ffa724(0x1000, &push, &push);
                if (func_ov107_020ca918(hits[i], *state, *state, 6, &push, 0) != 0) {
                    msg = data_ov235_020d2550;
                    PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
                    PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
                    PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
                    if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
                    }
                    state[0x1d] = hits[i];
                    *((u8 *)state + 0x63) |= 1 << *(u8 *)(hits[i] + 0x1b4);
                    func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3c8), 0xa, (void *)(obj + 0x74));
                }
            }
        } while (++i < n);
    }
    state[0x11] += *(int *)(node[0] + 0x2c);
    if (state[0x11] <= 0x400) {
        return;
    }
    {
        Cmd4 *p = &note;

        p->hi = data_ov235_020d24d0[4].hi;
        p->lo = data_ov235_020d24d0[4].lo;
        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
    }
    func_ov107_020c9264(*state, 0x21, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020d1484);
}
