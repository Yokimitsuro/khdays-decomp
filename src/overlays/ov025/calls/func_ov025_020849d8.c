/* Clear a rectangular run of BG map cells for a grid row: resolve the object's tile buffer once,
 * then for each of `rows` rows map (x, y+i) to a tile offset -- using the row stride from the
 * shared screen context -- and zero `cells` entries there.
 *
 * Parked as a register/scheduling tie. Three separate spellings were doing it:
 *   - the global has to be `data[1]`, not `*(int *)((int)data + 4)`;
 *   - the guard is `rows <= 0`, not `rows < 1` (the original tests `cmp #0` with `pople`);
 *   - the destination address has to be a NAMED LOCAL. Passed inline as
 *     `MIi_CpuClear16(0, dst + f(...) * 2, ...)`, mwcc materialises the literal 0 into r0 first
 *     and has to copy the call's result out of the way; computed into `addr` first, the add
 *     happens while r0 still holds the result, which is what the original does. */
extern int  func_ov025_02083b2c(int obj, int *out);
extern int  func_ov025_02083b70(int x, int y, int stride, int width);
extern void MIi_CpuClear16(int val, int dst, int bytes);
extern int  data_ov025_020b5744[];   /* [1] -> shared screen context */

void func_ov025_020849d8(int obj, int x, int y, int cells, int rows) {
    int i;
    int dst;

    dst = func_ov025_02083b2c(obj, 0);
    i = 0;
    if (rows <= 0) {
        return;
    }
    do {
        int addr = dst + func_ov025_02083b70(x, y + i,
                       *(int *)((char *)data_ov025_020b5744[1] + 0x95d0), 0x20) * 2;
        MIi_CpuClear16(0, addr, cells << 1);
        i++;
    } while (i < rows);
}
