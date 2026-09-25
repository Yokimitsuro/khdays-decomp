/* Damage handler of the ov237 actor: while alive and not separating (move 0xc) a heavy hit
 * (flag 8, high flag 8) in move 7 may stagger it (d100 below the per-limb data chance, +0x49e = 3,
 * +0x60 cleared) and a limb hit (flag 8, high flag 4, limb 2) in move 9 without a hold sets the
 * +0x4b4 hold (+0x64 cleared). The damage (020c89e8, into +0x28) comes off the health (clamped); at 0
 * a free linked partner keeps the pair alive at up to 5 health (and a far target, 35.0, outside move
 * 10 is remembered), otherwise the next move is 0xc and the partner is told (+0x4a8). A damaging hit
 * that is not a blocked special plays alternating hurt sounds 0x12d at the +0x488 rig (flag 0x22
 * picks the first pair). Returns 1 (0 when down or separating). */
typedef unsigned char u8;
typedef struct { u8 a, b; } Pair2;
typedef struct { short v[3]; } Chance3;
typedef struct { Pair2 heavy; Pair2 light; Chance3 chance; } Ov237HurtTmpl;
typedef struct { unsigned lo : 16; unsigned hi : 16; } HitWord;

extern int func_02023eb4(int bound);
extern int func_ov107_020c89e8(char *self, char *hit);
extern void func_ov107_020c5af8(char *actor, int bank, int variant, int at);
extern const Ov237HurtTmpl data_ov237_020d1b34;

int func_ov237_020cd1bc(char *self, int attacker, char *hit)
{
    Chance3 chance = data_ov237_020d1b34.chance;
    int *state = *(int **)(self + 0x214);
    int hp;

    if (*(short *)(self + 0x21a) <= 0) {
        return 0;
    }
    if (*(signed char *)(*state + 0x1c6) == 0xc) {
        return 0;
    }
    if (*(signed char *)(*state + 0x1c6) == 7 && (((HitWord *)hit)->lo & 8) && (((HitWord *)hit)->hi & 8) &&
        (unsigned int)func_02023eb4(100) < chance.v[*(u8 *)(hit + 0x1d)] && *(u8 *)(*state + 0x49e) != 3) {
        state[0x18] = 0;
        *(u8 *)(*state + 0x49e) = 3;
    }
    if (*(signed char *)(*state + 0x1c6) == 9 && (((HitWord *)hit)->lo & 8) && (((HitWord *)hit)->hi & 4) &&
        *(u8 *)(hit + 0x1d) == 2 && *(int *)(*state + 0x4b4) == 0) {
        state[0x19] = 0;
        *(int *)(*state + 0x4b4) = 1;
    }
    *(int *)(hit + 0x28) = func_ov107_020c89e8(self, hit);
    hp = *(short *)(self + 0x21a) - *(int *)(hit + 0x28);
    *(short *)(self + 0x21a) = hp < 0 ? 0 : (hp > *(short *)(self + 0x218) ? *(short *)(self + 0x218) : hp);
    if (*(short *)(self + 0x21a) <= 0) {
        {
            /* Down: health is reset to 0 and tested against the maximum again. Both outcomes are
             * 0, but the ROM keeps the load of the maximum and the compare. */
            int max = *(short *)(self + 0x218);
            int health = 0;

            if (health > max) {
                health = 0;
            }
            *(short *)(self + 0x21a) = health;
        }
        if (*(int *)(*state + 0x4ac) != 0 && *(int *)(*(int *)(*state + 0x4a4) + 0x4b0) == 0) {
            *(short *)(self + 0x21a) = *(short *)(self + 0x218) >= 5 ? 5 : *(short *)(self + 0x218);
            if (state[0xb] < 0x23000 && state[0x17] == 0 && *(signed char *)(*state + 0x1c6) != 10) {
                state[0xb] = 0x23000;
            }
        }
        if (*(short *)(self + 0x21a) == 0) {
            *(signed char *)(*state + 0x1c7) = 0xc;
            if (*(int *)(*state + 0x4ac) != 0) {
                *(int *)(*(int *)(*state + 0x4a4) + 0x4a8) = 1;
            }
        }
    }
    if (*(int *)(hit + 0x28) > 0) {
        if (!((((HitWord *)hit)->lo & 8) && (((HitWord *)hit)->lo & 0x80) && ((HitWord *)hit)->hi == 0x80)) {
            if (((HitWord *)hit)->lo & 0x22) {
                u8 pick[2];

                *(Pair2 *)pick = data_ov237_020d1b34.heavy;
                func_ov107_020c5af8(self, 0x12d, pick[++*((u8 *)state + 0x56) & 1], **(int **)(self + 0x488) + 4);
            } else {
                u8 pick[2];

                *(Pair2 *)pick = data_ov237_020d1b34.light;
                func_ov107_020c5af8(self, 0x12d, pick[++*((u8 *)state + 0x56) & 1], **(int **)(self + 0x488) + 4);
            }
        }
    }
    return 1;
}
