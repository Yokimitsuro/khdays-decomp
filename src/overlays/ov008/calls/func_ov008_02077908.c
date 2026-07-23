/* func_ov008_02077908 -- scroll the mission list by param_2 and push the resulting bar position.
 * Clamps the offset (obj+0x168) to [-0x40, span-0x40], where span = (rowCount - 0xc) * 8 for the
 * current page (obj + obj[1] * 4 + 0x144), then maps the clamped offset through the runtime
 * divide into the scroll-bar position.
 *
 * Declaration order carries two separate decisions: `span` first, because the ROM loads the page
 * index before the current offset; and `lim` before `pos`, which is what puts the offset in r0
 * and the limit in r2 at the clamp. The two values are symmetric there, so nothing else
 * distinguishes them. */
extern int  func_02020400(int a, int b);
extern void func_ov008_02074758(int obj, int bar);

void func_ov008_02077908(int param_1, int param_2) {
    int span = (*(int *)(param_1 + *(int *)(param_1 + 4) * 4 + 0x144) - 0xc) * 8;
    int lim = span - 0x40;
    int pos = *(int *)(param_1 + 0x168) + param_2;

    *(int *)(param_1 + 0x168) = pos;
    if (pos > lim) {
        *(int *)(param_1 + 0x168) = lim;
    }
    if (*(int *)(param_1 + 0x168) < -0x40) {
        *(int *)(param_1 + 0x168) = -0x40;
    }
    func_ov008_02074758(param_1,
        func_02020400((0x60 - *(int *)(param_1 + 0x164)) * (*(int *)(param_1 + 0x168) + 0x40), span));
}
