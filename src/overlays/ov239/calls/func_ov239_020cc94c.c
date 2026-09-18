/* Idle countdown of the ov239 enemy: the +0x2c timer counts the frame-time down and, once spent,
 * re-arms at random between the actor's +0x224 and +0x228 and requests sub-state 5 (roll below
 * 65 with the target closer than 0x6000) or 6. Returns 1 when a sub-state was requested. */
extern int func_02023eb4(int range);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

int func_ov239_020cc94c(int *node, int dist)
{
    int *state = (int *)node[1];
    int roll;

    state[0xb] -= *(int *)(*node + 0x2c);
    if (state[0xb] <= 0) {
        roll = func_02023eb4(0x64);
        state[0xb] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        if (dist < 0x6000) {
            *(unsigned char *)(*state + 0x1c7) = roll < 0x41 ? 5 : 6;
        } else {
            *(unsigned char *)(*state + 0x1c7) = 6;
        }
        if (*(signed char *)(*state + 0x1c7) != -1) {
            return 1;
        }
    }
    return 0;
}
