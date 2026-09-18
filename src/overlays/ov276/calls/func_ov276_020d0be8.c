/* Idle countdown of the ov276 enemy: once the +0x54 timer is spent it re-arms at random between
 * the actor's +0x224 and +0x228 and either replays the queued +0x60 sub-state, or, with an 80%
 * roll and the target closer than 0x3000, a 50% roll sets the +0x5c flag, zeroes the timer and
 * requests sub-state 4 (queueing 6 or, on a first roll of 80 and up, nothing) while the other
 * half requests sub-state 6. Returns 1 when a sub-state was requested. */
extern int func_02023eb4(int range);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

int func_ov276_020d0be8(int *node, int dist)
{
    int *state = (int *)node[1];
    int roll;

    if (state[0x15] <= 0) {
        roll = func_02023eb4(0x64);
        state[0x15] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        if (*(signed char *)(state + 0x18) != -1) {
            *(signed char *)(*state + 0x1c7) = *(signed char *)(state + 0x18);
            *(signed char *)(state + 0x18) = -1;
        } else if ((unsigned int)func_02023eb4(0x64) >= 0x14 && dist < 0x3000) {
            if ((unsigned int)func_02023eb4(0x64) < 0x32) {
                state[0x17] = 1;
                state[0x15] = 0;
                *(unsigned char *)(*state + 0x1c7) = 4;
                if (roll < 0x50) {
                    *(signed char *)(state + 0x18) = 6;
                } else {
                    *(signed char *)(state + 0x18) = -1;
                }
            } else {
                *(unsigned char *)(*state + 0x1c7) = 6;
            }
        }
        if (*(signed char *)(*state + 0x1c7) != -1) {
            return 1;
        }
    }
    return 0;
}
