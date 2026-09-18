/* Hit handler of the ov239 enemy: ignored while the actor's +0x1ac bit 0 is set or the +0x21a
 * stamina is spent. Sub-states 5/6 force hit mode 0/1, the hit point is recorded at +0x20, the
 * damage is resolved and an unguarded (+0x1c4 bit 1 clear) 0x4000 hit sets result 1 and
 * requests sub-state 7. Otherwise the stamina drops by the damage (clamped to the +0x218
 * maximum), the parameter is recorded at +0x34 and a positive damaging hit that is not the
 * 8|0x80/0x80 special fires reaction 0x138 with the mode taken from the overlay's pairs (0x22
 * hits use the second pair) alternated by the +0x31 toggle. Spent stamina requests sub-state 3;
 * a 1|0x10 hit in sub-state 6 marks +0x30; a 0x8000 hit requests sub-state 7. */
typedef unsigned char u8;
typedef struct Vec3 { int x, y, z; } Vec3;

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    Vec3 vPoint;
    int nDamage10;
    char pad014[0xc];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

struct ModePair { u8 a[2]; };
struct ModeTable { struct ModePair pair; struct ModePair pair22; };

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(char *actor, int a, int id, void *at);
extern const struct ModeTable data_ov239_020cdc20;

int func_ov239_020cc4ec(char *actor, int nParam, struct ActorHitEvent *hit)
{
    int *state = *(int **)(actor + 0x214);
    struct ModePair pair = data_ov239_020cdc20.pair;
    struct ModePair pair22 = data_ov239_020cdc20.pair22;
    int delta;
    int rem;

    if ((*(unsigned short *)(actor + 0x1ac) & 1) != 0) {
        return 0;
    }
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    switch (*(signed char *)(*state + 0x1c6)) {
    case 6:
        hit->uMode20 = 1;
        break;
    case 5:
        hit->uMode20 = 0;
        break;
    }
    *(Vec3 *)(state + 8) = hit->vPoint;
    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if ((*(u8 *)(actor + 0x1c4) & 2) == 0 && (hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        *(u8 *)(*state + 0x1c7) = 7;
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
    state[0xd] = nParam;
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                func_ov107_020c5af8(actor, 0x138, pair22.a[*(u8 *)((char *)state + 0x31)], (void *)state[2]);
            } else {
                func_ov107_020c5af8(actor, 0x138, pair.a[*(u8 *)((char *)state + 0x31)], (void *)state[2]);
            }
            *(u8 *)((char *)state + 0x31) ^= 1;
        }
    }
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(*state + 0x1c7) = 3;
        return 1;
    }
    if (*(signed char *)(*state + 0x1c6) == 6 && (hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
        *(u8 *)(state + 0xc) = 0xff;
        return 1;
    }
    if ((hit->uFlagsLo & 0x8000) != 0) {
        *(u8 *)(*state + 0x1c7) = 7;
    }
    return 1;
}
