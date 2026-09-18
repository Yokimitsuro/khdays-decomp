/* Hit handler of the ov250 enemy (and its byte-identical twin): ignored while the +0x21a
 * stamina is spent. A 1|0x10 hit during sub-state 9 only asks for sub-state 0xa. Otherwise the
 * hit mode follows the sub-state (7 -> 0, 8 -> 1, 9 -> 2), the hit point and parameter are
 * recorded and the damage is resolved; a 0x4000-flagged hit sets result 1 and asks for
 * sub-state 6. Otherwise the stamina drops by the damage (clamped to the +0x218 maximum), spent
 * stamina asks for sub-state 3 and a 0x8000 hit for 6; a positive damage that is not the
 * 8|0x80/0x80 special toggles bit 0 of +0x51 and fires reaction 0x159 with the mode alternating
 * (2/3 for flags 0x22, 0/1 otherwise) at the +8 position. */
typedef unsigned char u8;

struct Vec3 { int x; int y; int z; };

struct Ov134ActionState {
    int pOwner;
    char pad004[4];
    void *pPos;                 /* +0x08 */
    char pad00c[0x18];
    int nParam;                 /* +0x24 */
    char pad028[0x29];
    u8 bFacing : 1;             /* +0x51 */
    char pad052[0xe];
    struct Vec3 vHit;           /* +0x60 */
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

int func_ov251_020d3d7c(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov134ActionState *state = *(struct Ov134ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if ((hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0 && *(signed char *)(state->pOwner + 0x1c6) == 9) {
        *(u8 *)(state->pOwner + 0x1c7) = 0xa;
        return 1;
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
                func_ov107_020c5af8(actor, 0x159, (state->bFacing & 1) ? 2 : 3, state->pPos);
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x159, (state->bFacing & 1) ? 0 : 1, state->pPos);
            }
        }
    }
    return 1;
}
