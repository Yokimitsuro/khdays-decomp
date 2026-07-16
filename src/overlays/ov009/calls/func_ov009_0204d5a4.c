/* func_ov009_0204d5a4 -- advance the menu's page-swap animation one step, ov008.
 * Ticks the two page animators (func_ov009_0204e750 / 020514cc); once the swap-active bit
 * (bit2 of base+0x95f0) clears, it is done. While still swapping, refreshes the page contents
 * (func_ov009_0204cec0(1)) and re-arms the label rebuild (func_ov009_0204cb6c(3)). */
extern void func_ov009_0204e750(int a);
extern void func_ov009_0204e82c(int a);
extern void func_ov009_0204cec0(int a);
extern void func_ov009_0204cb6c(int a);
extern int  data_ov009_020563e4[];

void func_ov009_0204d5a4(void) {
    func_ov009_0204e750(*(int *)(data_ov009_020563e4[1] + 0x959c));
    func_ov009_0204e82c(*(int *)(data_ov009_020563e4[1] + 0x95a0));
    if (((unsigned int)*(int *)(data_ov009_020563e4[1] + 0x95f0) << 0x1d >> 0x1f) == 0) {
        return;
    }
    func_ov009_0204cec0(1);
    func_ov009_0204cb6c(3);
}
