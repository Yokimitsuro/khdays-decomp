/*
 * Swing sweep of the ov181 enemy (x4: ov181/182/183/184): from the +0x14 heading builds the
 * forward vector (sine/cosine table), a 0.5 push along it and a probe sphere 1.375 ahead of the
 * +8 position with radius 1.0; every actor in the sphere that takes the push through the ov107
 * hit hook (the caller's kind) gets a kind-5 message whose cmd byte is 2 when the target's
 * +0x7c facing agrees with the swing (kind 1 flips the sense) and 0 otherwise, carrying the
 * impact point (sphere centre plus push) delivered to the owner's +0x24 handler, plus reaction
 * 0x131/5 at that point.
 * Coordinates are packed through a wrapped copy (the func_ov131_020ce2b4 spelling): copying
 * a one-value struct is a struct copy mwcc keeps, which is the ROM's late stack copy.
 *
 * Codegen: the impact point is packed through per-component Fx32 wrapper copies (ov122_020d12f4
 * spelling); `pMsg = &msg` taken after the template copy keeps the message address in r8 across
 * the side test, and the command byte is spelled `flip == 0 ? 0 : 2`. */
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

struct Ov181Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov181Actor *self, struct Msg *msg, int size);
};

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8eb8(struct Ov181Actor *owner, Sphere *sphere, struct Ov181Actor **out);
extern int func_ov107_020ca918(struct Ov181Actor *hit, struct Ov181Actor *a, struct Ov181Actor *b, int kind, const Vec3 *push, int z);
extern char **OS_IsThreadAvailable_0x020c9848(void);   /* the ov107 global getter (misattributed SDK name) */
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_ov107_020c5af8(struct Ov181Actor *owner, u16 a, u16 id, Vec3 *pos);
extern const short data_0203d210[];
extern const struct Msg data_ov181_020cea04;

void func_ov181_020cc704(int *state, int kind)
{
    Vec3 fwd;
    Vec3 push;
    Sphere sphere;
    struct Ov181Actor *hits[4];
    Vec3 impact;
    struct Msg msg;
    struct Msg tmpl;
    FxVec vContact;
    struct Msg *pMsg;
    int idx;
    int i;
    int n;
    int flip;

    idx = (unsigned short)((0x28BE60DB9391LL * state[5] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.x = data_0203d210[(idx >> 4) << 1];                                              /* FX_SinIdx */
    fwd.y = 0;
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                        /* FX_CosIdx */
    func_01ffa724(0x800, &fwd, &push);
    func_01ffa724(0x1600, &fwd, &sphere.pos);
    VEC_Add((Vec3 *)state[2], &sphere.pos, &sphere.pos);
    sphere.radius = 0x1000;
    n = func_ov107_020c8eb8((struct Ov181Actor *)*state, &sphere, hits);
    i = 0;
    if (n > 0) {
        tmpl = data_ov181_020cea04;
        do {
            if (func_ov107_020ca918(hits[i], (struct Ov181Actor *)*state, (struct Ov181Actor *)*state, kind, &push, 0) != 0) {
                msg = tmpl;
                pMsg = &msg;
                flip = kind == 1 ? 1 : 0;
                if (VEC_DotProduct((Vec3 *)(*OS_IsThreadAvailable_0x020c9848() + 0x7c), &fwd) > 0) {
                    flip = (flip + 1) & 1;
                }
                ((u8 *)pMsg)[3] = flip == 0 ? 0 : 2;
                VEC_Add(&sphere.pos, &push, &impact);
                vContact.x = *(Fx32 *)&impact.x;
                ((u8 *)&msg)[5] = (u8)(((u32)vContact.x.value >> 16 & 0x7f) | ((u32)vContact.x.value >> 24 & 0x80));
                ((u8 *)&msg)[6] = (u8)((u32)vContact.x.value >> 8);
                ((u8 *)&msg)[7] = (u8)vContact.x.value;
                vContact.y = *(Fx32 *)&impact.y;
                ((u8 *)&msg)[8] = (u8)(((u32)vContact.y.value >> 16 & 0x7f) | ((u32)vContact.y.value >> 24 & 0x80));
                ((u8 *)&msg)[9] = (u8)((u32)vContact.y.value >> 8);
                ((u8 *)&msg)[10] = (u8)vContact.y.value;
                vContact.z = *(Fx32 *)&impact.z;
                ((u8 *)&msg)[11] = (u8)(((u32)vContact.z.value >> 16 & 0x7f) | ((u32)vContact.z.value >> 24 & 0x80));
                ((u8 *)&msg)[12] = (u8)((u32)vContact.z.value >> 8);
                ((u8 *)&msg)[13] = (u8)vContact.z.value;
                if (((struct Ov181Actor *)*state)->pfnMessage != 0) {
                    ((struct Ov181Actor *)*state)->pfnMessage((struct Ov181Actor *)*state, &msg, 0xe);
                }
                func_ov107_020c5af8((struct Ov181Actor *)*state, 0x131, 5, &impact);
            }
            i++;
        } while (i < n);
    }
}
