/* Move pick of the ov256 actor: a d100 roll is drawn and the target re-picked (020ccd54). When the
 * +0x50 idle time is out the roll and the gap (+0x58) choose the next move; move 0xa (claw attack)
 * needs all four claws (+0x43c..+0x448) idle (+0x394 clear). Below boost 4: closer than 16.0 -> 8
 * (< 30) or 9; closer than 32.0 -> 0xa (< 40), 0xd (< 45) or 8; farther -> 0xa (< 20) or 0xd. At boost
 * 4: closer than 16.0 -> 8 (< 5), 9 (< 65) or 6; closer than 32.0 -> 0xa (< 25), 8 (< 75) or 6;
 * farther -> 0xa (< 10), 0xd (< 90) or 6. A target beyond x 14.0 always gets 0xd. When a move was
 * picked the idle time is rolled between the +0x224 / +0x228 bounds and 1 is returned, else 0. */
typedef unsigned short u16;

extern int func_02023eb4(int n);
extern int func_ov256_020ccd54(int *node);

#define CLAWS_IDLE(a) (*(int *)(*(int *)((a) + 0x43c) + 0x394) == 0 && *(int *)(*(int *)((a) + 0x440) + 0x394) == 0 && \
                       *(int *)(*(int *)((a) + 0x444) + 0x394) == 0 && *(int *)(*(int *)((a) + 0x448) + 0x394) == 0)

int func_ov256_020ccdf0(int *node)
{
    int *state = (int *)node[1];
    u16 roll = func_02023eb4(100);

    func_ov256_020ccd54(node);
    if (state[0x14] == 0) {
        int actor = *state;

        if (*(int *)(actor + 0x45c) != 4) {
            if (state[0x16] < 0x10000) {
                if (roll < 0x1e) {
                    *(signed char *)(actor + 0x1c7) = 8;
                } else {
                    *(signed char *)(actor + 0x1c7) = 9;
                }
            } else if (state[0x16] < 0x20000) {
                if (roll < 0x28 && CLAWS_IDLE(actor)) {
                    *(signed char *)(actor + 0x1c7) = 0xa;
                } else if (roll < 0x2d) {
                    *(signed char *)(actor + 0x1c7) = 0xd;
                } else {
                    *(signed char *)(actor + 0x1c7) = 8;
                }
            } else {
                if (roll < 0x14 && CLAWS_IDLE(actor)) {
                    *(signed char *)(actor + 0x1c7) = 0xa;
                } else {
                    *(signed char *)(actor + 0x1c7) = 0xd;
                }
            }
        } else {
            if (state[0x16] < 0x10000) {
                if (roll < 5) {
                    *(signed char *)(actor + 0x1c7) = 8;
                } else if (roll < 0x41) {
                    *(signed char *)(actor + 0x1c7) = 9;
                } else {
                    *(signed char *)(actor + 0x1c7) = 6;
                }
            } else if (state[0x16] < 0x20000) {
                if (roll < 0x19 && CLAWS_IDLE(actor)) {
                    *(signed char *)(actor + 0x1c7) = 0xa;
                } else if (roll < 0x4b) {
                    *(signed char *)(actor + 0x1c7) = 8;
                } else {
                    *(signed char *)(actor + 0x1c7) = 6;
                }
            } else {
                if (roll < 0xa && CLAWS_IDLE(actor)) {
                    *(signed char *)(actor + 0x1c7) = 0xa;
                } else if (roll < 0x5a) {
                    *(signed char *)(actor + 0x1c7) = 0xd;
                } else {
                    *(signed char *)(actor + 0x1c7) = 6;
                }
            }
        }
        if (*(int *)(*(int *)(*state + 0x430) + 0x190) >= 0xe000) {
            *(signed char *)(*state + 0x1c7) = 0xd;
        }
    }
    if (*(signed char *)(*state + 0x1c7) != -1) {
        int lo = *(int *)(*state + 0x224);
        int v = *(int *)(*state + 0x228) - lo;

        if (v < 0) {
            v = -v;
        }
        state[0x14] = lo + func_02023eb4(v + 1);
        return 1;
    }
    return 0;
}
