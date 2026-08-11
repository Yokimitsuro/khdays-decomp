typedef unsigned char u8;
typedef unsigned short u16;

struct Ov281Vec3 { int x, y, z; };

struct Ov281ReactionModes {
    u8 normal[2];
    u8 special[2];
};

struct Ov281HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};

struct Ov281Hit {
    unsigned int flags;
    struct Ov281Vec3 position;
    char pad10[0x10];
    int reaction20;
    unsigned int resultFlags24;
    int damage28;
};

struct Ov281ReactionObject {
    char pad000[0x1c6];
    signed char state1c6;
    u8 nextState1c7;
};

struct Ov281ReactionWork {
    struct Ov281ReactionObject *object00;
    char pad004[0x08];
    int reactionContext0c;
    char pad010[0x1c];
    struct Ov281Vec3 position2c;
    int source38;
    char pad03c[0x02];
    u8 facing3e;
};

struct Ov281ActorHitState {
    char pad000[0x1ac];
    u16 flags1ac;
    char pad1ae[0x66];
    struct Ov281ReactionWork *work214;
    short hitFloor218;
    short hitPoints21a;
};

extern const struct Ov281ReactionModes data_ov281_020ce468;
extern int func_ov107_020c89e8(struct Ov281ActorHitState *self,
                               struct Ov281Hit *hit);
extern void func_ov107_020c5af8(struct Ov281ActorHitState *self,
                                int reactionId, u8 mode, int context);

/* Apply a hit, alternate its reaction mode and request the actor's resulting state. */
int func_ov281_020cc838(struct Ov281ActorHitState *self, int source,
                        struct Ov281Hit *hit)
{
    u8 normalModes[2] = {
        data_ov281_020ce468.normal[0],
        data_ov281_020ce468.normal[1]
    };
    u8 specialModes[2] = {
        data_ov281_020ce468.special[0],
        data_ov281_020ce468.special[1]
    };
    struct Ov281ReactionWork *work = self->work214;
    int delta;
    int remaining;
    struct Ov281HitFlags *flags;

    if (self->flags1ac & 1) {
        return 0;
    }
    if (self->hitPoints21a <= 0) {
        return 0;
    }

    switch (work->object00->state1c6) {
    case 6:
        hit->reaction20 = 0;
        break;
    case 7:
        hit->reaction20 = 1;
        break;
    case 9:
        hit->reaction20 = 2;
        break;
    }

    work->position2c = hit->position;
    hit->damage28 = func_ov107_020c89e8(self, hit);

    if (((u16)hit->flags & 0x4000) != 0) {
        hit->resultFlags24 = (hit->resultFlags24 & 0xffff0000) | 1;
        work->object00->nextState1c7 = 5;
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
    work->source38 = source;

    if (hit->damage28 > 0) {
        flags = (struct Ov281HitFlags *)hit;
        if ((flags->low & 8) == 0 || (flags->low & 0x80) == 0 ||
            flags->kind != 0x80) {
            if ((flags->low & 0x22) != 0) {
                work->facing3e = work->facing3e + 1;
                func_ov107_020c5af8(self, 0x169,
                                    specialModes[work->facing3e & 1],
                                    work->reactionContext0c);
            } else {
                work->facing3e = work->facing3e + 1;
                func_ov107_020c5af8(self, 0x169,
                                    normalModes[work->facing3e & 1],
                                    work->reactionContext0c);
            }
        }
    }

    if (self->hitPoints21a == 0) {
        work->object00->nextState1c7 = 3;
        return 1;
    }

    if ((work->object00->state1c6 == 7 || work->object00->state1c6 == 9) &&
        (((u16)hit->flags & 1) != 0) &&
        (((u16)hit->flags & 0x10) != 0)) {
        work->object00->nextState1c7 = 8;
        return 1;
    }

    if (((u16)hit->flags & 0x8000) != 0) {
        work->object00->nextState1c7 = 5;
    }
    return 1;
}
