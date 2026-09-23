/* Damage handler of the ov283 actor: while alive, the hit's point (+4) becomes the +0x1c knock-back
 * point, the hit's damage (020c89e8, into +0x28) comes off the health (+0x21a, clamped to 0..max) and
 * the attacker is remembered (+0xc). A damaging hit plays alternating hurt sounds 0x173 (flag 0x22
 * picks the first pair) at the +8 point. The +0x50 stagger clock gains 1.99; at or below the +0x3e8
 * percentage of the maximum (or at 0 health) the next move is 3, else a heavy hit (flag 0x8000) makes
 * it 0xb. Returns 1 (0 when already down). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 a, b; } Pair2;
typedef struct { unsigned lo : 16; unsigned hi : 16; } HitWord;

extern u8 data_ov283_020cfb64[];
extern int func_ov107_020c89e8(char *self, char *hit);
extern void func_ov283_020cc92c(char *actor, int bank, int variant, int at);

int func_ov283_020cc690(char *self, int attacker, char *hit)
{
    u8 pickB[2];
    u8 pickA[2];
    int *state;
    int hp;
    int limit;

    *(Pair2 *)pickB = *(Pair2 *)&data_ov283_020cfb64[2];
    *(Pair2 *)pickA = *(Pair2 *)&data_ov283_020cfb64[0];
    state = *(int **)(self + 0x214);
    if (*(short *)(self + 0x21a) <= 0) {
        return 0;
    }
    *(int *)(hit + 0x28) = func_ov107_020c89e8(self, hit);
    hp = *(short *)(self + 0x21a) - *(int *)(hit + 0x28);
    *(short *)(self + 0x21a) = hp < 0 ? 0 : (hp > *(short *)(self + 0x218) ? *(short *)(self + 0x218) : hp);
    state[3] = attacker;
    *(Vec3 *)(state + 7) = *(Vec3 *)(hit + 4);
    if (*(int *)(hit + 0x28) > 0) {
        if (((HitWord *)hit)->lo & 0x22) {
            func_ov283_020cc92c(self, 0x173, pickA[*((u8 *)state + 0x80)], state[2]);
        } else {
            func_ov283_020cc92c(self, 0x173, pickB[*((u8 *)state + 0x80)], state[2]);
        }
        *((u8 *)state + 0x80) ^= 1;
    }
    state[0x14] += 0x1fe0;
    limit = *(short *)(self + 0x218) * *(int *)(*state + 0x3e8) / 100;
    if (*(short *)(self + 0x21a) <= limit) {
        *(u8 *)(*state + 0x1c7) = 3;
        return 1;
    }
    if (*(short *)(self + 0x21a) == 0) {
        *(u8 *)(*state + 0x1c7) = 3;
        return 1;
    }
    if (((HitWord *)hit)->lo & 0x8000) {
        *(u8 *)(*state + 0x1c7) = 0xb;
    }
    return 1;
}
