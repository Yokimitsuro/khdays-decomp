/* Hit handler of the ov200 enemy (x3: ov200/ov201/ov271). An actor without hit points ignores
 * the hit; otherwise the source is kept at +0x54 and the hit point at +0x18 of the work.
 * Sub-state 6 tags the hit with reaction 1, sub-state 7 with 0. A 0x4000 hit only sets bit 0
 * of the result, requests sub-state 8 and returns. The hit points drain, floored at 0 and
 * capped at the +0x218 floor; empty hit points request sub-state 3, a 0x8000 hit sub-state 8
 * (and a 0x2000 one also raises +0x68). A damaging hit that is not the 8/0x80/kind-0x80 kind
 * fires reaction 0x157 with the +0x58 bit-0 side's mode from the overlay's hurt (bits 1/5) or
 * idle pair at the +0x48 point, then flips the side. */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov200ActionState {
    int pOwner;
    char pad004[0x14];
    struct Vec3 vHit;
    char pad024[0x24];
    void *pPos;
    char pad04c[8];
    int nParam;
    u8 bSide : 1;
    char pad059[0xf];
    int bStagger;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    char pad010[0x10];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, u8 mode, void *anchor);
extern const u8 data_ov200_020d182c[];

int func_ov200_020ce6ac(char *actor, int nParam, struct ActorHitEvent *hit)
{
    u8 idleModes[2] = { data_ov200_020d182c[2], data_ov200_020d182c[3] };
    u8 hurtModes[2] = { data_ov200_020d182c[0], data_ov200_020d182c[1] };
    struct Ov200ActionState *state = *(struct Ov200ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    state->nParam = nParam;
    state->vHit = hit->vPoint;
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 6:
        hit->uMode20 = 1;
        break;
    case 7:
        hit->uMode20 = 0;
        break;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
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
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if ((hit->uFlagsLo & 0x8000) != 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 8;
        if ((hit->uFlagsLo & 0x2000) != 0) {
            state->bStagger = 1;
        }
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                func_ov107_020c5af8(actor, 0x157, hurtModes[state->bSide], state->pPos);
            } else {
                func_ov107_020c5af8(actor, 0x157, idleModes[state->bSide], state->pPos);
            }
            state->bSide ^= 1;
        }
    }
    return 1;
}
