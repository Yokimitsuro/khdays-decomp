/* func_ov008_02050ab8 -- set the menu's active-page index and sync its control bits, ov008.
 * Writes the page index into the scene object: pushes it as a byte cursor position
 * (func_ov008_02055c08 on obj+0x954c), updates the two page control bits at obj+0x4a80
 * (func_ov008_02054e4c / 02054e24), and stores the raw index at obj+0x9604. */
extern void func_ov008_02055c08(int p, unsigned int v);
extern void func_ov008_02054e4c(int p, unsigned int v);
extern void func_ov008_02054e24(int p, unsigned int v);
extern int  data_ov008_02090f04[];

void func_ov008_02050ab8(unsigned int page) {
    func_ov008_02055c08(data_ov008_02090f04[1] + 0x954c, page);
    func_ov008_02054e4c(data_ov008_02090f04[1] + 0x4a80, page);
    func_ov008_02054e24(data_ov008_02090f04[1] + 0x4a80, page);
    *(unsigned int *)(data_ov008_02090f04[1] + 0x9604) = page;
}
