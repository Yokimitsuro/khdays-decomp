/*
 * Hit handler of the ov134 enemy (and its byte-identical twins), the func_ov181_020cc44c shape. A hit is
 * refused once the stagger timer (+0x21a) has run out. Sub-states 6/7/0xf publish 0/1/2 into
 * the event's mode field; the ov107 charge decides the damage; flag 0x4000 copies the hit point
 * into +0x24, sets the result's low half and goes to sub-state 5. The damage drains the stagger
 * timer (clamped to the +0x218 cap, floored at zero) -- an emptied timer ends in sub-state 3;
 * otherwise sub-state 8 is left alone, sub-state 7 turns into 8 for a hit carrying flags 1 and
 * 0x10, and any other 0x8000 hit goes to 5. The parameter lands in +0x38 and the hit point in
 * +0x24; a hit that charged flips the state's facing bit (+0x52 bit 0) and fires reaction 0x11c
 * at the +0x40 position, modes 2/3 for flag-0x22 hits and 0/1 otherwise, except for kind-0x80
 * hits carrying both flag 8 and flag 0x80.
 */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov134ActionState {
    int pOwner;
    char pad004[0x20];
    struct Vec3 vHit;
    char pad030[4];
    int nParam;
    void *pPos;
    char pad03c[6];
    u8 bHit : 1;
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

int func_ov135_020d01e0(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov134ActionState *state = *(struct Ov134ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 6:
        hit->uMode20 = 0;
        break;
    case 7:
        hit->uMode20 = 1;
        break;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        state->vHit = hit->vPoint;
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
    } else if (*(signed char *)(state->pOwner + 0x1c6) == 7 && (hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 8;
    } else if ((hit->uFlagsLo & 0x8000) != 0) {
        if (*(signed char *)(state->pOwner + 0x1c6) != 8) {
            *(u8 *)(state->pOwner + 0x1c7) = 5;
        }
        state->bHit = 1;
    }
    state->nParam = nParam;
    state->vHit = hit->vPoint;
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11c, (state->bFacing & 1) ? 2 : 3, state->pPos);
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11c, (state->bFacing & 1) ? 0 : 1, state->pPos);
            }
        }
    }
    return 1;
}
