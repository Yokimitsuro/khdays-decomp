/*
 * Dive tick of the ov181 enemy (x4: ov181/182/183/184): copies the +0x78 velocity into +0x54,
 * drops its +0x7c vertical part by 30 x dt x 0.046875 and advances the +0x1c and +0x6c timers;
 * once the +0x6c timer reaches 0x1222 with bit 1 of the +0x51 flags clear it sets the bit and
 * fires reaction 0x131/8 at the +4 position. After the first 0x100 of flight every actor in the
 * 0.875 sphere ahead of the +8 position that takes the (flattened, normalised) velocity push
 * (kind 2) gets a kind-5 message with the impact point delivered to the owner's +0x24 handler,
 * the velocity's x/z are zeroed and reaction 0/0x51 fires at the impact. Landing (+0x17a bit 0)
 * after that first stretch plays pose 0x10, clears bit 6 of the +0x60 high byte and moves to
 * handler 020ce5a8; otherwise the first downward velocity latches +0x50 and plays pose 0xf.
 * The impact point is packed through per-component Fx32 wrapper copies taken right before
 * each byte triple (the ov122_020d12f4 spelling).
 */
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

struct Flags17a { unsigned char bit0 : 1; };
struct Flags51 { unsigned char bit0 : 1; unsigned char bit1 : 1; };

struct Ov181Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov181Actor *self, struct Msg *msg, int size);
};

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8eb8(struct Ov181Actor *owner, Sphere *sphere, struct Ov181Actor **out);
extern int func_ov107_020ca918(struct Ov181Actor *hit, struct Ov181Actor *a, struct Ov181Actor *b, int kind, const Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov181Actor *owner, u16 a, u16 id, Vec3 *pos);
extern const struct Msg data_ov183_020d2652;
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov183_020d21e8(void);
struct hw60 { unsigned short lo : 8, hi : 8; };

void func_ov183_020d1e8c(int node)
{
    int *state = *(int **)(node + 4);
    Sphere sphere;
    Vec3 push;
    struct Ov181Actor *hits[4];
    Vec3 impact;
    struct Msg msg;
    struct Msg tmpl;
    FxVec vContact;
    int i;
    int n;

    *(Vec3 *)(state + 0x15) = *(Vec3 *)(state + 0x1e);
    state[0x1f] -= (int)(((long long)(*(int *)(*(int *)node + 0x2c) * 30) * 0xc0 + 0x800) >> 12);
    state[7] += *(int *)(*(int *)node + 0x2c);
    state[0x1b] += *(int *)(*(int *)node + 0x2c);
    if (!((struct Flags51 *)((char *)state + 0x51))->bit1 && state[0x1b] >= 0x1222) {
        *(unsigned char *)((char *)state + 0x51) |= 2;
        func_ov107_020c5af8((struct Ov181Actor *)*state, 0x131, 8, (Vec3 *)state[1]);
    }
    if (state[7] > 0x100) {
        VEC_Add((Vec3 *)state[2], (Vec3 *)(state + 0x15), &sphere.pos);
        sphere.radius = 0xe00;
        push.x = state[0x1e];
        push.y = 0;
        push.z = state[0x20];
        func_01ff8d18(&push, &push);
        func_01ffa724(0x1000, &push, &push);
        n = func_ov107_020c8eb8((struct Ov181Actor *)*state, &sphere, hits);
        i = 0;
        if (n > 0) {
            tmpl = data_ov183_020d2652;
            do {
                if (func_ov107_020ca918(hits[i], (struct Ov181Actor *)*state, (struct Ov181Actor *)*state, 2, &push, 0) != 0) {
                    msg = tmpl;
                    VEC_Add(&sphere.pos, (Vec3 *)(state + 0x15), &impact);
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
                    state[0x1e] = 0;
                    state[0x20] = 0;
                    func_ov107_020c5af8((struct Ov181Actor *)*state, 0, 0x51, &impact);
                }
                i++;
            } while (i < n);
        }
    }
    if (state[7] > 0x100 && ((struct Flags17a *)(*state + 0x17a))->bit0) {
        func_ov107_020c9264(*state, 0x10, 0);
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
        func_0203c634(node, *(signed char *)(node + 0x20), func_ov183_020d21e8);
        return;
    }
    if (*(unsigned char *)((char *)state + 0x50) != 0) {
        return;
    }
    if (state[0x1f] >= 0) {
        return;
    }
    *(unsigned char *)((char *)state + 0x50) = 1;
    func_ov107_020c9264(*state, 0xf, 0);
}
