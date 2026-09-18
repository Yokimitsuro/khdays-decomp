/*
 * Hit handler of the ov181 enemy (x4: ov181/182/183/184), the func_ov191_020d0408 shape. A hit
 * is refused once the stagger timer (+0x21a) has run out. A hit carrying flags 1 and 0x10 while
 * the sub-state is 9 only requests sub-state 10. Sub-states 7/8/9 publish 0/1/2 into the event's
 * mode field; the hit point is copied into +0x60 and the parameter into +0x24; the ov107 charge
 * decides the damage; flag 0x4000 sets the result's low half and goes to sub-state 6. The damage
 * drains the stagger timer (clamped to the +0x218 cap, floored at zero) -- an emptied timer ends
 * in sub-state 3, a 0x8000 flag in 6. A hit that charged flips the state's facing bit (+0x51
 * bit 0) and fires reaction 0x131 at the +8 position, modes 2/3 for flag-0x22 hits and 0/1
 * otherwise, except for kind-0x80 hits carrying both flag 8 and flag 0x80.
 */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov181ActionState {
    int pOwner;
    char pad004[4];
    void *pPos;
    char pad00c[0x18];
    int nParam;
    char pad028[0x29];
    u8 bFacing : 1;
    char pad052[0xe];
    struct Vec3 vHit;
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

int func_ov183_020d008c(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov181ActionState *state = *(struct Ov181ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if ((hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
        if (*(signed char *)(state->pOwner + 0x1c6) == 9) {
            *(u8 *)(state->pOwner + 0x1c7) = 10;
            return;
        }
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 7:
        hit->uMode20 = 0;
        break;
    case 8:
        hit->uMode20 = 1;
        break;
    case 9:
        hit->uMode20 = 2;
        break;
    }
    state->vHit = hit->vPoint;
    state->nParam = nParam;
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        *(u8 *)(state->pOwner + 0x1c7) = 6;
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
        *(u8 *)(state->pOwner + 0x1c7) = 6;
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x131, (state->bFacing & 1) ? 2 : 3, state->pPos);
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x131, (state->bFacing & 1) ? 0 : 1, state->pPos);
            }
        }
    }
    return 1;
}
