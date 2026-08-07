typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Sphere {
    VecFx32 centre;
    int radius;
};

struct Msg {
    u16 h[7];
};

struct W1 {
    int v;
};

struct Flags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct ObjFlags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct ListNode {
    void *item;
    char pad04[4];
    u32 lo08 : 8;
    u32 hi08 : 24;
};

struct HitPacket {
    u32 flags00;
    VecFx32 normal;
    u32 field10;
    u32 field14;
    void *pPart;
    u8 bKind1c;
    u8 pad1d[3];
    u32 tail[3];
};

struct PushPacket {
    VecFx32 push;
    u8 bKind0c;
    u8 bKind0d;
    u16 pad0e;
    u32 field10;
    u32 field14;
    int field18;
};

struct State {
    char *pActor;
    char pad04[0x2c];
    int nTimer30;
    char pad34[0xc];
    VecFx32 *pPos40;
    char pad44[8];
    unsigned long long uMask4c;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern int func_01ff8d18(VecFx32 *out, VecFx32 *in);
extern void func_01ffa724(int scale, VecFx32 *in, VecFx32 *out);
extern struct ListNode *func_01fffd70(void *list);
extern struct ListNode *func_01fffd8c(void *list);
extern int func_ov107_020c8eb8(char *actor, struct Sphere *shape, void **out);
extern int func_ov107_020ca918(void *victim, char *a, char *b, int mode,
                               VecFx32 *push, int flags);
extern int func_ov107_020c3504(void *part, struct Sphere *shape, int mode);
extern int func_ov107_020c5cfc(void *obj, void *target, struct HitPacket *packet);
extern int func_ov131_020cc5ac(void *world, struct Sphere *shape, void **out);
extern int func_ov002_02076dac(void *obj, struct PushPacket *packet);
extern void *memset(void *, int, unsigned long);
extern void func_0203c634(struct Node *node, int slot, int arg);

extern const struct Msg data_ov131_020cef74;
extern const struct Msg data_ov131_020cef90;


static inline void ov131_packImpact(struct Msg *msg, VecFx32 *v)
{
    VecFx32 raw;

    *(struct W1 *)&raw.x = *(struct W1 *)&v->x;
    *(struct W1 *)&raw.y = *(struct W1 *)&v->y;
    *(struct W1 *)&raw.z = *(struct W1 *)&v->z;
    ((u8 *)msg)[5] = (u8)(((u32)raw.x >> 16 & 0x7f) | ((u32)raw.x >> 24 & 0x80));
    ((u8 *)msg)[6] = (u8)((u32)raw.x >> 8);
    ((u8 *)msg)[7] = (u8)raw.x;
    ((u8 *)msg)[8] = (u8)(((u32)raw.y >> 16 & 0x7f) | ((u32)raw.y >> 24 & 0x80));
    ((u8 *)msg)[9] = (u8)((u32)raw.y >> 8);
    ((u8 *)msg)[10] = (u8)raw.y;
    ((u8 *)msg)[11] = (u8)(((u32)raw.z >> 16 & 0x7f) | ((u32)raw.z >> 24 & 0x80));
    ((u8 *)msg)[12] = (u8)((u32)raw.z >> 8);
    ((u8 *)msg)[13] = (u8)raw.z;
}

static inline void ov131_emitChildEvent(struct Msg *msg, VecFx32 *v)
{
    ov131_packImpact(msg, v);
}

static inline void ov131_scanVictims(struct State *st, struct Sphere *shape,
                                     void **aVictims, VecFx32 *vDir,
                                     VecFx32 *vPush, VecFx32 *vImpact, struct Msg *msgA)
{
    struct Msg tmplA;
    long nHits;
    long i;
    int id;
    void (*pfnHook)(char *, struct Msg *, int);

    nHits = func_ov107_020c8eb8(st->pActor, shape, aVictims);
    i = 0;
    if (nHits > 0) {
        tmplA = data_ov131_020cef90;
        do {
            id = *(u16 *)((char *)aVictims[i] + 2);
            if ((st->uMask4c >> id & 1) == 0) {
                VEC_Subtract((VecFx32 *)((char *)aVictims[i] + 0x74), &shape->centre, vDir);
                func_01ff8d18(vDir, vDir);
                func_01ffa724(0x800, vDir, vPush);
                if (func_ov107_020ca918(aVictims[i], st->pActor, st->pActor, 1,
                                        vPush, 0) != 0) {
                    *msgA = tmplA;
                    func_01ffa724(shape->radius, vDir, vImpact);
                    VEC_Add(&shape->centre, vImpact, vImpact);
                    ov131_packImpact(msgA, vImpact);
                    pfnHook = *(void (**)(char *, struct Msg *, int))(st->pActor + 0x24);
                    if (pfnHook != 0) {
                        (*pfnHook)(st->pActor, msgA, 0xe);
                    }
                    id = *(u16 *)((char *)aVictims[i] + 2);
                    st->uMask4c = st->uMask4c | (unsigned long long)1 << id;
                }
            }
            i++;
        } while (i < nHits);
    }
}

void func_ov131_020ce2b4(struct Node *node)
{
    struct State *st;
    void *world;
    void *aVictims[4];
    struct Sphere shape;
    VecFx32 vDir;
    VecFx32 vPush;
    VecFx32 vImpact;
    struct Msg msgA;
    struct ListNode *ln;
    struct ListNode *part;
    char *obj;
    void (*pfnHook)(char *, struct Msg *, int);
    int nHits;
    int i;
    int id;
    int timer;

    st = node->pState;
    world = *(void **)(st->pActor + 4);
    shape.centre = *st->pPos40;
    shape.radius = st->nTimer30 * 3 + 0x800;

    ov131_scanVictims(st, &shape, aVictims, &vDir, &vPush, &vImpact, &msgA);

    ln = func_01fffd70((char *)world + 0x80);
    obj = ln == 0 ? 0 : (char *)ln->item;
    while (obj != 0) {
        id = *(u16 *)(obj + 2);
        if ((st->uMask4c >> id & 1) == 0 &&
            obj != st->pActor && (((struct ObjFlags60 *)(obj + 0x60))->lo & 1) != 0 &&
            (*(u16 *)(obj + 0x1ac) & 7) == 0) {
            part = func_01fffd70(obj + 0x22c);
            while (part != 0) {
                if ((part->lo08 & 1) != 0 &&
                    func_ov107_020c3504(part->item, &shape, 0) != 0) {
                    struct HitPacket packet = {0};
                    VEC_Subtract((VecFx32 *)(obj + 0x74), &shape.centre, &vDir);
                    func_01ff8d18(&vDir, &vDir);
                    func_01ffa724(0x800, &vDir, &vPush);
                    packet.flags00 = (u16)(packet.flags00 & 0xffff0000 | 4 |
                                          0x2000) | 0x800000;
                    packet.normal = vPush;
                    packet.field10 = packet.field10 & 0xffff0000 |
                                     *(u16 *)(st->pActor + 0x296);
                    packet.field14 = packet.field14 & 0xffff0000 |
                                     (*(u32 *)(st->pActor + 0x258) & 0xffff);
                    packet.pPart = part;
                    packet.bKind1c = 100;
                    if (func_ov107_020c5cfc(obj, *(void **)(st->pActor + 0x25c),
                                            &packet) != 0) {
                        id = *(u16 *)(obj + 2);
                        st->uMask4c = st->uMask4c | (unsigned long long)1 << id;
                        break;
                    }
                }
                part = func_01fffd8c(obj + 0x22c);
            }
        }
        ln = func_01fffd8c((char *)world + 0x80);
        obj = ln == 0 ? 0 : (char *)ln->item;
    }

    void *aChildren[4];

    nHits = func_ov131_020cc5ac(*(void **)((char *)world + 0x7c), &shape, aChildren);
    i = 0;
    if (nHits > 0) {
        do {
            struct PushPacket push = {0};
            VecFx32 vDir2;
            VecFx32 vImpact2;
            struct Msg msgB;
            struct Msg tmplB;
            tmplB = data_ov131_020cef74;
            VEC_Subtract((VecFx32 *)((char *)aChildren[i] + 0x2c), &shape.centre, &vDir2);
            func_01ff8d18(&vDir2, &vDir2);
            func_01ffa724(0x800, &vDir2, &push.push);
            push.bKind0c = 0xff;
            push.bKind0d = 2;
            push.field10 = *(u16 *)(st->pActor + 0x296);
            push.field14 = 4;
            push.field18 = 1 << *(u8 *)(st->pActor + 0x294);
            if (func_ov002_02076dac(*(void **)(*(char **)((char *)aChildren[i] + 0x28) + 0x158),
                                    &push) != 0) {
                msgB = tmplB;
                func_01ffa724(shape.radius, &vDir2, &vImpact2);
                VEC_Add(&shape.centre, &vImpact2, &vImpact2);
                ov131_emitChildEvent(&msgB, &vImpact2);
                pfnHook = *(void (**)(char *, struct Msg *, int))(st->pActor + 0x24);
                if (pfnHook != 0) {
                    (*pfnHook)(st->pActor, &msgB, 0xe);
                }
            }
            i++;
        } while (i < nHits);
    }

    timer = st->nTimer30 + *(int *)((char *)node->pScene + 0x2c);
    st->nTimer30 = timer;
    if (timer >= 0x1000) {
        u16 *hw = (u16 *)(st->pActor + 0x60);
        unsigned int h = *hw;
        *hw = h & ~0xff00 | (((((u32)h << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
        ((struct Flags60 *)(st->pActor + 0x60))->hi =
            ((struct Flags60 *)(st->pActor + 0x60))->hi & ~1;
        *(u8 *)(st->pActor + 0x1c7) = 3;
        func_0203c634(node, node->bSlot, 0);
    }
}
