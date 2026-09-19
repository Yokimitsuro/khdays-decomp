/* Hit handler of the ov225 enemy. The hit's source is kept at +0x10 of the work; a locked
 * actor (+0x1ac bit 0) or one without hit points ignores the hit. With a +0x78 target, a hit on
 * the object's +0x3b0 or +0x3ac body only requests sub-state 7 out of sub-states 2/6 and is
 * otherwise ignored; without one a +0x3b0 body hit is ignored. Sub-state 9 tags the hit with
 * reaction 2 (4 without a target), 0xb with 3. A 0x4000 hit only sets bit 0 of the result and
 * returns. The hit points drain, floored at 0 and capped at the +0x218 floor. A damaging hit that
 * is not the 8/0x80/kind-0x80 kind fires reaction 0x14b with the +0x77 side's mode from the
 * overlay's hurt (bits 1/5) or idle table, then flips the side. Empty hit points request
 * sub-state 3; sub-state 9 with a target and a 1/0x10 hit requests 0xa. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Ov225Vec3 { int x, y, z; };

struct Ov225ModePair { u8 nFirst; u8 nSecond; };
union Ov225ModeSlot { struct Ov225ModePair sPair; u8 aModes[2]; };
struct Ov225ReactionModes {
    struct Ov225ModePair idle;
    struct Ov225ModePair hurt;
};

struct Ov225HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};

struct Ov225Hit {
    unsigned int flags;
    struct Ov225Vec3 position;
    char pad10[4];
    int kind14;
    int body18;
    char pad1c[4];
    int reaction20;
    unsigned int resultFlags24;
    int damage28;
};

struct Ov225ReactionObject {
    char pad000[0x1c6];
    signed char state1c6;
    u8 nextState1c7;
    char pad1c8[0x1e4];
    int body3ac;
    int body3b0;
};

struct Ov225ReactionWork {
    struct Ov225ReactionObject *object00;
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

struct Ov225ActorHitState {
    char pad000[0x1ac];
    u16 flags1ac;
    char pad1ae[0x66];
    struct Ov225ReactionWork *work214;
    short hitFloor218;
    short hitPoints21a;
};

extern const struct Ov225ReactionModes data_ov225_020d50b4;
extern int func_ov107_020c89e8(struct Ov225ActorHitState *self, struct Ov225Hit *hit);
extern void func_ov107_020c5af8(struct Ov225ActorHitState *self, int reactionId, u8 mode, int context);

int func_ov225_020d0710(struct Ov225ActorHitState *self, int source, struct Ov225Hit *hit)
{
    struct Ov225ReactionWork *work = self->work214;
    int delta;
    int remaining;
    struct Ov225HitFlags *flags;

    work->source10 = source;
    if (self->flags1ac & 1) {
        return 0;
    }
    if (self->hitPoints21a <= 0) {
        return 0;
    }

    if (work->target78 != 0
        && (hit->body18 == work->object00->body3b0 || hit->body18 == work->object00->body3ac)) {
        switch (work->object00->state1c6) {
        case 2:
        case 6:
            work->object00->nextState1c7 = 7;
            return 1;
        }
        return 0;
    }
    if (hit->body18 == work->object00->body3b0) {
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
    flags = (struct Ov225HitFlags *)hit;

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
                union Ov225ModeSlot uSlot;

                uSlot.sPair = data_ov225_020d50b4.hurt;
                func_ov107_020c5af8(self, 0x14b, uSlot.aModes[work->side77], work->reactionContext08);
            } else {
                union Ov225ModeSlot uSlot;

                uSlot.sPair = data_ov225_020d50b4.idle;
                func_ov107_020c5af8(self, 0x14b, uSlot.aModes[work->side77], work->reactionContext08);
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

    return 1;
}
