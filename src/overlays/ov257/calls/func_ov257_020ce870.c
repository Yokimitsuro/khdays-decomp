/* Bite tick of an ov257 state: the +0x54 timer accumulates the frame rate and at 0.2 reaction
 * +0x408 mode 0x16 fires once at the +4 point (+0x76). The +0x40 rate is the frame rate x 3;
 * without a nearest target (020cab14, kept in +0x60) sub-state 2 is requested, otherwise the +0x10
 * step heads for it (func_ov257_020ccf98, never past the gap). The +0x44 timer accumulates the
 * frame rate; between 0.27 and 0.73 the four segments of the owner's +0x3c0 parts (+0x78), moved
 * by the step and with a doubled radius, are swept over the actor list: every entity whose +2 id
 * bit is clear in the +0x73 mask is pushed 0.25 along the +0x1c heading; on acceptance the 14-byte
 * message of data_ov257_020d32a2 carries its +0x74 point to the owner's +0x24 hook, its bit is set
 * and reaction +0x408 mode 9 fires there. Once the +0xc idle byte clears, animation 0xe plays, the
 * +0x3d0 part plays motion 0xd, +0x44, +0x73 and +0x76 clear and the tick hands over to
 * func_ov257_020cec5c. */
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

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020cab14(int obj, int kind);
extern int func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov257_020d32a2;
extern const Vec3 data_02042258;
extern void VEC_Add(const void *a, const void *b, void *out);
extern void func_ov257_020cec5c(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov257_020ce870(int *node)
{
    int i;
    int obj;
    int *pHits;
    int *state = (int *)node[1];
    int k;
    int n;
    int speed;
    Vec3 dir;
    int hits[4];
    Segment seg;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;

    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x76) == 0 && state[0x15] >= 0x333) {
        func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x16, (void *)state[1]);
        *((u8 *)state + 0x76) = 1;
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[0x18] = func_ov107_020cab14(*state, 0);
    if (state[0x18] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    n = func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    if (n < speed) {
        speed = n;
    }
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x11] += *(int *)(node[0] + 0x2c);
    if (state[0x11] > 0x444 && state[0x11] < 0xbbb) {
        for (k = 0; k < 4; k++) {
            seg = *(Segment *)(((int *)*state)[0xf0 + k] + 0x78);
            VEC_Add(&seg.p0, state + 4, &seg.p0);
            seg.nRadius = FX_Mul(seg.nRadius, 0x2000);
            n = func_ov107_020c8f44(*state, &seg, hits);
            i = 0;
            if (i < n) {
                pHits = hits;
                do {
                    Vec3 push;
                    Cmd14 msg;

                    obj = pHits[i];
                    if ((*((u8 *)state + 0x73) & (1 << *(u16 *)(obj + 2))) == 0) {
                        func_0202f384(&push, state + 7, &data_02042258);
                        func_01ffa724(0x400, &push, &push);
                        if (func_ov107_020ca918(pHits[i], *state, *state, 0, &push, 0) != 0) {
                            msg = data_ov257_020d32a2;
                            PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
                            PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
                            PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
                            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
                            }
                            *((u8 *)state + 0x73) |= 1 << *(u16 *)(pHits[i] + 2);
                            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x408), 9, (void *)(obj + 0x74));
                        }
                    }
                    i++;
                } while (i < n);
            }
        }
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xe, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0xd, 0);
    state[0x11] = 0;
    *((u8 *)state + 0x73) = 0;
    *((u8 *)state + 0x76) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020cec5c);
}
