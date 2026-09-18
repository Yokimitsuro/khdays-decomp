/* Idle countdown of the ov240 enemy: the +0x38 timer counts the frame-time down and, once spent,
 * re-arms at random between the actor's +0x224 and +0x228 and requests a sub-state by range: up to
 * 0x3000 6 (roll below 60) or 4, below 0x10000 7 (roll below 50) or 5, else 5 (roll below 80)
 * or 4. Returns 1 when a sub-state was requested. */
extern int func_02023eb4(int range);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

int func_ov240_020ce804(int *node, int dist)
{
    int *state = (int *)node[1];
    int roll;

    state[0xe] -= *(int *)(*node + 0x2c);
    if (state[0xe] <= 0) {
        roll = func_02023eb4(0x64);
        state[0xe] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        if (dist <= 0x3000) {
            *(unsigned char *)(*state + 0x1c7) = roll < 0x3c ? 6 : 4;
        } else if (dist < 0x10000) {
            *(unsigned char *)(*state + 0x1c7) = roll < 0x32 ? 7 : 5;
        } else {
            *(unsigned char *)(*state + 0x1c7) = roll < 0x50 ? 5 : 4;
        }
        if (*(signed char *)(*state + 0x1c7) != -1) {
            return 1;
        }
    }
    return 0;
}
