/* Hit handler of the ov282 enemy (x2 with ov211): ignored while the +0x21a stamina is spent.
 * The hit's source is kept at +0x20 of the work and the hit mode follows the sub-state
 * (8 -> 1, 0xf -> 0, 0x10 -> 2) before the damage is resolved; a 0x4000-flagged hit sets result 1
 * and asks for sub-state 4. Sub-state 9 doubles the damage. The stamina drops by the damage
 * (clamped to the +0x218 maximum); spent stamina asks for sub-state 3, a 4|0x8000 hit asks for 4
 * with +0x68 cleared, a 1|0x10 hit in sub-state 8 asks for 4 with +0x68 raised. A positive damage
 * that is not the 8|0x80/0x80 special advances bit 0 of +0x65 and fires reaction 0x16a with the
 * mode alternating (2/3 for flags 0x22, 1/0 otherwise) at the +4 position. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x; int y; int z; };

struct Ov282ActionState {
    int pOwner;
    void *pPos;                 /* +0x04 */
    char pad008[0x18];
    int nParam;                 /* +0x20 */
    char pad024[0x41];
    u8 bToggle : 1;             /* +0x65 */
    char pad066[2];
    int bGrab;                  /* +0x68 */
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
extern void func_ov107_020c5af8(char *actor, int id, u16 mode, void *anchor);

int func_ov282_020d044c(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov282ActionState *state = *(struct Ov282ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    state->nParam = nParam;
    switch (*(signed char *)(state->pOwner + 0x1c6)) {
    case 8:
        hit->uMode20 = 1;
        break;
    case 0xf:
        hit->uMode20 = 0;
        break;
    case 0x10:
        hit->uMode20 = 2;
        break;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        *(u8 *)(state->pOwner + 0x1c7) = 4;
        return 1;
    }
    if (*(signed char *)(state->pOwner + 0x1c6) == 9) {
        hit->nDamage = hit->nDamage << 1;
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
    } else if ((hit->uFlagsLo & 4) != 0 && (hit->uFlagsLo & 0x8000) != 0) {
        state->bGrab = 0;
        *(u8 *)(state->pOwner + 0x1c7) = 4;
    } else if ((hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0 && *(signed char *)(state->pOwner + 0x1c6) == 8) {
        state->bGrab = 1;
        *(u8 *)(state->pOwner + 0x1c7) = 4;
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bToggle++;
                func_ov107_020c5af8(actor, 0x16a, (state->bToggle & 1) ? 2 : 3, state->pPos);
            } else {
                state->bToggle++;
                func_ov107_020c5af8(actor, 0x16a, (state->bToggle & 1) == 0 ? 1 : 0, state->pPos);
            }
        }
    }
    return 1;
}
