/* Start the panel's fade tween at +0xf8: mode 1, from 0 to full (0x18000) over
 * 300 frames, then sample it once so the first frame is already correct. */
extern void func_02035fb0(void *tween, int mode, int from, int to, int duration);
extern void func_02035ffc(void *tween);

extern char *data_ov002_0207f614;

void func_ov002_020555c8(void) {
    char *ctx = data_ov002_0207f614;

    func_02035fb0(ctx + 0xf8, 1, 0, 0x18000, 300);
    func_02035ffc(ctx + 0xf8);
}
