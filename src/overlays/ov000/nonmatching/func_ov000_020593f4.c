/* func_ov000_020593f4 -- scroll the logo list to a clamped row, ov000.
 * NONMATCHING: instruction-scheduling tie. The retail build keeps the row max in a
 * separate register and interleaves the pixel-offset math between the two clamps;
 * our mwcc serializes them. Logic is exact. For the port.
 * Only acts when the list has >8 rows; clamps the row to [0, rows-0xa], converts it to
 * a pixel offset ((0x14-rowHeight)*8) and applies via func_ov000_02059264. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern int  func_02020400(int fixed);
extern void func_ov000_02059264(int offset);
void func_ov000_020593f4(int row) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    if (h[0x15] <= 8) {
        return;
    }
    h[0x16] = row;
    if (row < 0) {
        row = 0;
    }
    if (row > h[0x15] - 0xa) {
        row = h[0x15] - 0xa;
    }
    func_ov000_02059264(h[0x18] + func_02020400(row * ((0x14 - h[0x17]) << 3)));
}
