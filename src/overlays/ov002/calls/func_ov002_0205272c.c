/*
 * func_ov002_0205272c - advance a timed effect's countdown one frame (ARM).
 *
 * On the first tick (state 3) it switches the effect to the running state 2 and seeds the countdown
 * with half of the configured duration (rounded up). On later ticks it decrements the countdown,
 * clamping at 0. After ticking the effect body via func_ov002_020524ec it reports completion: when
 * the countdown has reached 0 it clears the state and returns 1, otherwise returns 0.
 */
typedef struct {
    int state;       /* +0x00 */
    int countdown;   /* +0x04 */
    char _8[0x24 - 8];
    int duration;    /* +0x24 */
} Ov002TimedEffect;

extern void func_ov002_020524ec(int fx);

int func_ov002_0205272c(Ov002TimedEffect *fx)
{
    if (fx->state == 3) {
        fx->state = 2;
        fx->countdown = (fx->duration + 1) / 2;
    } else {
        int v = fx->countdown - 1;
        fx->countdown = v;
        if (v < 0) fx->countdown = 0;
    }
    func_ov002_020524ec((int)fx);
    if (fx->countdown <= 0) {
        fx->state = 0;
        return 1;
    }
    return 0;
}
