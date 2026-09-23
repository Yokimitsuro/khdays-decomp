/* Target check: the actor's +0x3dc target is re-picked (020cab14). With one, a move is requested
 * once the +0x3c cooldown has run out: 5 while the +0x78 aggressive flag is set, otherwise 7 when
 * the +0x468 partner's +0x388 latch is clear. When a move is pending the cooldown restarts (8.0
 * aggressive, 15.0 otherwise) and 1 is returned; else 0. */
extern int func_ov107_020cab14(int obj, int flag);

int func_ov254_020cd080(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x3dc) = func_ov107_020cab14(*state, 0);
    if (*(int *)(*state + 0x3dc) != 0) {
        if (state[0x1e] != 0) {
            if (state[0xf] <= 0) {
                *(signed char *)(*state + 0x1c7) = 5;
            }
        } else if (state[0xf] <= 0 && *(int *)(*(int *)(*state + 0x468) + 0x388) == 0) {
            *(signed char *)(*state + 0x1c7) = 7;
        }
    }
    if (*(signed char *)(*state + 0x100 + 0xc7) != -1) {
        state[0xf] = (state[0x1e] != 0 ? 8 : 0xf) << 12;
        return 1;
    }
    return 0;
}
