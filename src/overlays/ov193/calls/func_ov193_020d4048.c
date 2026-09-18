/*
 * Hit handler of the ov191 enemy (x3: ov191/192/193), the func_ov120_020cc568 shape. A hit is
 * refused once the stagger timer (+0x21a) has run out. Sub-state 6 publishes 1 into the event's
 * mode field and the damage starts at 0; a hit whose +0x18 source is the actor's own +0x388 item
 * only sets the result's low half to 1. Otherwise the ov107 charge decides the damage; flag
 * 0x4000 sets the result and goes to sub-state 5; the damage drains the stagger timer (clamped
 * to the +0x218 cap, floored at zero) -- an emptied timer ends in sub-state 3, a 0xa000 flag in 5.
 * A hit that charged flips the state's facing bit (+0x39 bit 0) and fires reaction 0x133 at the
 * pool node's +0x14, modes 2/3 for flag-0x22 hits and 0/1 otherwise, except for kind-0x80 hits
 * carrying both flag 8 and flag 0x80.
 */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov191ActionState {
    int pOwner;
    char pad004[0x35];
    u8 bFacing : 1;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    char pad010[8];
    int pSource18;
    char pad01c[4];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, unsigned short mode, void *anchor);

int func_ov193_020d4048(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov191ActionState *state = *(struct Ov191ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if (*(signed char *)(state->pOwner + 0x1c6) == 6) {
        hit->uMode20 = 1;
    }
    hit->nDamage = 0;
    if (hit->pSource18 == *(int *)(actor + 0x388)) {
        hit->uResultLo = 1;
        return 1;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        *(u8 *)(state->pOwner + 0x1c7) = 5;
        return 1;
    }
    delta = *(short *)(actor + 0x21a) - hit->nDamage;
    if (delta < 0) {
        rem = 0;
    } else {
        rem = *(short *)(actor + 0x218);
        if (delta <= rem) {
            rem = delta;
        }
    }
    *(short *)(actor + 0x21a) = (short)rem;
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if ((hit->uFlagsLo & 0xa000) != 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 5;
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x133, (state->bFacing & 1) ? 2 : 3,
                                    (void *)(*(int *)(state->pOwner + 0x398) + 0x14));
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x133, (state->bFacing & 1) ? 0 : 1,
                                    (void *)(*(int *)(state->pOwner + 0x398) + 0x14));
            }
        }
    }
    return 1;
}
