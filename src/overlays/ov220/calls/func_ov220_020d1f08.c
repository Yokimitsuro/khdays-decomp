/* Hit handler of the ov220 enemy (variant of the ov219 handler): ignores hits while bit 0 of
 * +0x1ac is set, the +0x21a stamina is spent or the actor sits in sub-state 3; forces mode 0 from
 * sub-state 5, records the hit point (+0x30) and resolves the damage. A 0x4000-flagged hit sets
 * result 1, clears the +0x60 knockback flags and asks for sub-state 8. Else the stamina drops by
 * the damage (clamped to the +0x218 maximum), the parameter is recorded (+0x40) and a 0x8000 hit
 * that is not the 8|0x80/0x80 special fires reaction 0x137 with the impact mode taken from the
 * overlay's 4-byte table (pair 1 for flags 0x22, pair 0 otherwise, alternating with the +0x3d
 * toggle). Spent stamina asks for sub-state 3; otherwise, outside sub-state 0xa, a zero parameter
 * asks for 0xa, a 1|0x10 hit from sub-state 5 asks for 6, and a 0x8000 hit stores the 0x22
 * knockback bits and asks for 8. Codegen: the impact table is held through a `T *const` local so
 * its pool load is created before the actor parameter is homed (r3, not r0). */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov220ActionState {
    int pOwner;
    char pad004[4];
    void *pPos;
    char pad00c[0x24];
    struct Vec3 vHit;
    char pad03c[1];
    u8 nToggle3d;
    char pad03e[2];
    int nParam;
    char pad044[0x1c];
    int nKnockback60;
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

/* The two reaction modes of one impact kind, copied out of the table as a unit so the
   alternating toggle can pick between them. */
struct ImpactPair { u8 nFirst; u8 nSecond; };
union ImpactSlot { struct ImpactPair sPair; u8 aModes[2]; };

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, u8 mode, void *anchor);
extern const u8 data_ov220_020d3b98[];

int func_ov220_020d1f08(char *actor, int nParam, struct ActorHitEvent *hit)
{
    const struct ImpactPair *const table = (const struct ImpactPair *)data_ov220_020d3b98;
    struct Ov220ActionState *state;
    union ImpactSlot uHit;
    union ImpactSlot uPush;
    int delta;
    int rem;

    uHit.sPair = table[0];
    uPush.sPair = table[1];
    state = *(struct Ov220ActionState **)(actor + 0x214);
    if ((*(unsigned short *)(actor + 0x1ac) & 1) != 0) {
        return 0;
    }
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if (*(signed char *)(state->pOwner + 0x1c6) == 3) {
        return 0;
    }
    if (*(signed char *)(state->pOwner + 0x1c6) == 5) {
        hit->uMode20 = 0;
    }
    state->vHit = hit->vPoint;
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        state->nKnockback60 = 0;
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
    state->nParam = nParam;
    if ((hit->uFlagsLo & 0x8000) != 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                func_ov107_020c5af8(actor, 0x137, uPush.aModes[state->nToggle3d], state->pPos);
            } else {
                func_ov107_020c5af8(actor, 0x137, uHit.aModes[state->nToggle3d], state->pPos);
            }
            state->nToggle3d ^= 1;
        }
    }
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if (*(signed char *)(state->pOwner + 0x1c6) != 0xa) {
        if (nParam == 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 0xa;
        } else if (*(signed char *)(state->pOwner + 0x1c6) == 5 && (hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 6;
        } else if ((hit->uFlagsLo & 0x8000) != 0) {
            state->nKnockback60 = hit->uFlagsLo & 0x22;
            *(u8 *)(state->pOwner + 0x1c7) = 8;
        }
    }
    return 1;
}
