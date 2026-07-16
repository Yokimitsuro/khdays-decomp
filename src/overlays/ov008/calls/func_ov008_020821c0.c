/* func_ov008_020821c0 -- per-frame refresh of the ov008 panel widget.
 * Ticks the widget (ctx+0xbfb8); unless the panel is in mode 2 with a live handle (ctx+0xc250 == 2
 * && ctx+0xc51c != 0), resets its stream (ctx+0xbff0); then advances it by 0x1000. */
extern void func_02023cc0(void *node);
extern void func_0202aa9c(unsigned short *p);
extern void func_0202a818(unsigned short *p, int step);
extern int  data_ov008_02090fac;   /* -> panel context */

void func_ov008_020821c0(void) {
    int ctx = data_ov008_02090fac;
    int w = ctx + 0xbfb8;
    func_02023cc0((void *)w);
    if (*(int *)(ctx + 0xc250) != 2 || *(int *)(ctx + 0xc51c) == 0) {
        func_0202aa9c((unsigned short *)(w + 0x38));
    }
    func_0202a818((unsigned short *)(w + 0x38), 0x1000);
}
