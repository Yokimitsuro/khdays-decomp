/* Hold the context's tween at +0xfd0 fully open (0x1f000 to 0x1f000) for the
 * duration stored at +0x1064, sample it immediately and clear the pending word
 * at +0xd0. */
extern void func_02035fb0(void *tween, int mode, int from, int to, int duration);
extern void func_02035ffc(void *tween);

extern char *data_ov002_0207f628;

void func_ov002_0206030c(void) {
    char *ctx = data_ov002_0207f628;

    func_02035fb0(ctx + 0xfd0, 0, 0x1f000, 0x1f000, *(int *)(ctx + 0x1064));
    func_02035ffc(ctx + 0xfd0);
    *(int *)(ctx + 0xd0) = 0;
}
