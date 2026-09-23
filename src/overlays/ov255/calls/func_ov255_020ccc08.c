/* Hit filter of the ov255 enemy (+0x1d0): ignored once the hit points (+0x21a) are gone. The hit's
 * +0x20 reaction follows the owner's kind (+0x1c6: 8 -> 0, 9 -> 3, 0xa -> 4, 0xb -> 5, 0xc -> 6)
 * and its damage (+0x28) is resolved (020c89e8); a guard hit (flag 0x4000) only reports 1 in
 * +0x24. Otherwise the damage is taken (clamped to [0, max]), the source is kept in the brain's
 * +0x3c, blow hits (0x20) count in +0x79 and damaging flag-4 hits in +0x78; a knockout requests
 * sub-state 3, and a flag 1+0x10 hit on a kind-8 owner requests 0xa. */
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
    char pad40[0x38];
    signed char hits78;
    signed char blows79;
};
struct Actor {
    char pad000[0x214];
    struct Brain *brain214;
    short hitMax218;
    short hitPoints21a;
};

extern int func_ov107_020c89e8(struct Actor *self, struct Hit *hit);

int func_ov255_020ccc08(struct Actor *self, int source, struct Hit *hit)
{
    struct Brain *brain = self->brain214;
    struct HitFlags *flags;
    int delta;
    int remaining;

    if (self->hitPoints21a <= 0) {
        return 0;
    }
    switch (*(signed char *)(brain->owner + 0x1c6)) {
    case 8:
        hit->reaction20 = 0;
        break;
    case 9:
        hit->reaction20 = 3;
        break;
    case 10:
        hit->reaction20 = 4;
        break;
    case 11:
        hit->reaction20 = 5;
        break;
    case 12:
        hit->reaction20 = 6;
        break;
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
    if ((flags->low & 0x20) != 0) {
        brain->blows79++;
    }
    if ((flags->low & 4) != 0 && hit->damage28 > 0) {
        brain->hits78++;
    }
    if (self->hitPoints21a == 0) {
        *(unsigned char *)(brain->owner + 0x1c7) = 3;
    } else if ((flags->low & 1) != 0 && (flags->low & 0x10) != 0) {
        if (*(signed char *)(brain->owner + 0x1c6) == 8) {
            *(unsigned char *)(brain->owner + 0x1c7) = 0xa;
        }
    }
    return 1;
}
