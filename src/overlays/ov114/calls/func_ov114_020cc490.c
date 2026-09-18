/* Hit handler of the ov114 enemy. A hit is refused once the stagger timer (+0x21a) has run
 * out (the owner's copy decides the emptied case). Sub-states 9/0xa publish 0/1 into the event's mode field; the hit point is kept at
 * the state's +0x5c before the ov107 charge decides the damage. Flag 0x4000 sets the result
 * and goes to sub-state 5; otherwise the damage drains the stagger timer (clamped to the
 * +0x218 cap, floored at zero) -- an emptied timer ends in sub-state 3, a 0x8000 flag in 5.
 * A hit that charged flips the state's facing bit (+0x4a bit 0) and fires reaction 0x112 at
 * the state's +8 anchor, modes 2/3 for flag-0x22 hits and 0/1 otherwise, except for kind-0x80
 * hits carrying both flag 8 and flag 0x80. */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov114ActionState {
    int pOwner;
    char pad004[4];
    void *pAnchor;
    char pad00c[0x50];
    struct Vec3 vHit;           /* +0x5c */
};

struct Ov114Facing {
    char pad000[0x4a];
    u8 bFacing : 1;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    char pad010[0x10];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, unsigned short mode, void *anchor);

int func_ov114_020cc490(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov114ActionState *state = *(struct Ov114ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 9:
        hit->uMode20 = 0;
        break;
    case 0xa:
        hit->uMode20 = 1;
        break;
    }
    state->vHit = hit->vPoint;
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
    if (*(short *)(state->pOwner + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if ((hit->uFlagsLo & 0x8000) != 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 5;
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                ((struct Ov114Facing *)state)->bFacing = ((struct Ov114Facing *)state)->bFacing + 1;
                func_ov107_020c5af8(actor, 0x112, (((struct Ov114Facing *)state)->bFacing & 1) ? 2 : 3, state->pAnchor);
            } else {
                ((struct Ov114Facing *)state)->bFacing = ((struct Ov114Facing *)state)->bFacing + 1;
                func_ov107_020c5af8(actor, 0x112, (((struct Ov114Facing *)state)->bFacing & 1) ? 0 : 1, state->pAnchor);
            }
        }
    }
    return 1;
}
