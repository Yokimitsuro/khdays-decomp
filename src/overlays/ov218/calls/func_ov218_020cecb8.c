/* Burst tick of the ov218 enemy's shot: for 0.5 after the bounce the +0x34 clock runs and the owner's
 * sphere (radius 2.0) hits every entity around the +0x390 body once (the +0x3c 64-bit kind mask): the
 * direct hits are pushed by 0.5 along the flattened direction away from the owner (kind 1 with a
 * +0x398 partner, else 0) and get message 0 at their position; every visible, unguarded actor of the
 * world list with a shown part inside the sphere gets a kind-4 hit packet (normal away from the
 * owner, the body's +0x290 power for that kind, the owner's +0x258 reaction, the part) through
 * 020c5cfc and message 0 on acceptance. Any hit fires reaction 0x135 mode 5 at the +8 target. Once
 * the +4 rig is idle sub-state 0 follows. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;
struct Sphere { Vec3 centre; int radius; };
struct ListNode { void *item; };
struct W8 { unsigned int lo : 8; };

struct Obj {
    u16 flags000;
    u16 id002;
    char pad004[0x5c];
    unsigned short lo060 : 8;
    unsigned short hi060 : 8;
    char pad062[0x12];
    Vec3 pos074;
    char pad080[0x12c];
    u16 attr1ac;
};

struct HitPacket {
    u32 flags00;
    Vec3 normal;
    u32 field10;
    u32 field14;
    void *pPart;
    u32 tail[4];
};

struct ShotState {
    int pOwner;             /* +0x00 */
    int pRig;               /* +0x04 */
    int pTarget;            /* +0x08 */
    char pad0c[0x28];
    int timer034;           /* +0x34 */
    char pad38[4];
    unsigned long long mask; /* +0x3c */
};

extern int func_ov107_020c8eb8(int owner, struct Sphere *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern struct ListNode *func_01fffd70(void *list);
extern struct ListNode *func_01fffd8c(void *list);
extern int func_ov107_020c3504(void *part, struct Sphere *shape, int flag);
extern int func_ov107_020c5cfc(struct Obj *obj, int target, struct HitPacket *packet);
extern void func_ov107_020c5af8(int owner, int id, int mode, int at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;

void func_ov218_020cecb8(int *node)
{
    struct ShotState *st = (struct ShotState *)node[1];
    struct Sphere sphere;
    int hits[4];
    Vec3 push;
    long n;
    int hit;
    int world;
    u8 kind;
    long i;
    struct Obj *obj;
    struct ListNode *ln;
    struct ListNode *part;

    st->timer034 += *(int *)(node[0] + 0x2c);
    if (st->timer034 < 0x800) {
        hit = 0;
        world = *(int *)(st->pOwner + 4);
        kind = *(int *)(st->pOwner + 0x398) != 0 ? 1 : 0;
        sphere = *(struct Sphere *)(st->pOwner + 0x74);
        sphere.radius = 0x2000;
        n = func_ov107_020c8eb8(*(int *)(st->pOwner + 0x390), &sphere, hits);
        for (i = 0; i < n; i++) {
            u16 id = *(u16 *)(hits[i] + 2);

            if ((st->mask >> id & 1) != 0) {
                continue;
            }
            st->mask = st->mask | (unsigned long long)1 << id;
            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(st->pOwner + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], st->pOwner, *(int *)(st->pOwner + 0x390), kind, &push, 0) != 0) {
                func_ov107_020c0b90(*(int *)(st->pOwner + 0x390), 0, *(Vec3 *)(hits[i] + 0x74), 0);
                hit = 1;
            }
        }
        ln = func_01fffd70((char *)world + 0x80);
        obj = ln == 0 ? 0 : (struct Obj *)ln->item;
        if (obj != 0) {
            int power = kind * 6;

            do {
                if (obj != (struct Obj *)st->pOwner && (st->mask >> obj->id002 & 1) == 0) {
                    st->mask = st->mask | (unsigned long long)1 << obj->id002;
                    if ((obj->lo060 & 1) != 0 && (obj->attr1ac & 3) == 0) {
                        part = func_01fffd70((char *)obj + 0x22c);
                        while (part != 0) {
                            if ((((struct W8 *)((char *)part + 8))->lo & 1) != 0 &&
                                func_ov107_020c3504(part->item, &sphere, 0) != 0) {
                                struct HitPacket packet = {0};

                                VEC_Subtract(&obj->pos074, (void *)(st->pOwner + 0x74), &packet.normal);
                                if (func_01ff8d18(&packet.normal, &packet.normal) == 0) {
                                    packet.normal = data_02042258;
                                }
                                packet.flags00 = packet.flags00 & 0xffff0000 | 4;
                                packet.field10 = packet.field10 & 0xffff0000 |
                                                 *(u16 *)(power + *(int *)(st->pOwner + 0x390) + 0x290);
                                packet.field14 = packet.field14 & 0xffff0000 |
                                                 (u16)*(int *)(st->pOwner + 0x258);
                                packet.pPart = part;
                                if (func_ov107_020c5cfc(obj, 0, &packet) != 0) {
                                    func_ov107_020c0b90(*(int *)(st->pOwner + 0x390), 0, obj->pos074, 0);
                                    hit = 1;
                                }
                            }
                            part = func_01fffd8c((char *)obj + 0x22c);
                        }
                    }
                }
                ln = func_01fffd8c((char *)world + 0x80);
                obj = ln == 0 ? 0 : (struct Obj *)ln->item;
            } while (obj != 0);
        }
        if (hit != 0) {
            func_ov107_020c5af8(st->pOwner, 0x135, 5, st->pTarget);
        }
    }
    if (*(u8 *)(st->pRig + 0xad) != 0) {
        return;
    }
    *(u8 *)(st->pOwner + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
