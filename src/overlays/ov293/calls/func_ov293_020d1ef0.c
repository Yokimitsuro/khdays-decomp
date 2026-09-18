/* Hit handler of the ov293 enemy. A hit is refused once the stagger timer (+0x21a) has run
 * out. The parameter goes to the state's +0x48 and the hit point to +0x34. In sub-state 6 a
 * hit carrying flags 1 and 0x10 asks for sub-state 7 at once; sub-state 6 otherwise publishes
 * mode 0 before the ov107 charge decides the damage. Flag 0x4000 sets the result and goes to
 * sub-state 5; otherwise the damage drains the stagger timer (clamped to the +0x218 cap,
 * floored at zero) -- an emptied timer records the parameter in the overlay's +0x3660 pair
 * (kind 0) and ends in sub-state 3, a 0x8000 flag in 5. A hit that charged flips the state's
 * facing bit (+0x50 bit 0) and fires reaction 0x11a at the state's +8 anchor, modes 2/3 for
 * flag-0x22 hits and 0/1 otherwise, except for kind-0x80 hits carrying both flag 8 and flag
 * 0x80. */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov293ActionState {
    int pOwner;
    char pad004[4];
    void *pAnchor;
    char pad00c[0x28];
    struct Vec3 vHit;           /* +0x34 */
    char pad040[8];
    int nParam;                 /* +0x48 */
};

struct Ov293Facing {
    char pad000[0x50];
    u8 bFacing : 1;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    int nDamage10;
    char pad014[0xc];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

struct Ov293HitRecord {
    int nKind;
    int pad04;
    int nParam;
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, unsigned short mode, void *anchor);
extern struct Ov293HitRecord data_ov293_020d3660;

int func_ov293_020d1ef0(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov293ActionState *state = *(struct Ov293ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    state->nParam = nParam;
    state->vHit = hit->vPoint;
    if (*(signed char *)(state->pOwner + 0x1c6) == 6 && (hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 7;
        return 1;
    }
    if (*(signed char *)(state->pOwner + 0x1c6) == 6) {
        hit->uMode20 = 0;
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
        if (nParam != 0) {
            data_ov293_020d3660.nParam = nParam;
            data_ov293_020d3660.nKind = 0;
        }
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if ((hit->uFlagsLo & 0x8000) != 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 5;
    }
    if ((short)hit->nDamage10 > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                ((struct Ov293Facing *)state)->bFacing = ((struct Ov293Facing *)state)->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11a, (((struct Ov293Facing *)state)->bFacing & 1) ? 2 : 3, state->pAnchor);
            } else {
                ((struct Ov293Facing *)state)->bFacing = ((struct Ov293Facing *)state)->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11a, (((struct Ov293Facing *)state)->bFacing & 1) ? 0 : 1, state->pAnchor);
            }
        }
    }
    return 1;
}
