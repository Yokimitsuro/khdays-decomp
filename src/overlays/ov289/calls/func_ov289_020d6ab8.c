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

struct ListNode {
    void *item;
};

struct Obj {
    u16 flags000;
    u16 id002;
    char pad004[0x5c];
    unsigned short lo060 : 8;
    unsigned short hi060 : 8;
    char pad062[0x12];
    VecFx32 pos074;
    char pad080[0x12c];
    u16 attr1ac;
};

struct HitPacket {
    u32 flags00;
    VecFx32 normal;
    u32 field10;
    u32 field14;
    void *pPart;
    u32 tail[4];
};

struct State {
    void *pActor;
    void *pOwner;
    void *pTarget;
    char pad00c[0x28];
    int timer034;
    char pad038[0x14];
    unsigned long long mask;
    u8 sent054;
    char pad055[3];
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad008[0x18];
    signed char bSlot;
};

struct Msg {
    u16 h[7];
};

struct Vec3s {
    int x;
    int y;
    int z;
};

struct W1 {
    int v;
};

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern struct ListNode *func_01fffd70(void *list);
extern struct ListNode *func_01fffd8c(void *list);
extern int func_ov107_020c3504(void *part, struct Sphere *shape, int mode);
extern int func_01ff8d18(VecFx32 *out, VecFx32 *in);
extern void func_01ffa724(int scale, VecFx32 *in, VecFx32 *out);
extern int func_ov107_020c5cfc(struct Obj *obj, void *target, struct HitPacket *packet);
extern void func_ov107_020c0b90(void *actor, int a, VecFx32 v, int d);
extern void *func_ov107_020c9b68(u16 id);
extern void func_02031384(int channel, void *packet, int len);
extern void func_0203c634(struct Node *node, int slot, void *arg);

void func_ov289_020d6ab8(struct Node *node)
{
    int mode;
    struct State *st;
    void *scene;
    void *actor;
    void *other;
    void *world;
    struct Obj *obj;
    struct ListNode *ln;
    struct ListNode *part;
    struct Sphere shape;
    int timer;
    int scale;
    int slot;
    u8 hasMode;
    int limit;
    int count;
    unsigned int clamp;

    scene = node->pScene;
    st = node->pState;
    timer = st->timer034 + *(int *)((char *)scene + 0x2c);
    st->timer034 = timer;
    if (timer < 0x800) {
        actor = st->pActor;
        mode = *(int *)((char *)actor + 0x38c);
        if (mode == 0) {
            if (mode != 0) {
                return;
            }
            if (timer < 0x200) {
                return;
            }
        }
        world = *(void **)((char *)actor + 4);
        hasMode = (u8)(mode != 0);
        shape = *(struct Sphere *)((char *)actor + 0x74);
        scale = *(int *)((char *)st->pActor + 0x38c) != 0 ? 0x6000 : 0x1000;
        shape.radius = (int)(((long long)shape.radius * scale + 0x800) >> 12);
        ln = func_01fffd70((char *)world + 0x80);
        obj = ln == 0 ? 0 : (struct Obj *)ln->item;
        if (obj == 0) {
            return;
        }
        slot = hasMode * 6;
        do {
            if (obj != (struct Obj *)st->pActor && (obj->lo060 & 1) != 0 &&
                (obj->attr1ac & 3) == 0 &&
                (st->mask >> obj->id002 & 1) == 0) {
                part = func_01fffd70((char *)obj + 0x22c);
                while (part != 0) {
                    if (func_ov107_020c3504(part->item, &shape, 0) != 0) {
                        struct HitPacket packet = {0};
                        VecFx32 hitNormal;
                        VEC_Subtract(&obj->pos074, (VecFx32 *)((char *)st->pActor + 0x74),
                                     &packet.normal);
                        func_01ff8d18(&packet.normal, &packet.normal);
                        hitNormal = packet.normal;
                        packet.flags00 = packet.flags00 & 0xffff0000 | 4 | 0x8000;
                        packet.field10 = packet.field10 & 0xffff0000 |
                                         *(u16 *)((char *)slot + (int)st->pActor + 0x290);
                        packet.field14 = packet.field14 & 0xffff0000 |
                                         (u16)*(int *)((char *)st->pActor + 0x258);
                        packet.field14 = (u16)packet.field14 |
                                         (u32)*(u8 *)((char *)st->pActor + 0x19c) << 0x10;
                        packet.pPart = part;
                        if (func_ov107_020c5cfc(obj, st->pTarget, &packet) != 0) {
                            st->mask = st->mask | (unsigned long long)1 << obj->id002;
                            func_01ffa724(shape.radius, &hitNormal, &hitNormal);
                            VEC_Add(&hitNormal, &shape.centre, &hitNormal);
                            func_ov107_020c0b90(st->pActor, 0, hitNormal, 0);
                        }
                    }
                    part = func_01fffd8c((char *)obj + 0x22c);
                }
            }
            ln = func_01fffd8c((char *)world + 0x80);
            obj = ln == 0 ? 0 : (struct Obj *)ln->item;
        } while (obj != 0);
        return;
    }
    if (st->sent054 == 0 && st->pTarget != 0) {
        struct Msg msg = {0};
        struct Vec3s v;
        struct Msg *m;
        void *src;
        count = 0;
        m = &msg;
        other = *(void **)((char *)st->pTarget + 0x18c);
        limit = 4;
        do {
            if ((st->mask >> limit & 1) != 0) {
                obj = (struct Obj *)func_ov107_020c9b68((u16)limit);
                if (obj == 0 || *(u8 *)((char *)obj + 0x19c) != 0x6b) {
                    count++;
                }
            }
            limit++;
        } while (limit < 0x40);
        m->h[0] = *(u16 *)((char *)st->pActor + 2);
        ((u8 *)m)[2] = 5;
        ((u8 *)m)[3] = 3;
        src = st->pActor;
        *(struct W1 *)&v.x = *(struct W1 *)((char *)src + 0x74);
        ((u8 *)&msg)[5] = (u8)(((u32)v.x >> 16 & 0x7f) | ((u32)v.x >> 24 & 0x80));
        ((u8 *)&msg)[6] = (u8)((u32)v.x >> 8);
        ((u8 *)&msg)[7] = (u8)v.x;
        *(struct W1 *)&v.y = *(struct W1 *)((char *)src + 0x78);
        ((u8 *)&msg)[8] = (u8)(((u32)v.y >> 16 & 0x7f) | ((u32)v.y >> 24 & 0x80));
        ((u8 *)&msg)[9] = (u8)((u32)v.y >> 8);
        ((u8 *)&msg)[10] = (u8)v.y;
        *(struct W1 *)&v.z = *(struct W1 *)((char *)src + 0x7c);
        ((u8 *)&msg)[11] = (u8)(((u32)v.z >> 16 & 0x7f) | ((u32)v.z >> 24 & 0x80));
        ((u8 *)&msg)[12] = (u8)((u32)v.z >> 8);
        ((u8 *)&msg)[13] = (u8)v.z;
        clamp = *(u8 *)((char *)other + 0x2ab3);
        if (clamp > 8) {
            clamp = 8;
        } else if (clamp < 1) {
            clamp = 1;
        }
        ((u8 *)&msg)[4] = (u8)((count + 1) * clamp);
        func_02031384(1, &msg.h, 0xe);
        st->sent054 = 1;
    }
    if (*(u8 *)((char *)st->pOwner + 0xad) != 0) {
        return;
    }
    *(u8 *)((char *)st->pActor + 0x1c7) = 3;
    func_0203c634(node, node->bSlot, 0);
}
