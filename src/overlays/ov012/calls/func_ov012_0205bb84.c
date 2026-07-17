/* ★ func_0202fa20 takes TWO arguments; this file declared one. The dropped 0 is the ROM's
 * `mov r1, #0` at +0x00, shared with the two field stores. (2026-07-17)
 *
 */

extern void func_0202fa20(int p, int b);

void func_ov012_0205bb84(int p) {
    *(int *)(p + 0x6c) = 0;
    *(int *)(p + 0x5c) = 0;
    *(int *)(p + 0x50) = 1;
    func_0202fa20(p, 0);
}
