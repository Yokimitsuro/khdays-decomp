/* func_ov000_02059910 -- (re)build the logo text window, ov000. Refreshes the display
 * (func_02033b78), lays out the text buffer @ctx+0xd118 (func_02035fb0/func_02035ffc),
 * and arms the window state @ctx+0x966a = 2. */
extern void func_02033b78(int, int);
extern void func_02035fb0(void *buf, int, int, int, int);
extern void func_02035ffc(void *buf);
void func_ov000_02059910(char *ctx) {
    func_02033b78(0, 3);
    func_02035fb0(ctx + 0xd118, 0, 0, 0x1000, 0x1f4);
    func_02035ffc(ctx + 0xd118);
    *(short *)(ctx + 0x966a) = 2;
}
