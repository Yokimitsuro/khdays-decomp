/* Move picker of the ov258 actor: with a target in reach (020cd028) the rage stage follows the health
 * (below a third 2, below half 1, else 0) and the next move is rolled from 3 up to 3 + stage + 2,
 * skipping the last one (+0x55); a queued +0x56 move overrides it. One-time moves fire as health drops:
 * stage 1 move 6 (+0x54 bit 7), stage 2 move 7 (bit 6), below 80 % move 8 (bit 5), below 15 % move 8
 * (bit 4). A picked move rolls the +0x38 delay between the +0x224 and +0x228 bounds, is remembered in
 * +0x55 and returns 1. */
typedef unsigned char u8;

extern int func_ov258_020cd028(int *node, int face);
extern int func_02023eb4(int bound);

int func_ov258_020cd2cc(int *node)
{
    int *state = (int *)node[1];
    signed char stage;
    u8 picked;
    int max;
    int hp;

    hp = *(short *)(*state + 0x21a);
    max = *(short *)(*state + 0x218);
    if (func_ov258_020cd028(node, 1) == 0) {
        return 0;
    }
    stage = hp < max / 3 ? 2 : (hp < max / 2 ? 1 : 0);
    for (picked = 0; picked < 1;) {
        signed char move = func_02023eb4(stage + 3) + 3;

        if (move != *((signed char *)state + 0x55)) {
            *(signed char *)(*state + 0x1c7) = move;
            picked++;
        }
    }
    if (*((signed char *)state + 0x56) != -1) {
        *(signed char *)(*state + 0x1c7) = *((signed char *)state + 0x56);
        *((signed char *)state + 0x56) = -1;
    }
    switch (stage) {
    case 1:
        if (*((u8 *)state + 0x54) & 0x80) {
            *((u8 *)state + 0x54) -= 0x80;
            *(signed char *)(*state + 0x1c7) = 6;
        }
        break;
    case 2:
        if (*((u8 *)state + 0x54) & 0x40) {
            *((u8 *)state + 0x54) -= 0x40;
            *(signed char *)(*state + 0x1c7) = 7;
        }
        break;
    }
    if (hp < max / 10 * 8 && (*((u8 *)state + 0x54) & 0x20)) {
        *((u8 *)state + 0x54) -= 0x20;
        *(signed char *)(*state + 0x1c7) = 8;
    }
    if (hp < max / 100 * 15 && (*((u8 *)state + 0x54) & 0x10)) {
        *((u8 *)state + 0x54) -= 0x10;
        *(signed char *)(*state + 0x1c7) = 8;
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        {
            int lo = *(int *)(*state + 0x224);
            int span = *(int *)(*state + 0x228) - lo;

            if (span < 0) {
                span = -span;
            }
            state[0xe] = lo + func_02023eb4(span + 1);
        }
        *((signed char *)state + 0x55) = *(signed char *)(*state + 0x1c7);
        return 1;
    }
    return 0;
}
