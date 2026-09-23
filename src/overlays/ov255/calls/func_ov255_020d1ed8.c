/* Flight tick of the ov255 homing shot: the +8 step is the forward axis turned by the +0x20
 * orientation times the +0x18 speed, plus a 0.125 sway along its side axis at the +0x24 phase (the
 * phase advances by 2*pi/32 of the frame step, wrapping at pi). With a nearest target the shot
 * turns towards its +0x1d8 part's point by the +0x14 rate while it is ahead (dot >= -0.5) and its
 * speed eases towards 1/16 plus a quarter of that dot; otherwise towards 0.125. The turn rate eases
 * towards the frame rate x 6. The shot's 0.25 sphere hits the actor list: the first accepted hit
 * (kind 6, pushed along the step) sends its +0x74 point in the 14-byte message of
 * data_ov255_020d2ba8 to the owner's +0x24 hook, spawns effect 3, clears +0x1c, fires the owner's
 * reaction 0x15 there and hands over to func_ov255_020d24bc. Hitting a plain wall on the way from
 * the owner's +0x39c point reports that point (data_ov255_020d2bb6) and ends the shot, as does
 * running for more than 5.0 (+0x1c); ending clears +0x1c and requests the owner's sub-state 0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { Vec3 c; int r; } Sphere;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *a, const Vec3 *b);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_0202f55c(void *a, int t, void *b, Quat *out);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int id, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern int *func_01fff8e8(void *collision, void *from, Vec3 *dir, int radius, int flag);
extern const Vec3 data_02042258;
extern const short data_0203d210[];
extern const Cmd14 data_ov255_020d2ba8;
extern const Cmd14 data_ov255_020d2bb6;
extern const Vec3 data_02041dc8;
extern void func_ov255_020d24bc(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov255_020d1ed8(int *node)
{
    int obj;
    int *pHits;
    int *h = (int *)node[1];
    Vec3 fwd;
    Vec3 side;
    Sphere sph;
    int hits[4];
    Vec3 d;
    Quat q;
    Vec3 push;
    Cmd14 msg;
    Vec3 wallDir;
    Cmd14 wallMsg;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 wallZ;
    Fx32 wallY;
    Fx32 wallX;
    int target;
    int dot;
    int n;
    int i;
    int *wall;

    func_0202f384(&fwd, (void *)h[8], &data_02042258);
    func_01ffa724(h[6], &fwd, (Vec3 *)(h + 2));
    *(int *)h[9] += FX_Mul(*(int *)(node[0] + 0x2c) * 30, 0x6488) / 32;
    if (*(int *)h[9] > 0x6488 / 2) {
        *(int *)h[9] -= 0x6488;
    }
    side.x = data_0203d210[ANG2IDX(*(int *)h[9]) * 2];
    side.y = data_0203d210[ANG2IDX(*(int *)h[9]) * 2 + 1];
    side.z = 0;
    func_0202f384(&side, (void *)h[8], &side);
    func_01ffa724(0x200, &side, &side);
    VEC_Add(h + 2, &side, h + 2);
    n = func_ov107_020cab14(h[0], 0);
    if (n != 0) {
        VEC_Subtract((void *)(*(int *)(n + 0x1d8) + 4), (void *)h[1], &d);
        func_01ff8d18(&d, &d);
        func_0202ed60(&q, &data_02042258, &d);
        dot = VEC_DotProduct(&fwd, &d);
        if (dot >= -0x800) {
            func_0202f55c((void *)h[8], h[5], (void *)h[8], &q);
        }
        if (dot < 0) {
            dot = 0;
        }
        h[6] += (FX_Mul(dot, 0x400) + 0x100 - h[6]) / 10;
    } else {
        h[6] += (0x200 - h[6]) / 10;
    }
    h[5] += (*(int *)(node[0] + 0x2c) * 30 / 5 - h[5]) / 20;
    sph.c = *(Vec3 *)h[1];
    sph.r = 0x400;
    n = func_ov107_020c8eb8(h[0], &sph, hits);
    if (n != 0) {
        i = 0;
        if (i < n) {
            pHits = hits;
            do {
                obj = pHits[i];
                func_01ffa724(0x1000, (Vec3 *)(h + 2), &push);
                if (func_ov107_020ca918(pHits[i], h[0], *(int *)(h[0] + 0x384), 6, &push, 0) != 0) {
                    msg = data_ov255_020d2ba8;
                    PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
                    PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
                    PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
                    if (*(void (**)(int, Cmd14 *, int))(h[0] + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(h[0] + 0x24))(h[0], &msg, 0xe);
                    }
                    func_ov107_020c0b90(h[0], 3, data_02041dc8, 0);
                    h[7] = 0;
                    func_ov107_020c5af8(h[0], (short)*(int *)(*(int *)(h[0] + 0x384) + 0x3f8), 0x15, (void *)(obj + 0x74));
                    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020d24bc);
                    return;
                }
                i++;
            } while (i < n);
        }
    }
    {
        int world = *(int *)(h[0] + 4);

        VEC_Subtract((void *)h[1], (void *)(h[0] + 0x39c), &wallDir);
        wall = func_01fff8e8(*(void **)(world + 0x7c), (void *)(h[0] + 0x39c), &wallDir, 0x400, 0);
    }
    if (wall != 0 && wall[2] == 0) {
        Vec3 *at;

        wallMsg = data_ov255_020d2bb6;
        at = (Vec3 *)(h[0] + 0x39c);
        PACK(wallMsg, wallX, *(Fx32 *)&at->x, 5);
        PACK(wallMsg, wallY, *(Fx32 *)&at->y, 8);
        PACK(wallMsg, wallZ, *(Fx32 *)&at->z, 11);
        if (*(void (**)(int, Cmd14 *, int))(h[0] + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(h[0] + 0x24))(h[0], &wallMsg, 0xe);
        }
        h[7] = 0;
        *(signed char *)(h[0] + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    h[7] += *(int *)(node[0] + 0x2c);
    if (h[7] <= 0x5000) {
        return;
    }
    h[7] = 0;
    *(signed char *)(h[0] + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
