/* Hit handler of the ov219 enemy: records the hit point (+0x30) and parameter (+0x40) in the
 * action state, ignores hits while bit 0 of +0x1ac is set or the +0x21a stamina is spent, and
 * otherwise resolves the damage (mode 0 forced from sub-state 5). A 0x4000-flagged hit sets
 * result 1, clears the +0x50 knockback flags and asks for sub-state 6. Else the stamina drops by
 * the damage (clamped to the +0x218 maximum); a damaging hit that is not the 8|0x80/0x80 special
 * fires reaction 0x136 with the impact mode taken from the overlay's 4-byte table (pair 1 for
 * flags 0x22, pair 0 otherwise, alternating with the +0x3d toggle). Spent stamina asks for
 * sub-state 3; otherwise, outside sub-state 8, a zero parameter asks for 8, a 1|0x10 hit from
 * sub-state 5 asks for 3, and a 0x8000 hit stores the 0x22 knockback bits and asks for 6.
 * Codegen: the impact table is held through a `T *const` local so its pool load is created before
 * the actor parameter is homed (r3, not r0). */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov219ActionState {
    int pOwner;
    char pad004[4];
    void *pPos;
    char pad00c[0x24];
    struct Vec3 vHit;
    char pad03c[1];
    u8 nToggle3d;
    char pad03e[2];
    int nParam;
    char pad044[0xc];
    int nKnockback50;
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
extern const u8 data_ov219_020d18a4[];

int func_ov219_020d00e8(char *actor, int nParam, struct ActorHitEvent *hit)
{
    const struct ImpactPair *const table = (const struct ImpactPair *)data_ov219_020d18a4;
    struct Ov219ActionState *state;
    union ImpactSlot uHit;
    union ImpactSlot uPush;
    int delta;
    int rem;

    uHit.sPair = table[0];
    uPush.sPair = table[1];
    state = *(struct Ov219ActionState **)(actor + 0x214);
    state->nParam = nParam;
    state->vHit = hit->vPoint;
    if ((*(unsigned short *)(actor + 0x1ac) & 1) != 0) {
        return 0;
    }
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if (*(signed char *)(state->pOwner + 0x1c6) == 5) {
        hit->uMode20 = 0;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        state->nKnockback50 = 0;
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
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                func_ov107_020c5af8(actor, 0x136, uPush.aModes[state->nToggle3d], state->pPos);
            } else {
                func_ov107_020c5af8(actor, 0x136, uHit.aModes[state->nToggle3d], state->pPos);
            }
            state->nToggle3d ^= 1;
        }
    }
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if (*(signed char *)(state->pOwner + 0x1c6) != 8) {
        if (nParam == 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 8;
        } else if (*(signed char *)(state->pOwner + 0x1c6) == 5 && (hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 3;
        } else if ((hit->uFlagsLo & 0x8000) != 0) {
            state->nKnockback50 = hit->uFlagsLo & 0x22;
            *(u8 *)(state->pOwner + 0x1c7) = 6;
        }
    }
    return 1;
}
