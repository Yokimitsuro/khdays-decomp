/* func_ov008_0204d6f8 -- reset the menu display to the page-list layout, ov008.
 * Restores the two capture/blend engines (func_0201e374/3cc -0x10), clears the BG-mode bits of
 * both DISPCNT registers and re-enables the LCD (POWCNT1), then reprograms the BG priorities:
 * main BG0..3 = 3/0/1/2, sub BG0..3 = 0/1/2/3 (preserving each register's char/screen bits). */
typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
extern void func_0201e374(int a);
extern void func_0201e3cc(int a);

void func_ov008_0204d6f8(void) {
    vu16 *sub = (vu16 *)0x04001008;
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    *(vu32 *)0x04000000 &= ~0x1f00;
    *(vu32 *)0x04001000 &= ~0x1f00;
    *(vu16 *)0x04000304 |= 0x8000;
    *(vu16 *)0x04000008 = *(vu16 *)0x04000008 & ~3 | 3;
    *(vu16 *)0x0400000a = *(vu16 *)0x0400000a & ~3;
    *(vu16 *)0x0400000c = *(vu16 *)0x0400000c & ~3 | 1;
    *(vu16 *)0x0400000e = *(vu16 *)0x0400000e & ~3 | 2;
    sub[0] = sub[0] & ~3;
    sub[1] = sub[1] & ~3 | 1;
    sub[2] = sub[2] & ~3 | 2;
    sub[3] = sub[3] & ~3 | 3;
}
