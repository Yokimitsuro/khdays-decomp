/* Hit filter of the ov257 enemy (+0x1d0): ignored once the hit points (+0x21a) are gone. The
 * damage (+0x28) is resolved (020c89e8); a guard hit (flag 0x4000) only reports 1 in +0x24.
 * Otherwise the damage is taken (clamped to [0, max]) and the source kept in the brain's +0x3c; a
 * damaging flag-4 hit from a source raises +0x79, blow hits (0x20) count in +0x89 and damaging
 * flag-4 hits in +0x88. A knockout requests sub-state 3; falling under 60% of the maximum the
 * first time (+0x7a) requests 0xb; a flag 1+0x10 hit on a kind-8 owner requests 0xa. */
typedef unsigned short u16;

struct HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};
struct Hit {
    unsigned int flags;
    char pad04[0x1c];
    int reaction20;
    unsigned int result24;
    int damage28;
};
struct Brain {
    int owner;
    char pad04[0x38];
    int source3c;
    char pad40[0x39];
    unsigned char struck79;
    unsigned char fled7a;
    char pad7b[0xd];
    signed char hits88;
    signed char blows89;
};
struct Actor {
    char pad000[0x214];
    struct Brain *brain214;
    short hitMax218;
    short hitPoints21a;
};

extern int func_ov107_020c89e8(struct Actor *self, struct Hit *hit);

int func_ov257_020ccde8(struct Actor *self, int source, struct Hit *hit)
{
    struct Brain *brain = self->brain214;
    struct HitFlags *flags;
    int delta;
    int remaining;

    if (self->hitPoints21a <= 0) {
        return 0;
    }
    hit->damage28 = func_ov107_020c89e8(self, hit);
    flags = (struct HitFlags *)hit;
    if (((u16)hit->flags & 0x4000) != 0) {
        hit->result24 = (hit->result24 & 0xffff0000) | 1;
        return 1;
    }
    delta = self->hitPoints21a - hit->damage28;
    if (delta < 0) {
        remaining = 0;
    } else {
        remaining = self->hitMax218;
        if (delta <= remaining) {
            remaining = delta;
        }
    }
    self->hitPoints21a = (short)remaining;
    brain->source3c = source;
    if (source != 0 && hit->damage28 > 0 && (flags->low & 4) != 0) {
        brain->struck79 = 1;
    }
    if ((flags->low & 0x20) != 0) {
        brain->blows89++;
    }
    if ((flags->low & 4) != 0 && hit->damage28 > 0) {
        brain->hits88++;
    }
    remaining = self->hitPoints21a;
    if (remaining == 0) {
        *(unsigned char *)(brain->owner + 0x1c7) = 3;
    } else if (brain->fled7a == 0 && remaining < self->hitMax218 * 60 / 100) {
        brain->fled7a = 1;
        *(unsigned char *)(brain->owner + 0x1c7) = 0xb;
    } else if ((flags->low & 1) != 0 && (flags->low & 0x10) != 0) {
        if (*(signed char *)(brain->owner + 0x1c6) == 8) {
            *(unsigned char *)(brain->owner + 0x1c7) = 0xa;
        }
    }
    return 1;
}
