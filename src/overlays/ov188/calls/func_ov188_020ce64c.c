typedef unsigned char u8;
typedef unsigned short u16;

struct Ov188Vec3 {
    int x;
    int y;
    int z;
};

struct Ov188ReactionModes {
    u8 normal[2];
    u8 special[2];
};

struct Ov188HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};

struct Ov188Hit {
    unsigned int flags;
    struct Ov188Vec3 position;
    char pad10[0x10];
    int reaction20;
    unsigned int resultFlags24;
    int damage28;
};

struct Ov188ReactionObject {
    char pad000[0x1c6];
    signed char state1c6;
    u8 nextState1c7;
};

struct Ov188ReactionWork {
    struct Ov188ReactionObject *object00;
    char pad004[0x08];
    int reactionContext0c;
    char pad010[0x1c];
    struct Ov188Vec3 position2c;
    int source38;
    char pad03c[0x02];
    u8 facing3e;
};

struct Ov188ActorHitState {
    char pad000[0x1ac];
    u16 flags1ac;
    char pad1ae[0x66];
    struct Ov188ReactionWork *work214;
    short hitFloor218;
    short hitPoints21a;
};

extern const struct Ov188ReactionModes data_ov188_020d0278;
extern int func_ov107_020c89e8(struct Ov188ActorHitState *self,
                               struct Ov188Hit *hit);
extern void func_ov107_020c5af8(struct Ov188ActorHitState *self,
                                int reactionId, u8 mode, int context);

int func_ov188_020ce64c(struct Ov188ActorHitState *self, int source,
                        struct Ov188Hit *hit)
{
    u8 normalModes[2] = {
        data_ov188_020d0278.normal[0],
        data_ov188_020d0278.normal[1]
    };
    u8 specialModes[2] = {
        data_ov188_020d0278.special[0],
        data_ov188_020d0278.special[1]
    };
    struct Ov188ReactionWork *work = self->work214;
    int delta;
    int remaining;
    struct Ov188HitFlags *flags;

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
        flags = (struct Ov188HitFlags *)hit;
        if ((flags->low & 8) == 0 || (flags->low & 0x80) == 0 ||
            flags->kind != 0x80) {
            if ((flags->low & 0x22) != 0) {
                work->facing3e = work->facing3e + 1;
                func_ov107_020c5af8(self, 0x12f,
                                    specialModes[work->facing3e & 1],
                                    work->reactionContext0c);
            } else {
                work->facing3e = work->facing3e + 1;
                func_ov107_020c5af8(self, 0x12f,
                                    normalModes[work->facing3e & 1],
                                    work->reactionContext0c);
            }
        }
    }

    if (self->hitPoints21a == 0) {
        work->object00->nextState1c7 = 3;
        return 1;
    }

    if ((work->object00->state1c6 == 7 ||
         work->object00->state1c6 == 9) &&
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
