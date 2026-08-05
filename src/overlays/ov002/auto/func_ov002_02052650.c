/*
 * func_ov002_02052650 - fill a 15x15 tilemap region with a running tile index (ARM, reloc-free).
 *
 * For each cell (i, j) in a 15x15 block, writes a BG map entry into the tilemap at param_1[0x2c]:
 * the target cell is buf[(i + 8) * 32 + j + 0x11] (rows offset down by 8, columns by 0x11 in a
 * 32-wide map) and the value is a tile id that increments in row-major order,
 * (param_1[0x14] + i*15 + j + 0x15), OR'd with the 0xc000 palette/priority attribute bits.
 *
 * i*15 is left as `i * 0xf` so mwcc strength-reduces it to the `ip += 0xf` induction variable;
 * the param_1[0x14] load is written last in the value expression so it is added after the index
 * terms and lands in the register the ROM uses. The two base pointers are re-read each iteration
 * because a store may alias them.
 */
void func_ov002_02052650(int param_1)
{
    int i, j;
    for (i = 0; i < 0xf; i++) {
        for (j = 0; j < 0xf; j++) {
            short *buf = (short *)*(int *)(param_1 + 0x2c);
            buf[(i + 8) * 32 + j + 0x11] =
                (j + i * 0xf + 0x15 + *(int *)(param_1 + 0x14)) | 0xc000;
        }
    }
}
