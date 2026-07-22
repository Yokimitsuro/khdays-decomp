/* Retarget then re-anchor a mission cell by tag: look the cell up in the active record's list,
 * move it to (x, y), then look it up again and re-anchor it.
 *
 * Parked as a CSE tie -- the original recomputes `(tag << 16) >> 16` before each lookup while
 * mwcc caches it. Nothing is being cached: the truncation belongs to the CALL, not to the
 * source expression. func_ov008_02055808's tag parameter is an `unsigned short`, so the caller
 * has to narrow at every call site, and writing `tag & 0xffff` in C instead puts one value in
 * the caller's own dataflow where mwcc is free to reuse it.
 *
 * Same for x and y: the mover takes `short`, which is where the pair of lsl/asr comes from. */
extern int  func_ov008_02050c28(void);
extern int  func_ov008_02055808(int list, unsigned short tag);
extern void func_ov008_02055874(int list, int cell, short x, short y);
extern void func_ov008_0205589c(int list, int cell);

void func_ov008_0206abb8(unsigned int tag, int x, int y) {
    int list = func_ov008_02050c28();
    func_ov008_02055874(list, func_ov008_02055808(list, tag), x, y);
    func_ov008_0205589c(list, func_ov008_02055808(list, tag));
}
