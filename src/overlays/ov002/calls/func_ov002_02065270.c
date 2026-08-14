/* Refresh the cursor's cell coordinates in the layout context.
 *
 * The current point is converted to cell space, rounded to the nearest whole cell -- adding 0x800
 * before shifting twelve is round-to-nearest in 20.12 fixed point -- and biased by 0x3c and 0x28
 * before being stored.
 *
 * Both rounded values are bound to locals before either is stored. That is what interleaves the
 * two coordinates the way the original does; writing the expressions inline finishes one
 * coordinate before starting the other.
 *
 * Ghidra carries the two fields as nCursorCellX and nCursorCellY on Ov002LayoutContext.
 */

extern char *data_ov002_0207f638;
extern int func_01fffe14(void);
extern void *func_ov022_020881f8(int index);
extern void func_ov002_02064cd8(int *out, void *point);

void func_ov002_02065270(void) {
    char *layout = data_ov002_0207f638;
    int cell[2];

    func_ov002_02064cd8(cell, func_ov022_020881f8(func_01fffe14()));
    {
        int x = (cell[0] + 0x800) >> 12;
        int y = (cell[1] + 0x800) >> 12;

        *(int *)(layout + 8) = x - 0x3c;
        *(int *)(layout + 0xc) = y - 0x28;
    }
}
