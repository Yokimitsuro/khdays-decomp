/* func_ov024_020831dc -- MobiClip player: restore the fades to a known state and re-arm the
 * display. Any fade level other than the two extremes (+/-0x10) is forced to -0x10 on both
 * screens; then the display is brought back up and POWCNT1 bit 15 (LCD enable) set. */
extern int  func_0201e428(void);
extern void func_0201e374(int level);
extern int  func_0201e438(void);
extern void func_0201e3cc(int level);
extern void func_0201e1d0(void);
extern void func_ov024_0208462c(int a, int b);

void func_ov024_020831dc(void) {
    int dark = -0x10;
    int level;

    level = func_0201e428();
    if (level != dark && level != 0x10) {
        level = dark;
    }
    func_0201e374(level);

    level = func_0201e438();
    if (level != dark && level != 0x10) {
        level = dark;
    }
    func_0201e3cc(level);

    func_0201e1d0();
    func_ov024_0208462c(1, 1);
    *(volatile unsigned short *)0x04000304 = *(volatile unsigned short *)0x04000304 | 0x8000;
}
