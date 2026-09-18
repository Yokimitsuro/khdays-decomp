/* Hit handler of the ov297 enemy: the damage is 1; the hit is ignored while the +0x21a stamina
 * is spent or the +0x80 alert is up. With the +0x8c guard up, a 90% roll parries: damage 0,
 * result 9, reaction 0 mode 0x3f at the +8 point, effect 1 at the actor's position and
 * sub-state 8. Otherwise the stamina drops by the damage (clamped to the +0x218 maximum), the
 * parameter and hit point are recorded, a positive damaging hit that is not the 8|0x80/0x80
 * special fires reaction 0x176 with the mode taken from the overlay's pairs (0x22 hits use the
 * second pair) alternated by the +0x92 toggle. Four retreats already taken (+0x60) with the alert
 * down set the stamina to 1 and request sub-state 10; with stamina left a 0x8000 hit outside
 * sub-state 6 requests sub-state 6, anything else arms the +0x5c chase clock at 0x2fd0 and
 * requests sub-state 7; spent stamina is pinned at 1. */
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

extern int func_02023eb4(int range);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int d);
extern const struct ModeTable data_ov297_020d5698;

int func_ov297_020d3dec(char *actor, int nParam, struct ActorHitEvent *hit)
{
    int *state = *(int **)(actor + 0x214);
    struct ModePair pair = data_ov297_020d5698.pair;
    struct ModePair pair22 = data_ov297_020d5698.pair22;
    int delta;
    int rem;
    int owner;

    hit->nDamage = 1;
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    if (state[0x20] != 0) {
        return 0;
    }
    if (state[0x23] != 0 && (unsigned int)func_02023eb4(0x64) < 0x5a) {
        hit->nDamage = 0;
        hit->uResultLo |= 9;
        func_ov107_020c5af8(*state, 0, 0x3f, (void *)state[2]);
        owner = *state;
        func_ov107_020c0b90(owner, 1, *(Vec3 *)(owner + 0x74), 0);
        *(u8 *)(*state + 0x1c7) = 8;
        goto done;
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
    state[3] = nParam;
    *(Vec3 *)(state + 7) = hit->vPoint;
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                func_ov107_020c5af8((int)actor, 0x176, pair22.a[*(u8 *)((char *)state + 0x92)], (void *)state[2]);
            } else {
                func_ov107_020c5af8((int)actor, 0x176, pair.a[*(u8 *)((char *)state + 0x92)], (void *)state[2]);
            }
            *(u8 *)((char *)state + 0x92) ^= 1;
        }
    }
    if (state[0x18] >= 4 && state[0x20] == 0) {
        *(short *)(actor + 0x21a) = 1;
        *(u8 *)(*state + 0x1c7) = 10;
        return 1;
    }
    if (*(short *)(actor + 0x21a) == 0) {
        *(short *)(actor + 0x21a) = 1;
        return 1;
    }
    if ((hit->uFlagsLo & 0x8000) != 0 && *(signed char *)(*state + 0x1c6) != 6) {
        *(u8 *)(*state + 0x1c7) = 6;
    } else {
        state[0x17] = 0x2fd0;
        *(u8 *)(*state + 0x1c7) = 7;
    }
    return 1;
done:
    return 1;
}
