/* Record the row's target at +0x1204 and start that row's 0x1c-byte tween at
 * +0x11b0 running to 0x64000 over 1000 frames, sampling it once. */
extern void func_02035fb0(void *tween, int mode, int from, int to, int duration);
extern void func_02035ffc(void *tween);

extern char *data_ov002_0207f628;

void func_ov002_02061c58(int row, int target) {
    char *ctx = data_ov002_0207f628;
    char *tween;

    *(int *)(ctx + row * 4 + 0x1204) = target;
    tween = ctx + 0x11b0 + row * 0x1c;
    func_02035fb0(tween, 0, 0, 0x64000, 1000);
    func_02035ffc(tween);
}
