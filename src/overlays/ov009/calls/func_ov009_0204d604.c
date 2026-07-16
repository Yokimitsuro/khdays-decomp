/* func_ov009_0204d604 -- advance the menu's simple page-slide one step, ov008.
 * Ticks the two page animators (func_ov009_0204e750/020514cc with their scroll accumulators
 * at base+0x959c/0x95a0); once the swap-active bit (bit2 of base+0x95f0) clears it is done,
 * otherwise re-arms the label rebuild (func_ov009_0204cb6c(8)). */
extern void func_ov009_0204e750(int a);
extern void func_ov009_0204e82c(int a);
extern void func_ov009_0204cb6c(int a);
extern int  data_ov009_020563e4[];

void func_ov009_0204d604(void) {
    func_ov009_0204e750(*(int *)(data_ov009_020563e4[1] + 0x959c));
    func_ov009_0204e82c(*(int *)(data_ov009_020563e4[1] + 0x95a0));
    if (((unsigned int)*(int *)(data_ov009_020563e4[1] + 0x95f0) << 0x1d >> 0x1f) == 0) {
        return;
    }
    func_ov009_0204cb6c(8);
}
