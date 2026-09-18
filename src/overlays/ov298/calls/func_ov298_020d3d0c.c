/* Hit handler of the ov298 enemy: resolves the damage and ignores the hit while the +0x21a
 * stamina is spent, the +0x84 alert is up or the +0x90 flag is set (damage zeroed). A 40% roll
 * requests sub-state 7 without taking the hit; otherwise the damage becomes 1, the stamina drops
 * by one (clamped to the +0x218 maximum), the parameter and hit point are recorded, a positive
 * damaging hit that is not the 8|0x80/0x80 special fires reaction 0x177 with the mode taken
 * from the overlay's pairs (0x22 hits use the first pair) alternated by the +0x96 toggle and
 * the +0x80 hit count grows. Four retreats already taken (+0x60) with the alert down set the
 * stamina to 1 and request sub-state 9; spent stamina is pinned at 1; a hit count at the
 * actor's +0x398 threshold with a valid +0x95 mode requests sub-state 8 and resets the count;
 * a 0x8000 hit requests sub-state 6. */
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
struct ModeTable { struct ModePair pair22; struct ModePair pair; };

extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern int func_02023eb4(int range);
extern void func_ov107_020c5af8(char *actor, int a, int id, void *at);
extern const struct ModeTable data_ov298_020d54ec;

int func_ov298_020d3d0c(char *actor, int nParam, struct ActorHitEvent *hit)
{
    int *state = *(int **)(actor + 0x214);
    struct ModePair pair = data_ov298_020d54ec.pair;
    struct ModePair pair22 = data_ov298_020d54ec.pair22;
    int delta;
    int rem;
    int owner;

    hit->nDamage = func_ov107_020c89e8(actor, hit);
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if (state[0x21] != 0) {
        return 0;
    }
    if (state[0x24] != 0) {
        hit->nDamage = 0;
        return 0;
    }
    if ((unsigned int)func_02023eb4(0x64) < 0x28) {
        *(u8 *)(*state + 0x1c7) = 7;
        return 0;
    }
    hit->nDamage = 1;
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
    state[3] = nParam;
    *(Vec3 *)(state + 7) = hit->vPoint;
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                func_ov107_020c5af8(actor, 0x177, pair22.a[*(u8 *)((char *)state + 0x96)], (void *)state[2]);
            } else {
                func_ov107_020c5af8(actor, 0x177, pair.a[*(u8 *)((char *)state + 0x96)], (void *)state[2]);
            }
            *(u8 *)((char *)state + 0x96) ^= 1;
        }
    }
    state[0x20]++;
    if (state[0x18] >= 4 && state[0x21] == 0) {
        *(short *)(actor + 0x21a) = 1;
        *(u8 *)(*state + 0x1c7) = 9;
        return 1;
    }
    if (*(short *)(actor + 0x21a) == 0) {
        *(short *)(actor + 0x21a) = 1;
        return 1;
    }
    owner = *state;
    if (state[0x20] >= *(int *)(owner + 0x398) && *(signed char *)((char *)state + 0x95) != -1) {
        *(u8 *)(owner + 0x1c7) = 8;
        state[0x20] = 0;
        return 1;
    }
    if ((hit->uFlagsLo & 0x8000) != 0) {
        *(u8 *)(owner + 0x1c7) = 6;
    }
    return 1;
}
