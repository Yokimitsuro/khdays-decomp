/* Retarget the scene's tween at +0x58 to the caller's range over 50 frames and
 * sample it immediately. The context is the SECOND word at data_ov002_0207f62c. */
extern void func_02035fb0(void *tween, int mode, int from, int to, int duration);
extern void func_02035ffc(void *tween);

extern char *data_ov002_0207f62c;

void func_ov002_020637d4(int from, int to) {
    char *ctx = (&data_ov002_0207f62c)[1];

    func_02035fb0(ctx + 0x58, 0, from, to, 50);
    func_02035ffc(ctx + 0x58);
}
