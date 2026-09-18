/* Hit handler of the ov156 enemy (and its byte-identical twin): ignored while the +0x21a stamina
 * is spent. Sub-state 6 marks the hit mode 1 and the damage is cleared; a hit through the actor's
 * own +0x388 shape whose +0x16 id is not 0x15 only sets result 1. Otherwise the damage is
 * resolved, the stamina drops by it (clamped to the +0x218 maximum), spent stamina asks for
 * sub-state 3 and a 0x8000 hit for 5; a positive damage that is not the 8|0x80/0x80 special
 * toggles bit 1 of +0x39 and fires reaction 0x13d with the mode alternating (2/3 for flags 0x22,
 * 0/1 otherwise) at the +0xc position. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x; int y; int z; };

struct Ov156ActionState {
    int pOwner;
    char pad004[0x8];
    void *pPos;                 /* +0xc */
    char pad010[0x29];
    u8 bit0 : 1;                /* +0x39 */
    u8 bToggle : 1;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    int nDamage10;
    int nField14 : 16;
    int nId16 : 16;
    void *pShape;               /* +0x18 */
    char pad01c[4];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;                /* +0x28 */
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int id, u16 mode, void *anchor);

int func_ov156_020cc7bc(char *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov156ActionState *state = *(struct Ov156ActionState **)(actor + 0x214);
    int delta;
    int rem;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if (*(signed char *)(state->pOwner + 0x1c6) == 6) {
        hit->uMode20 = 1;
    }
    hit->nDamage = 0;
    if (hit->pShape == *(void **)(actor + 0x388) && hit->nId16 != 0x15) {
        hit->uResultLo = 1;
        return 1;
    }
    hit->nDamage = func_ov107_020c89e8(actor, hit);
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
        *(u8 *)(state->pOwner + 0x1c7) = 5;
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bToggle++;
                func_ov107_020c5af8(actor, 0x13d, (state->bToggle & 1) ? 2 : 3, state->pPos);
            } else {
                state->bToggle++;
                func_ov107_020c5af8(actor, 0x13d, (state->bToggle & 1) ? 0 : 1, state->pPos);
            }
        }
    }
    return 1;
}
