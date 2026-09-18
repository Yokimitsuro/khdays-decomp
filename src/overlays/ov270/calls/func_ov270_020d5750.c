/* Swing tick of the ov269 enemy (and its byte-identical twin): the +0x14 turn step is zeroed;
 * until the +0x53 one-shot fires, the +0x54 timer accumulates and past 0x1333 reaction 0x160/6
 * fires at the +0x398 joint's +0x14 (+0x53 set). The +0x18 velocity is the +0x3d0 motion's
 * forward vector rotated into the actor frame and scaled by its speed. From +0x30 = 0x200 on,
 * a sphere at the +0x390 joint's +0x68 offset by the velocity sweeps: entities whose +0x1b4
 * kind is not yet in the +0x51 mask that accept a kind-1 hit (no push) get the
 * overlay's 14-byte message with their +0x74 position (y raised by 0x800) through the actor's
 * +0x24 hook, their mask bit and reaction 0x160/7 at that position. Once the +0x3d0 motion's
 * +0x3c item goes idle (+0xad), the +0x4c repeat count is spent: exhausted, a random +0x34
 * delay in [+0x224, +0x228] and sub-state 2 end the state; otherwise animation 9 replays with
 * +0x50/+0x30/+0x51/+0x53/+0x54 cleared and the d382c wait tick takes over. While the item is
 * busy the +0x30 timer accumulates.
 *
 * Codegen: the contact position is a stack copy (`raw`, y raised in place) packed through the
 * Fx32 wrapper copies (ov122_020d12f4 idiom) -- the three unread word stores at the frame
 * bottom are the ROM's; the ca918 push is the zero vector. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Ov269Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov269Owner *self, PosMsg *msg, int size);
};

extern void func_ov107_020c5af8(struct Ov269Owner *owner, int a, int id, void *at);
extern int func_ov107_020c9f48(int resource, Vec3 *out);
extern void func_0202f384(Vec3 *dst, void *xfm, Vec3 *src);
extern void func_01ffa724(int scale, Vec3 *src, Vec3 *dst);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8eb8(struct Ov269Owner *owner, Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, struct Ov269Owner *a, struct Ov269Owner *b, int kind, Vec3 *push, int z);
extern int func_02023eb4(int range);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(struct Ov269Owner *actor, int anim, int flag);
extern const PosMsg data_ov270_020d688a;
extern const Vec3 data_02041dc8;
extern void func_ov270_020d564c(void);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov270_020d5750(int *node)
{
    int *state = (int *)node[1];
    struct Ov269Owner *owner;
    Vec3 fwd;
    int hits[4];
    Sphere sphere;
    Vec3 raw;
    PosMsg msg;
    PosMsg tmpl;
    FxVec vContact;
    int speed;
    int nHits;
    int i;

    state[5] = 0;
    if (*(u8 *)((char *)state + 0x53) == 0) {
        state[0x15] += *(int *)(*node + 0x2c);
        if (state[0x15] > 0x1333) {
            func_ov107_020c5af8((struct Ov269Owner *)*state, 0x160, 6, (char *)*(int *)(*state + 0x398) + 0x14);
            *(u8 *)((char *)state + 0x53) = 1;
        }
    }
    speed = func_ov107_020c9f48(*(int *)(*state + 0x3d0), &fwd);
    func_0202f384((Vec3 *)(state + 6), (char *)*state + 0xa0, &fwd);
    func_01ffa724(speed, (Vec3 *)(state + 6), (Vec3 *)(state + 6));
    if (state[0xc] >= 0x200) {
        sphere = *(Sphere *)(*(int *)(*state + 0x390) + 0x68);
        VEC_Add(&sphere.pos, (Vec3 *)(state + 6), &sphere.pos);
        nHits = func_ov107_020c8eb8((struct Ov269Owner *)*state, &sphere, hits);
        i = 0;
        if (nHits > 0) {
            tmpl = data_ov270_020d688a;
            do {
                if (((*(u8 *)((char *)state + 0x51) >> *(u8 *)(hits[i] + 0x1b4)) & 1) == 0 &&
                    func_ov107_020ca918(hits[i], (struct Ov269Owner *)*state, (struct Ov269Owner *)*state, 1, (Vec3 *)&data_02041dc8, 0) != 0) {
                    msg = tmpl;
                    raw = *(Vec3 *)(hits[i] + 0x74);
                    raw.y += 0x800;
                    vContact.x = *(Fx32 *)&raw.x;
                    ((u8 *)&msg)[5] = (u8)(((u32)vContact.x.value >> 0x10 & 0x7f) | ((u32)vContact.x.value >> 0x18 & 0x80));
                    ((u8 *)&msg)[6] = (u8)((u32)vContact.x.value >> 8);
                    ((u8 *)&msg)[7] = (u8)vContact.x.value;
                    vContact.y = *(Fx32 *)&raw.y;
                    ((u8 *)&msg)[8] = (u8)(((u32)vContact.y.value >> 0x10 & 0x7f) | ((u32)vContact.y.value >> 0x18 & 0x80));
                    ((u8 *)&msg)[9] = (u8)((u32)vContact.y.value >> 8);
                    ((u8 *)&msg)[10] = (u8)vContact.y.value;
                    vContact.z = *(Fx32 *)&raw.z;
                    ((u8 *)&msg)[11] = (u8)(((u32)vContact.z.value >> 0x10 & 0x7f) | ((u32)vContact.z.value >> 0x18 & 0x80));
                    ((u8 *)&msg)[12] = (u8)((u32)vContact.z.value >> 8);
                    ((u8 *)&msg)[13] = (u8)vContact.z.value;
                    if (((struct Ov269Owner *)*state)->pfnMessage != 0) {
                        ((struct Ov269Owner *)*state)->pfnMessage((struct Ov269Owner *)*state, &msg, 0xe);
                    }
                    *(u8 *)((char *)state + 0x51) |= 1 << *(u8 *)(hits[i] + 0x1b4);
                    func_ov107_020c5af8((struct Ov269Owner *)*state, 0x160, 7, &raw);
                }
            } while (++i < nHits);
        }
    }
    if (*(u8 *)(*(int *)(*(int *)(*state + 0x3d0) + 0x3c) + 0xad) == 0) {
        state[0x13]--;
        if (state[0x13] <= 0) {
            state[0xd] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
            *(u8 *)(*state + 0x1c7) = 2;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        func_ov107_020c9264((struct Ov269Owner *)*state, 9, 0);
        *(u8 *)((char *)state + 0x50) = 0;
        state[0xc] = 0;
        *(u8 *)((char *)state + 0x51) = 0;
        *(u8 *)((char *)state + 0x53) = 0;
        state[0x15] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov270_020d564c);
        return;
    }
    state[0xc] += *(int *)(*node + 0x2c);
}
