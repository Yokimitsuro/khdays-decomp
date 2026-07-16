/* func_ov025_020848e0 -- set the menu's active-page index and sync its control bits, ov008.
 * Writes the page index into the scene object: pushes it as a byte cursor position
 * (func_ov025_02089818 on obj+0x954c), updates the two page control bits at obj+0x4a80
 * (func_ov025_02088af4 / 02054e24), and stores the raw index at obj+0x9604. */
extern void func_ov025_02089818(int p, unsigned int v);
extern void func_ov025_02088af4(int p, unsigned int v);
extern void func_ov025_02088acc(int p, unsigned int v);
extern int  data_ov025_020b5744[];

void func_ov025_020848e0(unsigned int page) {
    func_ov025_02089818(data_ov025_020b5744[1] + 0x954c, page);
    func_ov025_02088af4(data_ov025_020b5744[1] + 0x4a80, page);
    func_ov025_02088acc(data_ov025_020b5744[1] + 0x4a80, page);
    *(unsigned int *)(data_ov025_020b5744[1] + 0x9604) = page;
}
