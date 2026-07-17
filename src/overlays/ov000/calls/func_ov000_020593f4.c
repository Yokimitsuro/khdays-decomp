/* func_ov000_020593f4 -- scroll the logo list to a clamped row, ov000.
 *
 * Only acts when the list has more than 8 rows. Clamps `row` into [0, rows-0xa], then converts it
 * to a pixel offset and applies it via func_ov000_02059264:
 *
 *     offset = h[0x18] + row * ((0x14 - rowHeight) * 8) / (rows - 0xa)
 *
 * i.e. a scrollbar thumb: the row's position scaled across the free travel. The divisor is the
 * SAME `max` used for the clamp, which is why the ROM keeps it in its own register.
 *
 * ★ func_02020400 is the divide helper and takes TWO arguments (num, den), returning quotient in
 * r0 and remainder in r1 -- so it must be declared `long long`. This file declared it as
 * `int func_02020400(int fixed)`, a one-argument fixed-point call that does not exist, and then
 * blamed the resulting diff on scheduling: "instruction-scheduling tie. The retail build keeps the
 * row max in a separate register and interleaves the pixel-offset math between the two clamps; our
 * mwcc serializes them." The "row max in a separate register" WAS the missing divisor. (2026-07-17)
 */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern long long func_02020400(int num, int den);
extern void func_ov000_02059264(int offset);
void func_ov000_020593f4(int row) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    int max;

    if (h[0x15] <= 8) {
        return;
    }
    h[0x16] = row;
    max = h[0x15] - 0xa;
    if (row < 0) {
        row = 0;
    }
    if (row > max) {
        row = max;
    }
    func_ov000_02059264(h[0x18] + (int)func_02020400(row * ((0x14 - h[0x17]) << 3), max));
}
