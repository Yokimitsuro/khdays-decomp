/* Idle countdown of the ov220 enemy. The +0x18 timer loses the frame-time; once it runs out a
 * percentage is rolled, the timer is re-rolled to +0x224 + rand(|+0x228 - +0x224| + 1), a caller
 * distance of 0x6000 or more forces sub-state 5 and one above 0x3800 picks sub-state 5 (roll
 * below 75) or 7; the call reports 1 when a sub-state is pending. */
typedef unsigned char u8;

extern int func_02023eb4(int bound);

int func_ov220_020d2384(int *node, int value)
{
    int *state = (int *)node[1];
    int roll;
    int lo;
    int d;

    state[6] -= *(int *)(*node + 0x2c);
    if (state[6] <= 0) {
        roll = func_02023eb4(100);
        lo = *(int *)(*state + 0x224);
        d = *(int *)(*state + 0x228) - lo;
        state[6] = lo + func_02023eb4((d < 0 ? -d : d) + 1);
        if (value >= 0x6000) {
            *(u8 *)(*state + 0x1c7) = 5;
        } else if (value > 0x3800) {
            *(u8 *)(*state + 0x1c7) = roll < 0x4b ? 5 : 7;
        }
        if (*(signed char *)(*state + 0x1c7) != -1) {
            return 1;
        }
    }
    return 0;
}
