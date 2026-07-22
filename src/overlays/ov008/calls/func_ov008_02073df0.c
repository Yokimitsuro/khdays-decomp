/* Update the hovered mission row while dragging. Same gate and same shape as
 * func_ov008_02073d88, which does it for the grid: the panel has to be fully idle (+0x68,
 * +0x4f8, +0x30 clear), input enabled and the page not 7. Re-resolves the row and, if it
 * changed from the stored one at +0x54, stores it and refreshes.
 *
 * func_ov008_02072d9c takes TWO arguments, the object and the new row. The park had it as one
 * and read the resulting `mov r1,r0` as the compiler being smarter than the original -- it is
 * the second argument. */
extern int  func_ov008_02051028(void);
extern int  func_ov008_0205b7b4(void);
extern unsigned int func_ov008_0206fce0(int obj, int cell);
extern void func_ov008_02072d9c(unsigned int *obj, unsigned int cell);

void func_ov008_02073df0(unsigned int *obj) {
    unsigned int row;
    if (obj[0x1a] != 0 || obj[0x13e] != 0 || obj[0xc] != 0) {
        return;
    }
    if (func_ov008_02051028() == 0) {
        return;
    }
    if (func_ov008_0205b7b4() == 7) {
        return;
    }
    row = func_ov008_0206fce0((int)obj, 1);
    if (row != *(unsigned char *)((char *)obj + 0x54)) {
        *(unsigned char *)((char *)obj + 0x54) = (unsigned char)row;
        func_ov008_02072d9c(obj, row);
    }
}
