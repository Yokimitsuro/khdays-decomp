/* Move picker of the ov237 actor: once the +0x28 cooldown is spent and a target is in range (020cd830,
 * -1 = none) the next move follows a d100 roll by distance. Paired with a partner that is not busy
 * (+0x4a4's +0x4b0 clear): under 7.0 5 / 7 (with +0x60) / 9 (with +0x64) else 5; under 12.0
 * 5 / 6 / 7 / 9; under 28.0 5 / 6 / 9. Alone (or with a busy partner): under 7.0 5 / 7 / 9 / 5, under
 * 20.0 5 / 6 / 7 / 9 / 5, under 32.0 6 / 9 / 6, where 7 and 9 also need no +0x4b8 hold. A picked move
 * restarts the cooldown (4.0) and returns 1. */
typedef unsigned short u16;

extern int func_ov237_020cd830(int *node);
extern int func_02023eb4(int bound);

int func_ov237_020cd8c8(int *node)
{
    int *state = (int *)node[1];

    if (state[0xa] <= 0) {
        int dist = func_ov237_020cd830(node);

        if (dist != -1) {
            u16 roll = func_02023eb4(100);
            char *actor = (char *)*state;

            if (*(int *)(actor + 0x4ac) != 0 && *(int *)(*(int *)(actor + 0x4a4) + 0x4b0) == 0) {
                if (dist < 0x7000) {
                    if (roll < 0x19) {
                        *(signed char *)(actor + 0x1c7) = 5;
                    } else if (roll < 0x55 && state[0x18] != 0) {
                        *(signed char *)(actor + 0x1c7) = 7;
                    } else if (state[0x19] != 0) {
                        *(signed char *)(actor + 0x1c7) = 9;
                    } else {
                        *(signed char *)(actor + 0x1c7) = 5;
                    }
                } else if (dist < 0xc000) {
                    if (roll < 0x19) {
                        *(signed char *)(actor + 0x1c7) = 5;
                    } else if (roll < 0x3c) {
                        *(signed char *)(actor + 0x1c7) = 6;
                    } else if (roll < 0x50) {
                        *(signed char *)(actor + 0x1c7) = 7;
                    } else {
                        *(signed char *)(actor + 0x1c7) = 9;
                    }
                } else if (dist < 0x1c000) {
                    if (roll < 10) {
                        *(signed char *)(actor + 0x1c7) = 5;
                    } else if (roll < 0x37) {
                        *(signed char *)(actor + 0x1c7) = 6;
                    } else {
                        *(signed char *)(actor + 0x1c7) = 9;
                    }
                }
            } else if ((*(int *)(actor + 0x4ac) != 0 && *(int *)(*(int *)(actor + 0x4a4) + 0x4b0) != 0) ||
                       *(int *)(actor + 0x4ac) == 0) {
                if (dist < 0x7000) {
                    if (roll < 5) {
                        *(signed char *)(actor + 0x1c7) = 5;
                    } else if (roll < 0x4b && *(int *)(actor + 0x4b8) == 0 && state[0x18] != 0) {
                        *(signed char *)(actor + 0x1c7) = 7;
                    } else if (*(int *)(actor + 0x4b8) == 0 && state[0x19] != 0) {
                        *(signed char *)(actor + 0x1c7) = 9;
                    } else {
                        *(signed char *)(actor + 0x1c7) = 5;
                    }
                } else if (dist < 0x14000) {
                    if (roll < 8) {
                        *(signed char *)(actor + 0x1c7) = 5;
                    } else if (roll < 0x12) {
                        *(signed char *)(actor + 0x1c7) = 6;
                    } else if (roll < 0x46 && *(int *)(actor + 0x4b8) == 0 && state[0x18] != 0) {
                        *(signed char *)(actor + 0x1c7) = 7;
                    } else if (*(int *)(actor + 0x4b8) == 0 && state[0x19] != 0) {
                        *(signed char *)(actor + 0x1c7) = 9;
                    } else {
                        *(signed char *)(actor + 0x1c7) = 5;
                    }
                } else if (dist < 0x20000) {
                    if (roll < 0x19) {
                        *(signed char *)(actor + 0x1c7) = 6;
                    } else if (*(int *)(actor + 0x4b8) == 0 && state[0x19] != 0) {
                        *(signed char *)(actor + 0x1c7) = 9;
                    } else {
                        *(signed char *)(actor + 0x1c7) = 6;
                    }
                }
            }
        }
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        state[0xa] = 0x4000;
        return 1;
    }
    return 0;
}
