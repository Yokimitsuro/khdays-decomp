/* Idle tick of the ov297 enemy: measures the target gap, counts the +0x38 timer down and, once
 * spent without a +0x84 alert, re-arms the +0x3c timer at random between the actor's +0x224 and
 * +0x228; beyond 0x9000 sub-state 2 is requested, else the +0x28 turn is rolled (0x1922 to
 * 0x3243) and sub-state 4 requested when still unalerted; the state ends. While the timer
 * runs an alert with the target closer than 0x8d00 raises bits 0-1 of +0x1ae and requests
 * sub-state 3. */
extern int func_ov297_020d4168(void *node);
extern int func_02023eb4(int range);
extern unsigned int func_02023e80(unsigned int range);
extern void func_0203c634(int *node, int slot, void *cb);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov297_020d480c(int *node)
{
    int *state = (int *)node[1];
    int gap;

    gap = func_ov297_020d4168(node);
    state[0xe] -= *(int *)(*node + 0x2c);
    if (state[0xe] <= 0 && state[0x20] == 0) {
        state[0x10] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        if (gap > 0x9000) {
            *(unsigned char *)(*state + 0x1c7) = 2;
        } else {
            state[10] = func_02023e80(0x1922) + 0x1922;
            if (state[0x20] == 0) {
                *(unsigned char *)(*state + 0x1c7) = 4;
            }
        }
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x20] == 0) {
        return;
    }
    if (gap >= 0x8d00) {
        return;
    }
    *(unsigned short *)(*state + 0x1ae) |= 3;
    *(unsigned char *)(*state + 0x1c7) = 3;
}
