/* func_ov008_0204fa60 -- advance the menu's simple page-slide one step, ov008.
 * Ticks the two page animators (func_ov008_020513f0/020514cc with their scroll accumulators
 * at base+0x959c/0x95a0); once the swap-active bit (bit2 of base+0x95f0) clears it is done,
 * otherwise re-arms the label rebuild (func_ov008_0204ee28(8)). */
extern void func_ov008_020513f0(int a);
extern void func_ov008_020514cc(int a);
extern void func_ov008_0204ee28(int a);
extern int  data_ov008_02090f04[];

void func_ov008_0204fa60(void) {
    func_ov008_020513f0(*(int *)(data_ov008_02090f04[1] + 0x959c));
    func_ov008_020514cc(*(int *)(data_ov008_02090f04[1] + 0x95a0));
    if (((unsigned int)*(int *)(data_ov008_02090f04[1] + 0x95f0) << 0x1d >> 0x1f) == 0) {
        return;
    }
    func_ov008_0204ee28(8);
}
