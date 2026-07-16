/* NONMATCHING: correct; -4B CSE tie. The ROM saves the raw tag in a callee-saved reg and
 * recomputes (tag<<16)>>16 before each of the two FindEntryByTag calls; our mwcc computes the
 * mask once and reuses it. Retarget-cell-by-tag wrapper. */
/* func_ov006_02053cdc -- retarget then re-anchor a Mission Mode cell by tag, ov006.
 * Looks up the cell with the given tag in the Mission Mode object's cell list (base+8) and moves it
 * to (param_2, param_3) via func_ov006_0204d4a0, then re-looks it up and re-anchors it via
 * func_ov006_0204d4c8. */
extern int  func_ov006_0204d434(int list, unsigned int tag);
extern void func_ov006_0204d4a0(int list, int cell, short x, short y);
extern void func_ov006_0204d4c8(int list, int cell);
extern int  data_ov006_02056664;

void func_ov006_02053cdc(unsigned int tag, short x, short y) {
    int cell = func_ov006_0204d434(data_ov006_02056664 + 8, tag & 0xffff);
    func_ov006_0204d4a0(data_ov006_02056664 + 8, cell, x, y);
    cell = func_ov006_0204d434(data_ov006_02056664 + 8, tag & 0xffff);
    func_ov006_0204d4c8(data_ov006_02056664 + 8, cell);
}
