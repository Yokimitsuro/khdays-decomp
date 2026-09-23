/* Damage handler of the ov218 actor (unless +0x1ac bit 0 shields it, it is down or in move 3): the
 * hit's point becomes the +0x34 knock-back point, the hit's damage (020c89e8, into +0x28) comes off the
 * health (clamped to 0..max) and the attacker is remembered (+0x44). A damaging hit that is not a
 * blocked special plays alternating hurt sounds 0x135 (flag 0x22 picks the first pair). At 0 health the
 * next move is 3; otherwise, outside move 9, an unattributed hit makes 9 next and a heavy hit (flag
 * 0x8000) keeps its 0x22 flags in +0x64 and makes 7 next. Returns 1 (0 when ignored). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 a, b; } Pair2;
typedef struct { unsigned lo : 16; unsigned hi : 16; } HitWord;

extern u8 data_ov218_020cf310[];
extern int func_ov107_020c89e8(char *self, char *hit);
extern void func_ov107_020c5af8(char *actor, int bank, int variant, void *at);

int func_ov218_020cc5bc(char *self, int attacker, char *hit)
{
    u8 pickB[2];
    u8 pickA[2];
    int *state;
    int hp;

    *(Pair2 *)pickB = *(Pair2 *)&data_ov218_020cf310[0];
    *(Pair2 *)pickA = *(Pair2 *)&data_ov218_020cf310[2];
    state = *(int **)(self + 0x214);
    if (*(unsigned short *)(self + 0x1ac) & 1) {
        return 0;
    }
    if (*(short *)(self + 0x21a) <= 0) {
        return 0;
    }
    if (*(signed char *)(*state + 0x1c6) == 3) {
        return 0;
    }
    *(Vec3 *)(state + 0xd) = *(Vec3 *)(hit + 4);
    *(int *)(hit + 0x28) = func_ov107_020c89e8(self, hit);
    hp = *(short *)(self + 0x21a) - *(int *)(hit + 0x28);
    *(short *)(self + 0x21a) = hp < 0 ? 0 : (hp > *(short *)(self + 0x218) ? *(short *)(self + 0x218) : hp);
    state[0x11] = attacker;
    if (*(int *)(hit + 0x28) > 0) {
        if (!((((HitWord *)hit)->lo & 8) && (((HitWord *)hit)->lo & 0x80) && ((HitWord *)hit)->hi == 0x80)) {
            if (((HitWord *)hit)->lo & 0x22) {
                func_ov107_020c5af8(self, 0x135, pickA[*((u8 *)state + 0x41)], (void *)state[2]);
            } else {
                func_ov107_020c5af8(self, 0x135, pickB[*((u8 *)state + 0x41)], (void *)state[2]);
            }
            *((u8 *)state + 0x41) ^= 1;
        }
    }
    if (*(short *)(self + 0x21a) == 0) {
        *(u8 *)(*state + 0x1c7) = 3;
    } else if (*(signed char *)(*state + 0x1c6) != 9) {
        if (attacker == 0) {
            *(u8 *)(*state + 0x1c7) = 9;
        } else if (((HitWord *)hit)->lo & 0x8000) {
            state[0x19] = ((HitWord *)hit)->lo & 0x22;
            *(u8 *)(*state + 0x1c7) = 7;
        }
    }
    return 1;
}
