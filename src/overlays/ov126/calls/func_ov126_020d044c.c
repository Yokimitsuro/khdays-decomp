/*
 * Hit handler of the ov125 enemy, the func_ov120_020cc568 shape. A hit is refused once the
 * stagger timer (+0x21a) has run out. The hit's parameter is kept at state+0x30 and its point
 * at state+0x14; sub-state 6 publishes 1 into the event's mode field and sub-state 7 clears it.
 * The ov107 charge decides the damage; flag 0x4000 sets the result and goes to sub-state 8;
 * the damage drains the stagger timer (clamped to the +0x218 cap, floored at zero) -- an
 * emptied timer ends in sub-state 3, a 0x8000 flag in 6 (with 0x2000) or 8. A hit that charged
 * flips the state's facing bit (+0x34 bit 0) and fires reaction 0x11b at the state's +0x24
 * anchor, modes 2/3 for flag-0x22 hits and 0/1 otherwise, except for kind-0x80 hits carrying
 * both flag 8 and flag 0x80.
 */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov125ActionState {
    int pOwner;
    char pad004[0x10];
    struct Vec3 vPoint;
    char pad020[4];
    void *pAnchor;
    char pad028[8];
    int nParam;
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

int func_ov126_020d044c(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov125ActionState *state = *(struct Ov125ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    state->nParam = nParam;
    state->vPoint = hit->vPoint;
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 6:
        hit->uMode20 = 1;
        break;
    case 7:
        hit->uMode20 = 0;
        break;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        *(u8 *)(state->pOwner + 0x1c7) = 8;
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
    } else if ((hit->uFlagsLo & 0x8000) != 0) {
        if ((hit->uFlagsLo & 0x2000) != 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 6;
        } else {
            *(u8 *)(state->pOwner + 0x1c7) = 8;
        }
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11b, (state->bFacing & 1) ? 2 : 3, state->pAnchor);
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11b, (state->bFacing & 1) ? 0 : 1, state->pAnchor);
            }
        }
    }
    return 1;
}
