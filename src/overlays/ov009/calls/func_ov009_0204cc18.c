/* func_ov009_0204cc18 -- reset the menu's four scroll/animation sub-objects, ov008.
 * Runs func_0202ff7c on each of the four animator blocks at base+0x9680/0x968c/0x9698/0x96a4. */
extern void func_0202ff7c(int obj);
extern int  data_ov009_020563e4[];

void func_ov009_0204cc18(void) {
    func_0202ff7c(data_ov009_020563e4[1] + 0x9680);
    func_0202ff7c(data_ov009_020563e4[1] + 0x968c);
    func_0202ff7c(data_ov009_020563e4[1] + 0x9698);
    func_0202ff7c(data_ov009_020563e4[1] + 0x96a4);
}
