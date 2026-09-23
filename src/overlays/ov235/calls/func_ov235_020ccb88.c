/* Hit filter of the ov235 enemy, active while the +0x21a hit points are positive. The damage comes
 * from ov107 c89e8; a 0x4000 hit only sets bit 0 of the result. Otherwise the hit points drain
 * (floored at 0, capped at the +0x218 maximum), the source is kept at +0x3c of the brain, a 0x20 hit
 * counts at +0x8d and a damaging 4 hit at +0x8c. Empty hit points request sub-state 3; a 1|0x10 hit
 * in sub-state 8 requests 0xa. */
typedef unsigned short u16;

struct HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};
struct Hit {
    unsigned int flags;
    char pad04[0x20];
    unsigned int result24;
    int damage28;
};
struct Brain {
    int owner;
    char pad04[0x38];
    int source3c;
    char pad40[0x4c];
    signed char hits8c;
    signed char blows8d;
};
struct Actor {
    char pad000[0x214];
    struct Brain *brain214;
    short hitMax218;
    short hitPoints21a;
};

extern int func_ov107_020c89e8(struct Actor *self, struct Hit *hit);

int func_ov235_020ccb88(struct Actor *self, int source, struct Hit *hit)
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
    if ((flags->low & 0x20) != 0) {
        brain->blows8d++;
    }
    if ((flags->low & 4) != 0 && hit->damage28 > 0) {
        brain->hits8c++;
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
