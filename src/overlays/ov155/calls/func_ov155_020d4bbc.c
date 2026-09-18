/*
 * Hit handler of the ov153 enemy (x3: ov153/154/155), the func_ov191_020d0408 shape. A hit is
 * refused once the stagger timer (+0x21a) has run out. The ov107 charge decides the damage,
 * which drains the stagger timer (clamped to the +0x218 cap, floored at zero) -- an emptied
 * timer ends in sub-state 3, a 0x8000 flag in 5. A hit that charged bumps the state's +0x25
 * facing counter and fires reaction 0x13c at the state's +8 position, modes 2/3 for flag-0x22
 * hits and 0/1 otherwise, except for kind-0x80 hits carrying both flag 8 and flag 0x80.
 */
typedef unsigned char u8;

struct Ov153ActionState {
    int pOwner;
    char pad004[4];
    void *pPos;
    char pad00c[0x19];
    u8 nFacing;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    char pad004[0x24];
    int nDamage;
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, unsigned short mode, void *anchor);

int func_ov155_020d4bbc(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov153ActionState *state = *(struct Ov153ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
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
                state->nFacing = state->nFacing + 1;
                func_ov107_020c5af8(actor, 0x13c, (state->nFacing & 1) ? 2 : 3, state->pPos);
            } else {
                state->nFacing = state->nFacing + 1;
                func_ov107_020c5af8(actor, 0x13c, (state->nFacing & 1) ? 0 : 1, state->pPos);
            }
        }
    }
    return 1;
}
