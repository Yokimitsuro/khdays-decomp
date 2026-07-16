/* func_ov009_0204d35c -- advance the menu's page-slide and reset its offset, ov008.
 * Ticks the two page animators (func_ov009_0204e750/020514cc with base+0x959c/0x95a0); once
 * the swap-active bit (bit2 of base+0x95f0) clears it is done. While still swapping, zeroes the
 * scroll offset (base+0x95f8), re-scrolls (func_ov009_0204e3b4(1)) and re-arms the label
 * rebuild (func_ov009_0204cb6c(3)). */
extern void func_ov009_0204e750(int a);
extern void func_ov009_0204e82c(int a);
extern void func_ov009_0204e3b4(int a);
extern void func_ov009_0204cb6c(int a);
extern int  data_ov009_020563e4[];

void func_ov009_0204d35c(void) {
    func_ov009_0204e750(*(int *)(data_ov009_020563e4[1] + 0x959c));
    func_ov009_0204e82c(*(int *)(data_ov009_020563e4[1] + 0x95a0));
    if (((unsigned int)*(int *)(data_ov009_020563e4[1] + 0x95f0) << 0x1d >> 0x1f) == 0) {
        return;
    }
    *(int *)(data_ov009_020563e4[1] + 0x95f8) = 0;
    func_ov009_0204e3b4(1);
    func_ov009_0204cb6c(3);
}
