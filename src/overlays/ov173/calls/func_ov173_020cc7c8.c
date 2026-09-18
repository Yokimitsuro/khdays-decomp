/* Hit handler of the ov173 enemy (x2: ov173/174), variant of the matched ov166 sibling. Records
 * the impact point (+0x2c) and the +0x10 parameter, refuses while +0x21a is not positive; in
 * sub-states 2/4/5/6/8/9 a hit that is not a grab (1|0x10) nor the 8/0x80/0x80 combination has a
 * 1/3 chance to request sub-state 7 at once. Otherwise: mode 0 for sub-states 8/9, damage
 * resolved, a 0x4000 hit answers with sub-state 0xc, the health drops (clamped to +0x218), a
 * positive non-8/0x80/0x80 hit fires reaction 0x141 with the impact-table mode picked by the
 * alternating +0x85 counter, a grab in sub-state 9 requests 0xa, zero health requests 3 and,
 * outside sub-state 8, an 0x8000 hit goes to 0xd from 0xc/0xd and to 0xc otherwise. */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov173ActionState {
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
extern const u8 data_ov173_020ceca8[];
extern int func_02023eb4(int bound);

int func_ov173_020cc7c8(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov173ActionState *state = *(struct Ov173ActionState **)(actor + 0x214);
    int delta;
    int rem;
    int bGrab;
    int owner;
    int cur;

    bGrab = 0;
    if ((hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
        bGrab = 1;
    }
    state->vHit = hit->vPoint;
    state->nParam = nParam;
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 2:
    case 4:
    case 5:
    case 6:
    case 8:
    case 9:
        if (!bGrab && ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) &&
            func_02023eb4(3) == 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 7;
            return 1;
        }
        break;
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

                uSlot.sPair = *(const struct ImpactPair *)&data_ov173_020ceca8[0];
                state->nToggle85++;
                func_ov107_020c5af8(actor, 0x141, uSlot.aModes[state->nToggle85 & 1], state->pPos);
            } else {
                union ImpactSlot uSlot;

                uSlot.sPair = *(const struct ImpactPair *)&data_ov173_020ceca8[2];
                state->nToggle85++;
                func_ov107_020c5af8(actor, 0x141, uSlot.aModes[state->nToggle85 & 1], state->pPos);
            }
        }
    }
    owner = state->pOwner;
    cur = *(signed char *)(owner + 0x1c6);
    if (cur == 9 && bGrab) {
        *(u8 *)(owner + 0x1c7) = 0xa;
        return 1;
    }
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(owner + 0x1c7) = 3;
    } else if (cur != 8 && (hit->uFlagsLo & 0x8000) != 0) {
        if (!(cur != 0xc && cur != 0xd)) {
            *(u8 *)(owner + 0x1c7) = 0xd;
        } else {
            *(u8 *)(owner + 0x1c7) = 0xc;
        }
    }
    return 1;
}
