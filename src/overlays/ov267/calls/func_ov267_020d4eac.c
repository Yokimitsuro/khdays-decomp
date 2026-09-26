/* Trail tick of the ov267 enemy's thrown part (byte-identical twin of ov212 020d1294). Bit 7 of
 * the owner's +0x60
 * high byte clears. The owner's +0x74 sphere is queried against the +0x38c body's targets; while
 * nothing is hit, each leg of the three-point +0x40 trail (a box as long as the leg, a third of
 * the owner radius wide, upright) is queried too. The first target the 0.5 push (flattened unit
 * direction from the owner) lands on gets the contact point (owner radius along the direction,
 * plus the push, from the sphere centre): reaction 0/0x4f fires at the +4 point, effect 3 spawns
 * there and sub-state 2 ends the tick. Otherwise the +4 point's step since +0x34 is kept, every
 * 0x300 of the +0x2c timer the trail shifts back and restarts at the point, a 0xb message with the
 * step's heading and the packed point goes through the owner's +0x24 hook, and sub-state 2 ends
 * the tick when the step hits a wall, finds no floor within 0x300, or the +0x20 distance reaches
 * 32.0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { Vec3 c; int r; } Sphere;
typedef struct { Vec3 center; Vec3 axisX; Vec3 axisY; Vec3 axisZ; int extent[3]; } Obb;
typedef struct { u16 id; u8 kind; u8 cmd; Quat q; u8 pos[9]; u8 pad[3]; } Msg32;
struct hw60 { unsigned short lo : 8, hi : 8; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern int func_ov107_020c8eb8(int body, Sphere *src, int *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8df0(int body, Obb *query, int *out);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_020050b4(int y, int x);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void *func_01fff920(void *collision, Vec3 *origin, Vec3 *dir);
extern int *func_01fff8e8(void *collision, Vec3 *origin, Vec3 *dir, int radius, void *ignore);
extern int VEC_Mag(const Vec3 *v);
extern const Vec3 data_02042264;

/* The three-point trail at +0x40 of the state. Codegen notes: the leg's far end is addressed as a
 * byte offset from the trail (`i * 12 + 12`, an offset induction variable next to the walker of
 * pts[i]) and the shift loop reads the trail as a member of the state view; the loop tests
 * `i - 1 >= 0` (subs/bpl). */
struct TrailState { char pad[0x40]; Vec3 pts[3]; };
void func_ov267_020d4eac(int *node)
{
    int *state = (int *)node[1];
    int i;
    int n;
    int world = *(int *)(*state + 4);
    Sphere sphere;
    Vec3 d;
    Quat quat;
    int hits[4];
    Obb obb;
    Vec3 dir;
    Vec3 at;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int *floor;

    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    sphere = *(Sphere *)(*state + 0x74);
    n = func_ov107_020c8eb8(*(int *)(*state + 0x38c), &sphere, hits);
    for (i = 0; n == 0 && i + 1 < 3; i++) {
        Vec3 *cur = &((Vec3 *)(state + 0x10))[i];

        VEC_Subtract((Vec3 *)((char *)(state + 0x10) + (i * 12 + 12)), cur, &d);  /* pts[i + 1] */
        obb.extent[2] = func_01ff8d18(&d, &obb.axisZ) / 2;
        if (obb.extent[2] == 0) {
            break;
        }
        obb.axisY = data_02042264;
        VEC_CrossProduct(&obb.axisY, &obb.axisZ, &obb.axisX);
        obb.extent[0] = obb.extent[1] = *(int *)(*state + 0x80) / 3;
        func_01ffa724(0x800, &d, &obb.center);
        VEC_Add(&obb.center, cur, &obb.center);
        n = func_ov107_020c8df0(*(int *)(*state + 0x38c), &obb, hits);
    }
    for (i = 0; i < n; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &dir);
        func_01ff8d18(&dir, &at);
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        func_01ffa724(0x800, &dir, &dir);
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), 3, &dir, 0) != 0) {
            func_01ffa724(*(int *)(*state + 0x80), &at, &at);
            VEC_Add(&at, &dir, &at);
            VEC_Add(&at, &sphere.c, &at);
            func_ov107_020c5af8(state[0], 0, 0x4f, (void *)state[1]);
            func_ov107_020c0b90(*(int *)(*state + 0x38c), 3, at, 0);
            *(u8 *)(*state + 0x1c7) = 2;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    VEC_Subtract((void *)state[1], (void *)(state + 0xd), &d);
    *(Vec3 *)(state + 0xd) = *(Vec3 *)state[1];
    state[0xb] += *(int *)(*node + 0x2c);
    if (state[0xb] >= 0x300) {
        state[0xb] = 0;
        for (i = 2; i - 1 >= 0; i--) {
            ((struct TrailState *)state)->pts[i] = ((struct TrailState *)state)->pts[i - 1];
        }
        ((struct TrailState *)state)->pts[0] = *(Vec3 *)state[1];
    }
    func_0202f188(&quat, &data_02042264, func_020050b4(-d.x, -d.z));
    {
        Msg32 msg = {0};
        u16 *p = (u16 *)&msg;

        p[0] = *(u16 *)(*state + 2);
        ((u8 *)p)[2] = 5;
        ((u8 *)p)[3] = 0xb;
        {
            Fx32 *p = (Fx32 *)state[1];
            PACK(msg, scratchX, p[0], 0x14);
            PACK(msg, scratchY, p[1], 0x17);
            PACK(msg, scratchZ, p[2], 0x1a);
        }
        msg.q = quat;
        if (*(void (**)(int, Msg32 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Msg32 *, int))(*state + 0x24))(*state, &msg, 0x20);
        }
    }
    if (func_01fff920(*(void **)(world + 0x7c), (Vec3 *)state[1], &d) != 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    floor = func_01fff8e8(*(void **)(world + 0x7c), (Vec3 *)state[1], &d, 0x300, 0);
    if (floor != 0 && floor[2] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[8] += VEC_Mag(&d);
    if (state[8] < 0x20000) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
