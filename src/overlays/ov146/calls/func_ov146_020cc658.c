/* Damage handler of the ov146 actor: while alive, the hit's point (+4) becomes the +0x1c knock-back
 * point, the hit's damage (020c89e8, into +0x28) comes off the health (+0x21a, clamped to 0..max) and
 * the attacker is remembered (+0x54). A damaging hit that is not a blocked special (flags 8|0x80 with
 * kind 0x80) plays alternating hurt sounds 0x125 (flag 0x22 picks the second pair). At 0 health the
 * next move is 3; a heavy hit (flag 0x8000) outside move 9 keeps its 0x22 flags in +0x5c and makes 9
 * next. Returns 1 (0 when already down). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 a, b; } Pair2;
typedef struct { unsigned lo : 16; unsigned hi : 16; } HitWord;

extern u8 data_ov146_020cf50c[];
extern int func_ov107_020c89e8(char *self, char *hit);
extern void func_ov107_020c5af8(char *actor, int bank, int variant, void *at);

int func_ov146_020cc658(char *self, int attacker, char *hit)
{
    u8 pickB[2];
    u8 pickA[2];
    int *state;
    int hp;

    *(Pair2 *)pickB = *(Pair2 *)&data_ov146_020cf50c[2];
    *(Pair2 *)pickA = *(Pair2 *)&data_ov146_020cf50c[0];
    state = *(int **)(self + 0x214);
    if (*(short *)(self + 0x21a) <= 0) {
        return 0;
    }
    *(Vec3 *)(state + 7) = *(Vec3 *)(hit + 4);
    *(int *)(hit + 0x28) = func_ov107_020c89e8(self, hit);
    hp = *(short *)(self + 0x21a) - *(int *)(hit + 0x28);
    *(short *)(self + 0x21a) = hp < 0 ? 0 : (hp > *(short *)(self + 0x218) ? *(short *)(self + 0x218) : hp);
    state[0x15] = attacker;
    if (*(int *)(hit + 0x28) > 0) {
        if (!((((HitWord *)hit)->lo & 8) && (((HitWord *)hit)->lo & 0x80) && ((HitWord *)hit)->hi == 0x80)) {
            if (((HitWord *)hit)->lo & 0x22) {
                func_ov107_020c5af8(self, 0x125, pickA[*((u8 *)state + 0x51)], (void *)state[3]);
            } else {
                func_ov107_020c5af8(self, 0x125, pickB[*((u8 *)state + 0x51)], (void *)state[3]);
            }
            *((u8 *)state + 0x51) ^= 1;
        }
    }
    if (*(short *)(self + 0x21a) == 0) {
        *(u8 *)(*state + 0x1c7) = 3;
    } else if ((((HitWord *)hit)->lo & 0x8000) && *(signed char *)(*state + 0x1c6) != 9) {
        state[0x17] = ((HitWord *)hit)->lo & 0x22;
        *(u8 *)(*state + 0x1c7) = 9;
    }
    return 1;
}
