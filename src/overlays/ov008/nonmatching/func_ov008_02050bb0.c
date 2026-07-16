/* NONMATCHING: semantics correct; ties on register allocation (dst/i in r5<->r6) plus a
 * one-instruction scheduling diff in the MIi_CpuClear16 arg setup. No C reordering reproduced
 * the ROM's reg choice. */
/* func_ov008_02050bb0 -- clear a horizontal run of BG map cells for an ov008 grid row.
 * dst = tile buffer for param_1 (func_ov008_0204fd04); then for each of param_5 columns, map
 * (param_2, param_3+i) to a tile offset via func_ov008_0204fd48 (row stride from the shared
 * screen ctx +0x95d0, width 0x20) and zero param_4 cells there (MIi_CpuClear16). ov008. */
extern int  func_ov008_0204fd04(int obj, int *out);
extern int  func_ov008_0204fd48(int x, int y, int stride, int width);
extern void MIi_CpuClear16(int val, int dst, int bytes);
extern int  data_ov008_02090f04[];   /* [1] -> shared screen context */

void func_ov008_02050bb0(int param_1, int param_2, int param_3, int param_4, int param_5) {
    int i = 0;
    int dst = func_ov008_0204fd04(param_1, 0);
    if (param_5 < 1) {
        return;
    }
    do {
        int off = func_ov008_0204fd48(param_2, param_3 + i,
                      *(int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x95d0), 0x20);
        MIi_CpuClear16(0, dst + off * 2, param_4 << 1);
        i++;
    } while (i < param_5);
}
