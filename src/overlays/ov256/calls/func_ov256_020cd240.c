/* Damage handler of the ov256 actor: +0x6c records `guard`. While guarding (moves 2, 4, 5) the hit is
 * blocked: the guard count +0x60 grows, the hit is flagged (+0x24 bit 0) and the next move is 5, or
 * after five blocks the count and +0x78 reset and the next move is 6. Otherwise the hit's damage
 * (020c89e8, into +0x28) scaled by 1 + boost/10 (+0x45c) comes off the health (+0x21a); in rage
 * (+0x80) the +0x5c counter grows; the +0x64 damage tally loses a fifth of the maximum (+0x218) each
 * time it reaches it, except at boost 3; health stays at or above 0. Always returns 1. */
typedef unsigned char u8;
struct HitWord { unsigned lo : 16; unsigned hi : 16; };

extern int func_ov107_020c89e8(char *self, char *hit);

int func_ov256_020cd240(char *self, int guard, char *hit)
{
    int *state = *(int **)(self + 0x214);

    state[0x1b] = guard;
    if (!(*(signed char *)(*state + 0x1c6) != 2 && *(signed char *)(*state + 0x1c6) != 4 &&
          *(signed char *)(*state + 0x1c6) != 5)) {
        state[0x18]++;
        ((struct HitWord *)(hit + 0x24))->lo |= 1;
        if (state[0x18] < 5) {
            *(signed char *)(*state + 0x1c7) = 5;
        } else {
            state[0x18] = 0;
            state[0x1e] = 0;
            *(signed char *)(*state + 0x1c7) = 6;
        }
        return 1;
    }
    *(int *)(hit + 0x28) = func_ov107_020c89e8(self, hit);
    *(short *)(self + 0x21a) -= *(int *)(hit + 0x28) * ((*(int *)(*state + 0x45c) * 10 + 100) / 100);
    if (state[0x20] != 0) {
        state[0x17]++;
    }
    state[0x19] += *(int *)(hit + 0x28);
    if (state[0x19] >= *(short *)(self + 0x218) / 5 && *(int *)(*state + 0x45c) != 3) {
        state[0x19] -= *(short *)(self + 0x218) / 5;
    }
    if (*(short *)(self + 0x21a) < 0) {
        *(short *)(self + 0x21a) = 0;
    }
    return 1;
}
