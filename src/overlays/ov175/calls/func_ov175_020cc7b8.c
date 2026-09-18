/* Hit handler of the ov175 enemy (x3: ov175/176/177), ported from the matched ov166 sibling.
 * Records the impact point (+0x2c) and the +0x10 parameter, refuses while +0x21a is not positive,
 * clears the event mode for sub-states 8/9, resolves the damage, and a 0x4000 hit answers 1 and
 * requests sub-state 0xc. Otherwise the health is reduced (clamped to +0x218), a positive hit
 * that is not the 8/0x80/0x80 combination fires reaction 0x142 with the impact-table mode picked
 * by the alternating +0x85 counter; an 0x8 hit that is not that combination (and, with no
 * damage, not 0x80) turns the impact vector into a knockback scaled by 0xc00 / the camera's
 * +0x40 and requests sub-state 0xc; then zero health requests 3 and, outside sub-state 8, an
 * 0x8000 hit goes to 0xd from 0xc/0xd and to 0xc otherwise. */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov175ActionState {
    int pOwner;
    char pad004[4];
    void *pPos;
    char pad00c[4];
    int nParam;
    char pad014[0x18];
    struct Vec3 vHit;
    char pad038[0x4d];
    u8 nToggle85;
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
   alternating counter can pick between them. */
struct ImpactPair { u8 nFirst; u8 nSecond; };
union ImpactSlot { struct ImpactPair sPair; u8 aModes[2]; };

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, u8 mode, void *anchor);
extern const u8 data_ov175_020cea84[];
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *out);
extern char *OS_IsThreadAvailable_0x020c9848(void);   /* the game's camera-state getter, named after the byte-identical SDK thunk */
extern int FX_Inv_0x01ff8a40(int x);
extern void func_01ffa724(int scale, struct Vec3 *v, struct Vec3 *out);

int func_ov175_020cc7b8(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov175ActionState *state = *(struct Ov175ActionState **)(actor + 0x214);
    int delta;
    int rem;

    state->vHit = hit->vPoint;
    state->nParam = nParam;
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 8:
        hit->uMode20 = 0;
        break;
    case 9:
        hit->uMode20 = 0;
        break;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        *(u8 *)(state->pOwner + 0x1c7) = 0xc;
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
                union ImpactSlot uSlot;

                uSlot.sPair = *(const struct ImpactPair *)&data_ov175_020cea84[0];
                state->nToggle85++;
                func_ov107_020c5af8(actor, 0x142, uSlot.aModes[state->nToggle85 & 1], state->pPos);
            } else {
                union ImpactSlot uSlot;

                uSlot.sPair = *(const struct ImpactPair *)&data_ov175_020cea84[2];
                state->nToggle85++;
                func_ov107_020c5af8(actor, 0x142, uSlot.aModes[state->nToggle85 & 1], state->pPos);
            }
        }
    }
    if ((hit->uFlagsLo & 8) != 0 &&
        ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) &&
        (hit->nDamage != 0 || (hit->uFlagsLo & 0x80) == 0)) {
        func_01ff8d18(&state->vHit, &state->vHit);
        func_01ffa724((int)(((long long)FX_Inv_0x01ff8a40(*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x40)) * 0xc00 + 0x800) >> 12), &state->vHit, &state->vHit);
        *(u8 *)(state->pOwner + 0x1c7) = 0xc;
    }
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if (*(signed char *)(state->pOwner + 0x1c6) != 8 && (hit->uFlagsLo & 0x8000) != 0) {
        int cur = *(signed char *)(state->pOwner + 0x1c6);
        if (!(cur != 0xc && cur != 0xd)) {
            *(u8 *)(state->pOwner + 0x1c7) = 0xd;
        } else {
            *(u8 *)(state->pOwner + 0x1c7) = 0xc;
        }
    }
    return 1;
}
