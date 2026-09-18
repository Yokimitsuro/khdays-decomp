/*
 * Hit handler of the ov178 enemy (and its byte-identical twins): copies the hit point into +0x2c and the
 * parameter into +0x10, then refuses the hit once the stagger timer (+0x21a) has run out.
 * Sub-states 8 and 9 publish 0 into the event's mode field; the ov107 charge decides the
 * damage; flag 0x4000 sets the result's low half and goes to sub-state 0xc. The damage drains
 * the stagger timer (clamped to the +0x218 cap, floored at zero). A hit that charged bumps the
 * +0x85 counter and fires reaction 0x143 at the +8 position with the counter-alternated mode
 * from the local pair table (bytes 0/1 for flag-0x22 hits, 2/3 otherwise), except for kind-0x80
 * hits carrying both flag 8 and flag 0x80. An emptied timer ends in sub-state 3; otherwise a
 * 0x8000 hit outside sub-state 8 goes to 0xd from 0xc/0xd and to 0xc from anything else.
 */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov178ActionState {
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
extern const u8 data_ov179_020d48e8[];

int func_ov179_020d2304(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov178ActionState *state = *(struct Ov178ActionState **)(actor + 0x214);
    int delta;
    int rem;

    state->vHit = hit->vPoint;
    state->nParam = nParam;
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 8:
        hit->uMode20 = 1;
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

                uSlot.sPair = *(const struct ImpactPair *)&data_ov179_020d48e8[0];
                state->nToggle85++;
                func_ov107_020c5af8(actor, 0x143, uSlot.aModes[state->nToggle85 & 1], state->pPos);
            } else {
                union ImpactSlot uSlot;

                uSlot.sPair = *(const struct ImpactPair *)&data_ov179_020d48e8[2];
                state->nToggle85++;
                func_ov107_020c5af8(actor, 0x143, uSlot.aModes[state->nToggle85 & 1], state->pPos);
            }
        }
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
