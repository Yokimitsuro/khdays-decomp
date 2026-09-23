/* Move pick of the ov238 actor: with a target (020d0878 gives its distance) a roll decides: under 3.0
 * mostly 6 (30 % a front swipe 7, from ahead of -15.0 on z, else 6); under 6.0 5 % 6, 60 % 7/8 by the
 * front test, else 8; under 9.0 20 % 7/8, else 8. When a move is set +0x28 is 3.0 and 1 is returned. */
typedef unsigned short u16;

extern int func_ov238_020d0878(int *node);
extern int func_02023eb4(int bound);

int func_ov238_020d0b2c(int *node)
{
    int *state = (int *)node[1];
    int front = *(int *)(state[2] + 8) >= -0xf000;
    int dist = func_ov238_020d0878(node);

    if (dist != -1) {
        u16 roll = func_02023eb4(0x64);

        if (dist < 0x3000) {
            if (roll < 0x46) {
                *(unsigned char *)(*state + 0x1c7) = 6;
            } else if (front) {
                *(unsigned char *)(*state + 0x1c7) = 7;
            } else {
                *(unsigned char *)(*state + 0x1c7) = 6;
            }
        } else if (dist < 0x6000) {
            if (roll < 5) {
                *(unsigned char *)(*state + 0x1c7) = 6;
            } else if (roll < 0x41) {
                if (front) {
                    *(unsigned char *)(*state + 0x1c7) = 7;
                } else {
                    *(unsigned char *)(*state + 0x1c7) = 8;
                }
            } else {
                *(unsigned char *)(*state + 0x1c7) = 8;
            }
        } else if (dist < 0x9000) {
            if (roll < 0x14) {
                if (front) {
                    *(unsigned char *)(*state + 0x1c7) = 7;
                } else {
                    *(unsigned char *)(*state + 0x1c7) = 8;
                }
            } else {
                *(unsigned char *)(*state + 0x1c7) = 8;
            }
        }
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        state[0xa] = 0x3000;
        return 1;
    }
    return 0;
}
