/* Attack tick of the ov134 enemy (x3: ov134/135/136). Counts the +0x30 timer and fires reaction
 * 0x11c mode 6 once at 0x330 (+0x40 latch); steers the +0x18 velocity along the +0x3a0 resource's
 * local step rotated by the actor's +0xa0 quaternion, then sweeps a 0x800 sphere around the
 * +0x394 item's +0x14 placement moved by that velocity: every victim whose +0x1b4 kind bit is
 * not yet in the +0x41 mask and accepts the push (mode 1) receives the 0xe message with the
 * victim's +0x74 position (raised by 0x800) through the actor's +0x24 hook, marks the bit, fires
 * reaction 0x11c mode 7 and clears the +0x42 bit-0 flag. When the +4 sub-item's +0xad byte is
 * clear the +0x60 high-byte bit 6 is dropped and the state advances to func_ov136_020d3794.
 * Codegen: the victim position is a plain stack copy (`raw`, y raised in place) and each
 * component is packed through an Fx32 wrapper copy taken right before its bytes (the three
 * unread word stores are the ROM's); this is what puts x/y+0x800/z in r1/r2/ip. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Vec3i { int x, y, z; };
typedef struct { int x, y, z, w; } Quat;

struct Sphere {
    FxVec centre;
    int radius;
};

struct Msg {
    u16 h[7];
};

struct Flags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct Flags42 {
    u8 bCharge : 1;
};

struct State {
    void *pActor;
    void *pSub;
    char pad08[0x10];
    FxVec vVelocity;
    char pad24[0xc];
    int nElapsed30;
    char pad34[8];
    void *pAnchor3c;
    u8 bFired40;
    u8 uHitMask41;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern const struct Msg data_ov136_020d3a10;
extern void func_ov136_020d3794(void);

extern void func_ov107_020c5af8(void *actor, int id, u16 mode, void *at);
extern int func_ov107_020c9f48(void *resource, FxVec *out);
extern void func_0202f384(FxVec *out, void *q, const FxVec *in);
extern void func_01ffa724(int scale, FxVec *in, FxVec *out);
extern void VEC_Add(FxVec *a, FxVec *b, FxVec *ab);
extern int func_ov107_020c8eb8(void *actor, struct Sphere *shape, void *victims[]);
extern int func_ov107_020ca918(void *victim, void *actor, void *actor2, int kind, FxVec *push, int flags);
extern void func_0203c634(struct Node *node, int slot, void *cb);

void func_ov136_020d34b4(struct Node *node)
{
    struct State *st;
    FxVec vLocal;
    void *aVictims[4];
    struct Sphere shape;
    struct Vec3i raw;
    struct Msg msg;
    struct Msg tmpl;
    FxVec vContact;
    int i;
    int nHits;
    int speed;

    st = node->pState;
    st->nElapsed30 += *(int *)((char *)node->pScene + 0x2c);
    if (st->bFired40 == 0 && st->nElapsed30 >= 0x330) {
        st->bFired40 = 1;
        func_ov107_020c5af8(st->pActor, 0x11c, 6, st->pAnchor3c);
    }
    speed = func_ov107_020c9f48(*(void **)((char *)st->pActor + 0x3a0), &vLocal);
    func_0202f384(&st->vVelocity, (char *)st->pActor + 0xa0, &vLocal);
    func_01ffa724(speed, &st->vVelocity, &st->vVelocity);
    VEC_Add((FxVec *)((char *)*(void **)((char *)st->pActor + 0x394) + 0x14), &st->vVelocity, &shape.centre);
    shape.radius = 0x800;
    nHits = func_ov107_020c8eb8(st->pActor, &shape, aVictims);
    i = 0;
    if (nHits > 0) {
        tmpl = data_ov136_020d3a10;
        do {
            if (((st->uHitMask41 >> *(u8 *)((char *)aVictims[i] + 0x1b4)) & 1) == 0 &&
                func_ov107_020ca918(aVictims[i], st->pActor, st->pActor, 1, &st->vVelocity, 0) != 0) {
                msg = tmpl;
                raw = *(struct Vec3i *)((char *)aVictims[i] + 0x74);
                raw.y += 0x800;
                vContact.x = *(Fx32 *)&raw.x;
                ((u8 *)&msg)[5] = (u8)(((u32)vContact.x.value >> 16 & 0x7f) |
                                       ((u32)vContact.x.value >> 24 & 0x80));
                ((u8 *)&msg)[6] = (u8)((u32)vContact.x.value >> 8);
                ((u8 *)&msg)[7] = (u8)vContact.x.value;
                vContact.y = *(Fx32 *)&raw.y;
                ((u8 *)&msg)[8] = (u8)(((u32)vContact.y.value >> 16 & 0x7f) |
                                       ((u32)vContact.y.value >> 24 & 0x80));
                ((u8 *)&msg)[9] = (u8)((u32)vContact.y.value >> 8);
                ((u8 *)&msg)[10] = (u8)vContact.y.value;
                vContact.z = *(Fx32 *)&raw.z;
                ((u8 *)&msg)[11] = (u8)(((u32)vContact.z.value >> 16 & 0x7f) |
                                        ((u32)vContact.z.value >> 24 & 0x80));
                ((u8 *)&msg)[12] = (u8)((u32)vContact.z.value >> 8);
                ((u8 *)&msg)[13] = (u8)vContact.z.value;
                {
                    void (*pfnHook)(void *, struct Msg *, int) =
                        *(void (**)(void *, struct Msg *, int))((char *)st->pActor + 0x24);
                    if (pfnHook != 0) {
                        (*pfnHook)(st->pActor, &msg, 0xe);
                    }
                }
                st->uHitMask41 |= 1 << *(u8 *)((char *)aVictims[i] + 0x1b4);
                func_ov107_020c5af8(st->pActor, 0x11c, 7, st->pAnchor3c);
                ((struct Flags42 *)&st->uHitMask41)[1].bCharge = 0;
            }
            i++;
        } while (i < nHits);
    }
    if (*(u8 *)((char *)st->pSub + 0xad) == 0) {
        ((struct Flags60 *)((char *)st->pActor + 0x60))->hi &= ~0x40;
        func_0203c634(node, node->bSlot, func_ov136_020d3794);
    }
}
