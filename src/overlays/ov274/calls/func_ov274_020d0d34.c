/*
 * Hit handler of the ov274 enemy. A hit is refused once the stagger timer (+0x21a) has run
 * out. A hit on the +0x3ac body marks the attacker's slot (+0x53 + id) as 5: in sub-state 7
 * the ov107 charge is doubled and drains the timer; otherwise the charge accumulates in
 * +0x28 and, past a tenth of the +0x218 cap (mode 0x3000) or for a flag-8/8 hit (mode
 * 0x9000), +0x28 clears, +0x4c keeps the mode, bit 0 of +0x1ae is raised and sub-state 7
 * begins; the charge then drains the timer (clamped to the cap, floored at zero). A hit on
 * the +0x3b0 body from an unmarked attacker fires reaction 0x163 mode 8 at the body's
 * transform for a positive mode word, zeroes the damage, sets result bits 0/3 and returns 1.
 * A hit that charged flips the state's facing bit (+0x51 bit 0) and fires reaction 0x163 at
 * the body's transform, modes 2/3 for flag-0x22 hits and 0/1 otherwise, except for kind-0x80
 * hits carrying both flag 8 and flag 0x80; an emptied timer ends in sub-state 3.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x; int y; int z; };

struct Ov274ActionState {
    int pOwner;
    char pad004[0x24];
    int nCharge;                 /* 0x28 */
    char pad02c[0x20];
    int nMode;                   /* 0x4c */
    char pad050[1];
    u8 bFacing : 1;              /* 0x51 */
    char pad052[1];
    u8 aSlot[1];                 /* 0x53 */
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    unsigned int uMode10;
    char pad014[4];
    int *pSource18;
    char pad01c[8];
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void VEC_Subtract(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern void func_0202f384(struct Vec3 *out, void *basis, const struct Vec3 *v);
extern void func_ov107_020c5af8(int actor, int id, unsigned short mode, void *anchor);
extern const struct Vec3 data_02042258;

int func_ov274_020d0d34(char *actor, char *attacker, struct ActorHitEvent *hit)
{
    struct Ov274ActionState *state = *(struct Ov274ActionState **)(actor + 0x214);
    struct Vec3 d;
    struct Vec3 v;
    int delta;
    int rem;
    int dmg;
    int mode;

    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if ((int)hit->pSource18 == *(int *)(actor + 0x3ac)) {
        state->aSlot[*(u16 *)(attacker + 2)] = 5;
        if (*(signed char *)(state->pOwner + 0x1c6) == 7) {
            hit->nDamage = func_ov107_020c89e8(actor, hit) * 2;
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
        } else {
            mode = 0;
            dmg = func_ov107_020c89e8(actor, hit);
            state->nCharge += dmg;
            if (state->nCharge >= *(short *)(actor + 0x218) / 10) {
                mode = 0x3000;
            }
            if ((hit->uFlagsLo & 8) != 0 && (hit->uFlagsHi & 8) != 0) {
                mode = 0x9000;
            }
            if (mode != 0) {
                state->nCharge = 0;
                state->nMode = mode;
                *(u16 *)(state->pOwner + 0x100 + 0xae) |= 1;
                *(u8 *)(state->pOwner + 0x1c7) = 7;
            }
            hit->nDamage = dmg;
            delta = *(short *)(actor + 0x21a) - dmg;
            if (delta < 0) {
                rem = 0;
            } else {
                rem = *(short *)(actor + 0x218);
                if (delta <= rem) {
                    rem = delta;
                }
            }
            *(short *)(actor + 0x21a) = (short)rem;
        }
    } else if ((int)hit->pSource18 == *(int *)(actor + 0x3b0)) {
        if (state->aSlot[*(u16 *)(attacker + 2)] == 0) {
            VEC_Subtract((struct Vec3 *)(attacker + 0x190), (struct Vec3 *)(actor + 0xb0), &d);
            func_0202f384(&v, actor + 0xa0, &data_02042258);
            if ((short)hit->uMode10 > 0) {
                func_ov107_020c5af8(state->pOwner, 0x163, 8, (char *)*hit->pSource18 + 4);
            }
            hit->nDamage = 0;
            hit->uResultLo |= 9;
            return 1;
        }
        return 0;
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8((int)actor, 0x163, (state->bFacing & 1) ? 2 : 3, (char *)*hit->pSource18 + 4);
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8((int)actor, 0x163, (state->bFacing & 1) ? 0 : 1, (char *)*hit->pSource18 + 4);
            }
        }
    }
    if (*(short *)(state->pOwner + 0x21a) == 0) {
        *(u8 *)(state->pOwner + 0x1c7) = 3;
    }
    return 1;
}
