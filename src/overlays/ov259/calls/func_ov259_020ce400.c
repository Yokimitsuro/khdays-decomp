/* Think slot of the ov259 actor: it picks a stance by a d100 roll (above 80: 020cd590 1, else 0) and
 * keeps facing its target; the +0x68 decision and +0x74 idle clocks run. After 0xaa0 idle on the
 * ground (+0x4c clear) a d100 roll of 5 or less queues move 8, otherwise the idle clock restarts; a
 * grounded actor whose +0x8c clock reaches 0x1de20 queues move 0xe and ends. When the decision clock
 * passes +0x84 a new d100 roll picks the next move by range (020cdd48) in body radii (+0x80):
 * grounded, closer than 4 / 7 / beyond: 0xb (<= 60 / 40), 0xd (<= 90 / 95 / 10) or 0xc; airborne,
 * closer than 5 / 12 / beyond: 0x11 (<= 55 / 15), 0x10 (<= 95 / 70 / 10) or 0x12. The next decision
 * waits 0x1fe0 on the ground. */
extern int func_02023eb4(int n);
extern void func_ov259_020cd590(int *node, int stance);
extern void func_ov259_020cd5d4(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov259_020cdd48(int *node);

void func_ov259_020ce400(int *node)
{
    int *state = (int *)node[1];
    int roll;
    int range;

    if ((unsigned int)func_02023eb4(100) <= 0x50) {
        func_ov259_020cd590(node, 0);
    } else {
        func_ov259_020cd590(node, 1);
    }
    func_ov259_020cd5d4(node);
    state[0x1a] += *(int *)(node[0] + 0x2c);
    state[0x1d] += *(int *)(node[0] + 0x2c);
    if (state[0x1d] > 0xaa0 && state[0x13] == 0) {
        if (func_02023eb4(0x65) + (roll - roll) <= 5) {
            *(signed char *)(*state + 0x1c7) = 8;
        } else {
            state[0x1d] = 0;
        }
    }
    if (state[0x13] == 0 && state[0x23] >= 0x1de20) {
        state[0x23] = 0;
        *(signed char *)(*state + 0x1c7) = 0xe;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x1a] <= state[0x21]) {
        return;
    }
    roll = func_02023eb4(0x65) + (roll - roll);
    if (state[0x13] == 0) {
        state[0x21] = 0x1fe0;
    } else {
        state[0x21] = 0;
    }
    range = func_ov259_020cdd48(node);
    if (state[0x13] == 0) {
        int actor = *state;
        int radius = *(int *)(actor + 0x80);

        if (range < radius * 4) {
            if (roll <= 0x3c) {
                *(signed char *)(actor + 0x1c7) = 0xb;
            } else if (roll <= 0x5a) {
                *(signed char *)(actor + 0x1c7) = 0xd;
            } else {
                *(signed char *)(actor + 0x1c7) = 0xc;
            }
        } else if (range < radius * 7) {
            if (roll <= 0x28) {
                *(signed char *)(actor + 0x1c7) = 0xb;
            } else if (roll <= 0x5f) {
                *(signed char *)(actor + 0x1c7) = 0xd;
            } else {
                *(signed char *)(actor + 0x1c7) = 0xc;
            }
        } else {
            if (roll <= 10) {
                *(signed char *)(actor + 0x1c7) = 0xd;
            } else {
                *(signed char *)(actor + 0x1c7) = 0xc;
            }
        }
    } else {
        int actor = *state;
        int radius = *(int *)(actor + 0x80);

        if (range < radius * 5) {
            if (roll <= 0x37) {
                *(signed char *)(actor + 0x1c7) = 0x11;
            } else if (roll <= 0x5f) {
                *(signed char *)(actor + 0x1c7) = 0x10;
            } else {
                *(signed char *)(actor + 0x1c7) = 0x12;
            }
        } else if (range < radius * 12) {
            if (roll <= 0xf) {
                *(signed char *)(actor + 0x1c7) = 0x11;
            } else if (roll <= 0x46) {
                *(signed char *)(actor + 0x1c7) = 0x10;
            } else {
                *(signed char *)(actor + 0x1c7) = 0x12;
            }
        } else {
            if (roll <= 10) {
                *(signed char *)(actor + 0x1c7) = 0x10;
            } else {
                *(signed char *)(actor + 0x1c7) = 0x12;
            }
        }
    }
}
