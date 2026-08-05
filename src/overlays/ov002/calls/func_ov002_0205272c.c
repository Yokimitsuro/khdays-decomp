/*
 * func_ov002_0205272c - advance a timed effect's countdown one frame (ARM).
 *
 * On the first tick (state at +0 equal to 3) it switches the effect to the running state 2 and
 * seeds the countdown at +4 with half of the configured duration at +0x24 (rounded up). On later
 * ticks it decrements the countdown, clamping at 0. After ticking the effect body via
 * func_ov002_020524ec, it reports completion: when the countdown has reached 0 it clears the state
 * and returns 1, otherwise returns 0.
 */
extern void func_ov002_020524ec(int a);

int func_ov002_0205272c(int param_1)
{
    if (*(int *)param_1 == 3) {
        *(int *)param_1 = 2;
        *(int *)(param_1 + 4) = (*(int *)(param_1 + 0x24) + 1) / 2;
    } else {
        int v = *(int *)(param_1 + 4) - 1;
        *(int *)(param_1 + 4) = v;
        if (v < 0) *(int *)(param_1 + 4) = 0;
    }
    func_ov002_020524ec(param_1);
    if (*(int *)(param_1 + 4) <= 0) {
        *(int *)param_1 = 0;
        return 1;
    }
    return 0;
}
