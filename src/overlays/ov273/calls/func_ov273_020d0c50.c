/*
 * Hit handler of the ov273 actor, the func_ov191_020d0408 shape. A hit is refused once the
 * stagger timer (+0x21a) has run out. Sub-states 8/9/0xb/0xc/0xe publish 2/3/4/1/0 into the
 * event's mode field; the parameter is kept at +0x20; the ov107 charge decides the damage; flag
 * 0x4000 sets the result's low half and goes to sub-state 6. The damage drains the stagger
 * timer (clamped to the +0x218 cap, floored at zero) -- an emptied timer ends in sub-state 3,
 * while sub-state 9 with a flag-0x20 hit requests 0xa. A hit that dealt damage (+0x10 low half) flips the state's
 * facing bit (+0x6b bit 0) and fires reaction 0x162 at the +4 position, modes 2/3 for flag-2 hits
 * and 0/1 otherwise, except for kind-0x80 hits carrying both flag 8 and flag 0x80.
 */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov273ActionState {
    int pOwner;
    void *pPos;
    char pad008[0x18];
    int nParam;
    char pad024[0x47];
    u8 bFacing : 1;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    int nDealt10 : 16;
    int pad12 : 16;
    char pad014[4];
    int pSource18;
    char pad01c[4];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, unsigned short mode, void *anchor);

int func_ov273_020d0c50(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov273ActionState *state = *(struct Ov273ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 0xe:
        hit->uMode20 = 0;
        break;
    case 9:
        hit->uMode20 = 3;
        break;
    case 0xb:
        hit->uMode20 = 4;
        break;
    case 0xc:
        hit->uMode20 = 1;
        break;
    case 8:
        hit->uMode20 = 2;
        break;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
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
    state->nParam = nParam;
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if (*(signed char *)(state->pOwner + 0x1c6) == 9) {
        if ((hit->uFlagsLo & 0x20) != 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 0xa;
        }
    }
    if (hit->nDealt10 > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 2) != 0) {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x162, (state->bFacing & 1) ? 2 : 3, state->pPos);
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x162, (state->bFacing & 1) ? 0 : 1, state->pPos);
            }
        }
    }
    return 1;
}
