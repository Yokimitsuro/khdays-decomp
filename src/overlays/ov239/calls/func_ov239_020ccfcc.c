/* Wander entry of the ov239 enemy: re-arms the +0x2c timer at random between the actor's
 * +0x224 and +0x228 and configures sub-state 2 (part action 0, flag 1) before handing off to
 * cd028. */
extern int func_02023eb4(int range);
extern void func_ov239_020cc9f0(int *node, int anim, int action, int flag, void *next);
extern void func_ov239_020cd028(int *node);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov239_020ccfcc(int *node)
{
    int *state = (int *)node[1];

    state[0xb] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    func_ov239_020cc9f0(node, 2, 0, 1, func_ov239_020cd028);
}
