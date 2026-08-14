/* Slide the scene out, if it is allowed to.
 *
 * The tween runs from zero to minus one screen width over fifty frames, and the scene moves to
 * phase 3 once it is running. Nothing happens at all when the check refuses.
 *
 * The tween address is written as the context plus 0x58 at both call sites rather than held in a
 * local, which is what makes the original form it twice.
 */

extern char *data_ov002_0207f62c[];
extern int func_ov002_02052ab8(void);
extern void func_02035fb0(void *tween, int from, int to, int flags, int frames);
extern void func_02035ffc(void *tween);

void func_ov002_02062ad8(void) {
    char *ctx = data_ov002_0207f62c[1];

    if (func_ov002_02052ab8()) {
        func_02035fb0(ctx + 0x58, 0, -0x10000, 0, 0x32);
        func_02035ffc(ctx + 0x58);
        *(int *)(ctx + 8) = 3;
    }
}
