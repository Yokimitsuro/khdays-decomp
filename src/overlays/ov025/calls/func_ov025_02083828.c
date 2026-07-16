/* func_ov025_02083828 -- advance the menu's page-swap animation one step, ov008.
 * Ticks the two page animators (func_ov025_020851a0 / 020514cc); once the swap-active bit
 * (bit2 of base+0x95f0) clears, it is done. While still swapping, refreshes the page contents
 * (func_ov025_02082fd4(1)) and re-arms the label rebuild (func_ov025_02082c50(3)). */
extern void func_ov025_020851a0(int a);
extern void func_ov025_0208527c(int a);
extern void func_ov025_02082fd4(int a);
extern void func_ov025_02082c50(int a);
extern int  data_ov025_020b5744[];

void func_ov025_02083828(void) {
    func_ov025_020851a0(*(int *)(data_ov025_020b5744[1] + 0x959c));
    func_ov025_0208527c(*(int *)(data_ov025_020b5744[1] + 0x95a0));
    if (((unsigned int)*(int *)(data_ov025_020b5744[1] + 0x95f0) << 0x1d >> 0x1f) == 0) {
        return;
    }
    func_ov025_02082fd4(1);
    func_ov025_02082c50(3);
}
