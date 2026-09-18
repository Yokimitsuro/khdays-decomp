/* Hit handler of the ov204 enemy (and its byte-identical twin): ignored while the +0x21a
 * stamina is spent. The hit mode follows the sub-state (6 -> 0, 7 -> 1, 0xb -> 2) before the
 * damage is resolved; a 0x4000-flagged hit records the hit point, sets result 1 and asks for
 * sub-state 5. Otherwise the stamina drops by the damage (clamped to the +0x218 maximum), spent
 * stamina asks for sub-state 3, sub-state 8 with a plain (or 0x800) damaging hit asks for 9, a
 * 1|0x10 hit from sub-state 6 asks for 8 and, outside sub-states 7/0xb, a 0x8000 hit asks for 5;
 * the parameter and hit point are recorded and a positive +0x10 damage that is not the
 * 8|0x80/0x80 special fires reaction 0x132 with the mode alternating through the +0x46 counter
 * (2/3 for flags 0x22, 1/0 otherwise). */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x; int y; int z; };

struct Ov204ActionState {
    int pOwner;
    char pad004[0x10];
    struct Vec3 vHit;
    char pad020[4];
    void *pPos;
    char pad028[0x18];
    int nParam;
    char pad044[2];
    u8 nToggle46;
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

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, u16 mode, void *anchor);

int func_ov204_020d014c(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov204ActionState *state = *(struct Ov204ActionState **)(actor + 0x214);
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
    case 0xb:
        hit->uMode20 = 2;
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
    } else {
        if (*(signed char *)(state->pOwner + 0x1c6) == 8 && ((hit->uFlagsLo & 0x88) == 0 || (hit->uFlagsHi & 0x80) == 0) &&
            (hit->nDamage > 0 || (hit->uFlagsLo & 0x800) != 0)) {
            *(u8 *)(state->pOwner + 0x1c7) = 9;
        } else if ((hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0 && *(signed char *)(state->pOwner + 0x1c6) == 6) {
            *(u8 *)(state->pOwner + 0x1c7) = 8;
        } else if (*(signed char *)(state->pOwner + 0x1c6) != 0xb && *(signed char *)(state->pOwner + 0x1c6) != 7 && (hit->uFlagsLo & 0x8000) != 0) {
            *(u8 *)(state->pOwner + 0x1c7) = 5;
        }
    }
    state->nParam = nParam;
    state->vHit = hit->vPoint;
    if ((short)hit->nDamage10 > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->nToggle46++;
                func_ov107_020c5af8(actor, 0x132, (state->nToggle46 & 1) ? 2 : 3, state->pPos);
            } else {
                state->nToggle46++;
                func_ov107_020c5af8(actor, 0x132, (state->nToggle46 & 1) == 0 ? 1 : 0, state->pPos);
            }
        }
    }
    return 1;
}
