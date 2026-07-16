/* NONMATCHING: -8B CSE tie (twin of func_ov006_02053cdc) -- the ROM recomputes (tag<<16)>>16
 * before each FindEntryByTag call; our mwcc caches the mask. Retarget mission cell by tag. */
/* func_ov008_0206abb8 -- retarget then re-anchor a mission cell by tag, ov008.
 * Looks up the cell with the given tag in the active record's cell list (func_ov008_02050c28)
 * and moves it to (x, y) via func_ov008_02055874, then re-looks it up and re-anchors it via
 * func_ov008_0205589c. */
extern int  func_ov008_02050c28(void);
extern int  func_ov008_02055808(int list, unsigned int tag);
extern void func_ov008_02055874(int list, int cell, short x, short y);
extern void func_ov008_0205589c(int list, int cell);

void func_ov008_0206abb8(unsigned int tag, short x, short y) {
    int list = func_ov008_02050c28();
    int cell = func_ov008_02055808(list, tag & 0xffff);
    func_ov008_02055874(list, cell, x, y);
    cell = func_ov008_02055808(list, tag & 0xffff);
    func_ov008_0205589c(list, cell);
}
