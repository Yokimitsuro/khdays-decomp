/* func_ov025_020835e0 -- advance the menu's page-slide and reset its offset, ov008.
 * Ticks the two page animators (func_ov025_020851a0/020514cc with base+0x959c/0x95a0); once
 * the swap-active bit (bit2 of base+0x95f0) clears it is done. While still swapping, zeroes the
 * scroll offset (base+0x95f8), re-scrolls (func_ov025_02084868(1)) and re-arms the label
 * rebuild (func_ov025_02082c50(3)). */
extern void func_ov025_020851a0(int a);
extern void func_ov025_0208527c(int a);
extern void func_ov025_02084868(int a);
extern void func_ov025_02082c50(int a);
extern int  data_ov025_020b5744[];

void func_ov025_020835e0(void) {
    func_ov025_020851a0(*(int *)(data_ov025_020b5744[1] + 0x959c));
    func_ov025_0208527c(*(int *)(data_ov025_020b5744[1] + 0x95a0));
    if (((unsigned int)*(int *)(data_ov025_020b5744[1] + 0x95f0) << 0x1d >> 0x1f) == 0) {
        return;
    }
    *(int *)(data_ov025_020b5744[1] + 0x95f8) = 0;
    func_ov025_02084868(1);
    func_ov025_02082c50(3);
}
