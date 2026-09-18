/* Hit handler of the ov139 enemy (and its byte-identical twin): ignored while the +0x21a
 * stamina is spent. The hit mode follows the sub-state (5 -> 0, 6 -> 1) before the damage is
 * resolved; a 0x4000-flagged hit records the hit point, sets result 1 and asks for sub-state 9.
 * Otherwise the stamina drops by the damage (clamped to the +0x218 maximum), the parameter and
 * hit point are recorded, spent stamina asks for sub-state 3, a 0x8000 hit from sub-state 7
 * asks for 8, a 1|0x10 hit from sub-state 5 asks for 7 and any other 0x8000 hit asks for 9; a
 * positive +0x10 damage that is not the 8|0x80/0x80 special toggles bit 0 of +0x56 and fires
 * reaction 0x11f with the mode alternating (2/3 for flags 0x22, 0/1 otherwise) at the +0x4c
 * position. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x; int y; int z; };

struct Ov139ActionState {
    int pOwner;
    char pad004[0x1c];
    struct Vec3 vHit;           /* +0x20 */
    char pad02c[0x18];
    int nParam;                 /* +0x44 */
    char pad048[4];
    void *pPos;                 /* +0x4c */
    char pad050[6];
    u8 bToggle : 1;             /* +0x56 */
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

int func_ov140_020d0024(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov139ActionState *state = *(struct Ov139ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 5:
        hit->uMode20 = 0;
        break;
    case 6:
        hit->uMode20 = 1;
        break;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        state->vHit = hit->vPoint;
        hit->uResultLo = 1;
        *(u8 *)(state->pOwner + 0x1c7) = 9;
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
    state->vHit = hit->vPoint;
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    } else if ((hit->uFlagsLo & 0x8000) != 0 && *(signed char *)(state->pOwner + 0x1c6) == 7) {
        *(u8 *)(state->pOwner + 0x1c7) = 8;
    } else if ((hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0 && *(signed char *)(state->pOwner + 0x1c6) == 5) {
        *(u8 *)(state->pOwner + 0x1c7) = 7;
    } else if ((hit->uFlagsLo & 0x8000) != 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 9;
    }
    if ((short)hit->nDamage10 > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bToggle++;
                func_ov107_020c5af8(actor, 0x11f, (state->bToggle & 1) ? 2 : 3, state->pPos);
            } else {
                state->bToggle++;
                func_ov107_020c5af8(actor, 0x11f, (state->bToggle & 1) == 0 ? 1 : 0, state->pPos);
            }
        }
    }
    return 1;
}
