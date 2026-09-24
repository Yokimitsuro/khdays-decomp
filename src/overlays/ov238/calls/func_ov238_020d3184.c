/* Charge sweep tick of the ov238 enemy. Between 0.17 and 1.49 of the +0x2c clock a sphere at the +8
 * position (radius growing from 1.04 with the clock, capped at 1.71) collects the entities around the
 * owner; each one not yet in the +0x1c 64-bit mask with a +0x1c4 hit hook gets a 40-byte packet (the
 * +0x28 heading, the partner's +0x296 power and +0x293 knock bits, a random reaction of the owner's
 * four at +0x39c, knock 100, the partner as source); an acceptance latches +0x394, marks the kind and
 * sends message 3 from the partner 1.5 above the victim's +0x190 point. Every visible, unguarded actor
 * of the world list (not the partner) with a shown part inside the sphere then gets a kind-4 44-byte
 * packet through 020c5cfc (random reaction, partner power, owner +0x258 reaction, knock 100) and is
 * marked on acceptance. Once the clock reaches 2.0 +0x390 clears and sub-state 0 follows. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int nRadius; } Sphere;
struct Atk { u8 b0; u8 bits; u8 r2; u8 r3; u16 power; };
struct Rider { char pad[0x28c]; struct Atk atk[2]; };
struct ListNode { void *item; };
struct W8 { unsigned int lo : 8; };

struct Obj {
    u16 flags000;
    u16 id002;
    char pad004[0x5c];
    unsigned short lo060 : 8;
    unsigned short hi060 : 8;
    char pad062[0x14a];
    u16 attr1ac;
};

struct HitPacket40 {
    int nKind;
    Vec3 vNormal;
    int nPower;
    int nReaction;
    u8 bKnock;
    int pSource;
    int w[2];
};

struct HitPacket {
    u32 flags00;
    Vec3 normal;
    u32 field10;
    u32 field14;
    void *pPart;
    u8 bKnock;
    u32 tail[3];
};

struct ChargeState {
    int pOwner;             /* +0x00 */
    int pad04;
    Vec3 *pPos;             /* +0x08 */
    char pad0c[0x10];
    unsigned long long mask; /* +0x1c */
    int pad24;
    int nHeading;           /* +0x28 */
    int nClock;             /* +0x2c */
};

typedef int (*HitHook)(u16 id, struct HitPacket40 *packet);

extern int func_ov107_020c8eb8(int owner, Sphere *query, int *out);
extern int func_02023eb4(int bound);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern struct ListNode *func_01fffd70(void *list);
extern struct ListNode *func_01fffd8c(void *list);
extern int func_ov107_020c3504(void *part, Sphere *shape, int flag);
extern int func_ov107_020c5cfc(struct Obj *obj, int target, struct HitPacket *packet);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov238_020d3184(int *node)
{
    struct ChargeState *st = (struct ChargeState *)node[1];
    Sphere sphere;
    Vec3 dir;
    int hits[4];
    struct HitPacket40 packet1 = {0};
    Vec3 at;
    long n;
    long i;
    int partner = *(int *)(st->pOwner + 0x398);
    int bit;
    struct Obj *obj;
    struct ListNode *ln;
    struct ListNode *part;
    int world;

    if (st->nClock >= 0x2a8 && st->nClock < 0x17e8) {
        int idx = ANG2IDX(st->nHeading) * 2;

        dir.y = 0;
        dir.x = data_0203d210[idx];
        dir.z = data_0203d210[idx + 1];
        sphere.pos = *st->pPos;
        if (st->nClock < 0x17e8 - 0xaa0) {
            sphere.nRadius = st->nClock + 0xe00;
        } else {
            sphere.nRadius = 0x17e8 + 0x360;
        }
        n = func_ov107_020c8eb8(st->pOwner, &sphere, hits);
        i = 0;
        if (n > 0) {
            do {
                bit = 1 << *(u16 *)(hits[i] + 2);
                if ((st->mask & (long long)bit) == 0 && *(HitHook *)(hits[i] + 0x1c4) != 0) {
                    packet1.vNormal = dir;
                    packet1.nKind |= 1;
                    packet1.nPower = ((u16 *)partner)[0x14b];
                    if ((((u8 *)(partner + 0x292))[1] & 1) != 0) {
                        packet1.nKind |= 0x20;
                    }
                    if ((((u8 *)(partner + 0x292))[1] & 2) != 0) {
                        packet1.nKind |= 0x40;
                    }
                    packet1.nReaction = *(short *)(st->pOwner + func_02023eb4(4) * 2 + 0x39c);
                    packet1.bKnock = 100;
                    packet1.pSource = *(int *)(st->pOwner + 0x398);
                    if ((*(HitHook *)(hits[i] + 0x1c4))(*(u16 *)(hits[i] + 2), &packet1) != 0) {
                        at = *(Vec3 *)(hits[i] + 0x190);
                        *(int *)(st->pOwner + 0x394) = 1;
                        st->mask |= (long long)bit;
                        at.y += 0x1800;
                        func_ov107_020c0b90(*(int *)(st->pOwner + 0x398), 3, at, 0);
                    }
                }
            } while (++i < n);
        }
        world = *(int *)(st->pOwner + 4);
        {
            struct HitPacket packet2 = {0};

            packet2.flags00 = packet2.flags00 & 0xffff0000 | 4;
            packet2.flags00 = (u16)packet2.flags00 |
                              (u32)*(short *)(st->pOwner + func_02023eb4(4) * 2 + 0x39c) << 16;
            packet2.field10 = packet2.field10 & 0xffff0000 | ((struct Rider *)*(int *)(st->pOwner + 0x398))->atk[1].power;
            packet2.field14 = packet2.field14 & 0xffff0000 | (u16)*(int *)(st->pOwner + 0x258);
            packet2.bKnock = 100;
            packet2.normal = dir;
            ln = func_01fffd70((char *)world + 0x80);
            obj = ln == 0 ? 0 : (struct Obj *)ln->item;
            while (obj != 0) {
                if ((st->mask >> obj->id002 & 1) == 0 && obj != *(struct Obj **)(st->pOwner + 0x398) &&
                    (obj->lo060 & 1) != 0 && (obj->attr1ac & 7) == 0) {
                    for (part = func_01fffd70((char *)obj + 0x22c); part != 0;
                         part = func_01fffd8c((char *)obj + 0x22c)) {
                        if ((((struct W8 *)((char *)part + 8))->lo & 1) != 0 &&
                            func_ov107_020c3504(part->item, &sphere, 0) != 0) {
                            packet2.pPart = part;
                            if (func_ov107_020c5cfc(obj, *(int *)(st->pOwner + 0x25c), &packet2) != 0) {
                                st->mask = st->mask | (unsigned long long)1 << obj->id002;
                                break;
                            }
                        }
                    }
                }
                ln = func_01fffd8c((char *)world + 0x80);
                obj = ln == 0 ? 0 : (struct Obj *)ln->item;
            }
        }
    }
    st->nClock += *(int *)(node[0] + 0x2c);
    if (st->nClock < 0x1fe0) {
        return;
    }
    *(int *)(st->pOwner + 0x390) = 0;
    *(u8 *)(st->pOwner + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
