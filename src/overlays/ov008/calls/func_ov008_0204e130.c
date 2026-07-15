/* func_ov008_0204e130 -- tear down the menu's 2D display, ov008.
 * Releases the menu's object/graphics engine binding (func_ov008_02050614), restores the
 * two capture/blend engines (func_0201e374/3cc with -0x10), clears the BG-mode/screen-base
 * bits of both DISPCNT registers, and re-enables the LCD via POWCNT1. Returns 0. */
typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
extern void func_ov008_02050614(int a);
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);

int func_ov008_0204e130(void) {
    func_ov008_02050614(0);
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    *(vu32 *)0x04000000 &= ~0x1f00;
    *(vu32 *)0x04001000 &= ~0x1f00;
    *(vu16 *)0x04000304 |= 0x8000;
    return 0;
}
