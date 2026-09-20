/* Swing sweep for ov114: probe the forward volume, notify each accepted hit,
 * spawn reaction 0x112 at the target position, and report whether any hit was accepted. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;

struct Msg {
    u16 h[7];
};

struct Ov114Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov114Actor *self, struct Msg *msg, int size);
    char pad028[0x74 - 0x28];
    Vec3 position;
};

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8eb8(struct Ov114Actor *owner, Sphere *sphere, struct Ov114Actor **out);
extern int func_ov107_020ca918(struct Ov114Actor *hit, struct Ov114Actor *a, struct Ov114Actor *b, int kind, const Vec3 *push, int z);
extern char **OS_IsThreadAvailable_0x020c9848(void);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_ov107_020c5af8(struct Ov114Actor *owner, u16 a, u16 id, Vec3 *pos);
extern const short data_0203d210[];
extern const struct Msg data_ov277_020d3740;

#pragma opt_dead_assignments off
int func_ov277_020d1d00(int *state, int kind)
{
    Vec3 fwd;
    Vec3 push;
    Sphere sphere;
    struct Ov114Actor *hits[4];
    Vec3 impact;
    struct Msg msg;
    struct Msg tmpl;
    FxVec vContact;
    struct Ov114Actor *hit;
    struct Msg *pMsg;
    int idx;
    int n;
    int i;
    int flip;
    int hitAny;
    int command;
    long long scaledAngle;

    scaledAngle = 0x28BE60DB9391LL * state[5] + 0x80000000000LL;
    idx = (unsigned short)(scaledAngle >> 44);
    fwd.x = data_0203d210[(idx >> 4) << 1];
    fwd.y = 0;
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];
    hitAny = (int)scaledAngle;
    hitAny = 0;
    i = 0;
    n = 0;
    pMsg = 0;
    func_01ffa724(0x400, &fwd, &push);
    func_01ffa724(0xc00, &fwd, &sphere.pos);
    VEC_Add((Vec3 *)state[2], &sphere.pos, &sphere.pos);
    sphere.radius = 0x600;
    n = func_ov107_020c8eb8((struct Ov114Actor *)*state, &sphere, hits);
    i = hitAny;
    if (n > 0) {
        tmpl = data_ov277_020d3740;
        do {
            if (func_ov107_020ca918(hits[i], (struct Ov114Actor *)*state, (struct Ov114Actor *)*state, kind, &push, 0) != 0) {
                msg = tmpl;
                hit = hits[i];
                pMsg = &msg;
                flip = kind == 1 ? 1 : 0;
                if (VEC_DotProduct((Vec3 *)(*OS_IsThreadAvailable_0x020c9848() + 0x7c), &fwd) > 0) {
                    flip = (flip + 1) & 1;
                }
                if (flip == 0) {
                    command = 0;
                } else {
                    command = 0;
                    command = 1;
                }
                ((u8 *)pMsg)[3] = command;
                VEC_Add(&sphere.pos, &push, &impact);
                vContact.x = *(Fx32 *)&hit->position.x;
                ((u8 *)&msg)[5] = (u8)(((u32)vContact.x.value >> 16 & 0x7f) | ((u32)vContact.x.value >> 24 & 0x80));
                ((u8 *)&msg)[6] = (u8)((u32)vContact.x.value >> 8);
                ((u8 *)&msg)[7] = (u8)vContact.x.value;
                vContact.y = *(Fx32 *)&hit->position.y;
                ((u8 *)&msg)[8] = (u8)(((u32)vContact.y.value >> 16 & 0x7f) | ((u32)vContact.y.value >> 24 & 0x80));
                ((u8 *)&msg)[9] = (u8)((u32)vContact.y.value >> 8);
                ((u8 *)&msg)[10] = (u8)vContact.y.value;
                vContact.z = *(Fx32 *)&hit->position.z;
                ((u8 *)&msg)[11] = (u8)(((u32)vContact.z.value >> 16 & 0x7f) | ((u32)vContact.z.value >> 24 & 0x80));
                ((u8 *)&msg)[12] = (u8)((u32)vContact.z.value >> 8);
                ((u8 *)&msg)[13] = (u8)vContact.z.value;
                if (((struct Ov114Actor *)*state)->pfnMessage != 0) {
                    ((struct Ov114Actor *)*state)->pfnMessage((struct Ov114Actor *)*state, &msg, 0xe);
                }
                func_ov107_020c5af8((struct Ov114Actor *)*state, 0x112, 5, &hit->position);
                hitAny = 1;
            }
        } while (++i < n);
    }
    return hitAny;
}

