/* Retarget then re-anchor a mission cell by tag: look the cell up in the active record's list,
 * move it to (x, y), then look it up again and re-anchor it.
 *
 * Parked as a CSE tie -- the original recomputes `(tag << 16) >> 16` before each lookup while
 * mwcc caches it. Nothing is being cached: the truncation belongs to the CALL, not to the
 * source expression. func_ov025_020894b0's tag parameter is an `unsigned short`, so the caller
 * has to narrow at every call site, and writing `tag & 0xffff` in C instead puts one value in
 * the caller's own dataflow where mwcc is free to reuse it.
 *
 * Same for x and y: the mover takes `short`, which is where the pair of lsl/asr comes from. */
extern int  func_ov025_02084a50(void);
extern int  func_ov025_020894b0(int list, unsigned short tag);
extern void func_ov025_0208951c(int list, int cell, short x, short y);
extern void func_ov025_02089544(int list, int cell);

void func_ov025_0209cc88(unsigned int tag, int x, int y) {
    int list = func_ov025_02084a50();
    func_ov025_0208951c(list, func_ov025_020894b0(list, tag), x, y);
    func_ov025_02089544(list, func_ov025_020894b0(list, tag));
}
