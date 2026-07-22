/* Refresh the highlighted grid cell from the pointer. Only proceeds while the widget has no
 * pending sub-target (+0x68, +0x4f8, +0x30 all clear), input is enabled and the current page is
 * not 7; then re-picks the hovered cell and, if it changed from the stored one at +0x54, stores
 * it and rebuilds the highlight.
 *
 * func_ov008_02072d9c takes TWO arguments -- the object AND the new cell. That is what forces
 * the original's `mov r1,r0` after the pick: with a one-argument callee mwcc stores straight out
 * of r0 and sets up the call afterwards, and the copy has nowhere to come from. The proof is in
 * the original: `mov r0,r4` is emitted BEFORE the strb, so r1 is still live and holding the cell
 * when the bl runs. func_ov008_0206fce0 takes two arguments as well, not four.
 *
 * The three-field gate is a plain `||` chain; the park's b3/b4 transcription of the conditional
 * compares was reconstructing what the compiler does on its own. */
extern int  func_ov008_02051028(void);
extern int  func_ov008_0205b7b4(void);
extern unsigned int func_ov008_0206fce0(int obj, int cell);
extern void func_ov008_02072d9c(unsigned int *obj, unsigned int cell);

void func_ov008_02073d88(unsigned int *obj) {
    unsigned int cell;
    if (obj[0x1a] != 0 || obj[0x13e] != 0 || obj[0xc] != 0) {
        return;
    }
    if (func_ov008_02051028() == 0) {
        return;
    }
    if (func_ov008_0205b7b4() == 7) {
        return;
    }
    cell = func_ov008_0206fce0((int)obj, -1);
    if (cell != *(unsigned char *)((char *)obj + 0x54)) {
        *(unsigned char *)((char *)obj + 0x54) = (unsigned char)cell;
        func_ov008_02072d9c(obj, cell);
    }
}
