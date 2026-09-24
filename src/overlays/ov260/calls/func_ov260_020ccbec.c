/* Hit handler of the ov260 enemy. The source is kept in +8 and the hit point in +0x38; the hit is
 * ignored while the +0x1ac bit 0 guard is up. With a source the facing of the +0x64 yaw against the
 * direction to it decides whether the hit comes from the front. Sub-state 5 forces the +0x78 hit mode
 * (when set) and sub-state 6 mode 3; a forced 0x4000 hit is deflected (result bits 0 and 3, reaction
 * 0x3f, sub-state 12). In sub-states 2/4 a frontal hit is parried half the time (sub-state 11) and in
 * sub-state 11 every hit is deflected. Otherwise the damage is resolved and taken from the +0x21a
 * stamina (clamped to the +0x218 maximum); a damaging hit other than the 8|0x80 / 0x80 special plays
 * the hurt sound from the overlay's pairs (0x22 hits use the first) alternated by +0x7a. Spent stamina
 * requests sub-state 3; otherwise sub-state 5 is broken by a 1|0x10 hit and, outside sub-state 13, a
 * 0x8000 hit requests sub-state 12 and the first drop to half stamina sub-state 13 (+0x80 latched). A
 * sub-state 12 request on a +0x470 carrier is undone. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Vec3 { int x, y, z; } Vec3;

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    Vec3 vPoint;
    int nDamage10;
    unsigned char pad014[0xc];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

struct ModePair { u8 a[2]; };
struct ModeTable { struct ModePair pair22; struct ModePair pair; };

extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern void func_ov107_020c5af8(int actor, int a, int id, int at);
extern int func_02023eb4(int bound);
extern int func_ov107_020c89e8(char *actor, struct ActorHitEvent *hit);
extern void func_ov260_020cd148(char *actor, int mode, int at);
extern short data_0203d210[];
extern const struct ModeTable data_ov260_020d2a6c;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

int func_ov260_020ccbec(char *self, int other, struct ActorHitEvent *hit)
{
    int *state = *(int **)(self + 0x214);
    Vec3 facing;
    Vec3 d;
    struct ModePair pair;
    struct ModePair pair22;
    int forced;
    int frontal;
    signed char saved;
    unsigned int idx;
    int hp;
    int max;
    unsigned int lo;
    int owner;

    pair = data_ov260_020d2a6c.pair;
    pair22 = data_ov260_020d2a6c.pair22;
    saved = *(signed char *)(*state + 0x1c7);
    state[2] = other;
    *(Vec3 *)(state + 0xe) = hit->vPoint;
    forced = 0;
    frontal = 0;
    if ((*(u16 *)(self + 0x100 + 0xac) & 1) != 0) {
        return 0;
    }
    if (other != 0) {
        idx = ANG2IDX(state[0x19]);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        VEC_Subtract((void *)(other + 0x74), (void *)(*state + 0x74), &d);
        func_01ff8d18(&d, &d);
        if (VEC_DotProduct(&facing, &d) >= 0) {
            frontal = 1;
        }
    }
    switch (*(signed char *)(*state + 0x1c6)) {
    case 5:
        if (*((signed char *)state + 0x78) >= 0) {
            hit->uMode20 = *((signed char *)state + 0x78);
            forced = 1;
        }
        break;
    case 6:
        hit->uMode20 = 3;
        forced = 1;
        break;
    }
    if (forced != 0 && (hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo |= 9;
        func_ov107_020c5af8(*state, 0, 0x3f, state[4]);
        *(u8 *)(*state + 0x1c7) = 0xc;
        return 1;
    }
    switch (*(signed char *)(*state + 0x1c6)) {
    case 2:
    case 4:
        if (frontal != 0 && (unsigned int)func_02023eb4(100) < 0x32) {
            hit->uResultLo |= 9;
            func_ov107_020c5af8(*state, 0, 0x3f, state[4]);
            *(u8 *)(*state + 0x1c7) = 0xb;
            return 1;
        }
        break;
    case 0xb:
        hit->uResultLo |= 9;
        func_ov107_020c5af8(*state, 0, 0x3f, state[4]);
        return 1;
    }
    hit->nDamage = func_ov107_020c89e8(self, hit);
    *(short *)(self + 0x21a) -= hit->nDamage;
    max = *(short *)(self + 0x218);
    hp = *(short *)(self + 0x21a);
    if (hp <= max) {
        if (hp < 0) {
            hp = 0;
        }
        max = hp;
    }
    *(short *)(self + 0x21a) = max;
    if (hit->nDamage > 0) {
        lo = hit->uFlagsLo;
        if ((lo & 8) == 0 || (lo & 0x80) == 0 || hit->uFlagsHi != 0x80) {
            if ((lo & 0x22) != 0) {
                func_ov260_020cd148(self, pair22.a[*((u8 *)state + 0x7a) & 1], state[4]);
            } else {
                func_ov260_020cd148(self, pair.a[*((u8 *)state + 0x7a) & 1], state[4]);
            }
            *((u8 *)state + 0x7a) ^= 1;
        }
    }
    if (*(short *)(self + 0x21a) == 0) {
        *(u8 *)(*state + 0x1c7) = 3;
        return 1;
    }
    owner = *state;
    if (*(signed char *)(owner + 0x1c6) == 5) {
        if ((hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
            *(u8 *)(owner + 0x1c7) = 0xc;
        }
    } else if (*(signed char *)(owner + 0x1c6) != 0xd) {
        if ((hit->uFlagsLo & 0x8000) != 0) {
            *(u8 *)(owner + 0x1c7) = 0xc;
        } else if (state[0x20] == 0 && *(short *)(owner + 0x21a) <= *(short *)(owner + 0x218) * 0x32 / 100) {
            state[0x20] = 1;
            *(u8 *)(*state + 0x1c7) = 0xd;
        }
    }
    {
        char *o = (char *)*state;

        if (*(int *)(o + 0x470) != 0 && o[0x1c7] == 0xc) {
            o[0x1c7] = saved;
        }
    }
    return 1;
}
