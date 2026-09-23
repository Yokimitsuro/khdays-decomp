/* Hit handler of the ov227 enemy. The hit's source is kept at +0x10 of the work; a locked
 * actor (+0x1ac bit 0) or one without hit points ignores the hit. Sub-state 9 tags the hit with
 * reaction 2 (4 without a +0x78 target), 0xb with 3. The damage comes from ov107 c89e8. A 0x4000 hit only
 * sets bit 0 of the result and returns. The hit points drain, floored at 0 and capped at the
 * +0x218 floor. A damaging hit that is not the 8/0x80/kind-0x80 kind fires reaction 0x14d with the
 * +0x77 side's mode from the overlay's hurt (bits 1/5) or idle table, then flips the side.
 * Empty hit points request sub-state 3; sub-state 9 with a target and a 1/0x10 hit requests 0xa;
 * otherwise, off game mode 8 with a target and outside sub-state 0xd, a damaging hit counts
 * down the +0x74 hits and requests 0xd when they run out or the hit's +0x14 kind is 0x6b. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Ov227Vec3 { int x, y, z; };

struct Ov227ModePair { u8 nFirst; u8 nSecond; };
union Ov227ModeSlot { struct Ov227ModePair sPair; u8 aModes[2]; };
struct Ov227ReactionModes {
    struct Ov227ModePair idle;
    struct Ov227ModePair hurt;
};

struct Ov227HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};

struct Ov227Hit {
    unsigned int flags;
    struct Ov227Vec3 position;
    char pad10[4];
    int kind14;
    int body18;
    char pad1c[4];
    int reaction20;
    unsigned int resultFlags24;
    int damage28;
};

struct Ov227ReactionObject {
    char pad000[0x1c6];
    signed char state1c6;
    u8 nextState1c7;
    char pad1c8[0x1e4];
    int body3ac;
};

struct Ov227ReactionWork {
    struct Ov227ReactionObject *object00;
    char pad004[4];
    int reactionContext08;
    char pad00c[4];
    int source10;
    char pad014[0x60];
    signed char hitsLeft74;
    char pad075[2];
    u8 side77;
    int target78;
};

struct Ov227ActorHitState {
    char pad000[0x1ac];
    u16 flags1ac;
    char pad1ae[0x66];
    struct Ov227ReactionWork *work214;
    short hitFloor218;
    short hitPoints21a;
};

extern const struct Ov227ReactionModes data_ov227_020d4b54;
extern int func_ov107_020c89e8(struct Ov227ActorHitState *self, struct Ov227Hit *hit);
extern void func_ov107_020c5af8(struct Ov227ActorHitState *self, int reactionId, u8 mode, int context);
extern int func_ov002_0207298c(void);

int func_ov227_020d0720(struct Ov227ActorHitState *self, int source, struct Ov227Hit *hit)
{
    struct Ov227ReactionWork *work = self->work214;
    int delta;
    int remaining;
    struct Ov227HitFlags *flags;

    work->source10 = source;
    if (self->flags1ac & 1) {
        return 0;
    }
    if (self->hitPoints21a <= 0) {
        return 0;
    }

    switch (work->object00->state1c6) {
    case 9:
        hit->reaction20 = work->target78 != 0 ? 2 : 4;
        break;
    case 0xb:
        hit->reaction20 = 3;
        break;
    }

    hit->damage28 = func_ov107_020c89e8(self, hit);
    flags = (struct Ov227HitFlags *)hit;

    if (((u16)hit->flags & 0x4000) != 0) {
        hit->resultFlags24 = (hit->resultFlags24 & 0xffff0000) | 1;
        return 1;
    }

    delta = self->hitPoints21a - hit->damage28;
    if (delta < 0) {
        remaining = 0;
    } else {
        remaining = self->hitFloor218;
        if (delta <= remaining) {
            remaining = delta;
        }
    }
    self->hitPoints21a = (short)remaining;

    if (hit->damage28 > 0) {
        if ((flags->low & 8) == 0 || (flags->low & 0x80) == 0 || flags->kind != 0x80) {
            if ((flags->low & 0x22) != 0) {
                union Ov227ModeSlot uSlot;

                uSlot.sPair = data_ov227_020d4b54.hurt;

                func_ov107_020c5af8(self, 0x14d, uSlot.aModes[work->side77], work->reactionContext08);
            } else {
                union Ov227ModeSlot uSlot;

                uSlot.sPair = data_ov227_020d4b54.idle;
                func_ov107_020c5af8(self, 0x14d, uSlot.aModes[work->side77], work->reactionContext08);
            }
            work->side77 ^= 1;
        }
    }

    if (self->hitPoints21a == 0) {
        work->object00->nextState1c7 = 3;
        return 1;
    }

    if (work->object00->state1c6 == 9 && work->target78 != 0
        && ((u16)hit->flags & 1) != 0 && ((u16)hit->flags & 0x10) != 0) {
        work->object00->nextState1c7 = 0xa;
        return 1;
    }

    if (func_ov002_0207298c() != 8 && work->target78 != 0
        && work->object00->state1c6 != 0xd && hit->damage28 > 0) {
        work->hitsLeft74 = work->hitsLeft74 - 1;
        if (work->hitsLeft74 <= 0 || (hit->kind14 >> 16) == 0x6b) {
            work->object00->nextState1c7 = 0xd;
        }
    }
    return 1;
}
