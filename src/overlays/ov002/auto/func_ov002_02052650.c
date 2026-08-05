/*
 * func_ov002_02052650 - fill a 15x15 tilemap region with a running tile index (ARM, reloc-free).
 *
 * For each cell (i, j) in a 15x15 block, writes a BG map entry into the owner's tilemap: the target
 * cell is map[(i + 8) * 32 + j + 0x11] (rows offset down by 8, columns by 0x11 in a 32-wide map) and
 * the value is a tile id that increments in row-major order, (tileBase + i*15 + j + 0x15), OR'd with
 * the 0xc000 palette/priority attribute bits.
 *
 * i*15 is left as `i * 0xf` so mwcc strength-reduces it to an induction variable; the tileBase load
 * is written last in the value expression so it is added after the index terms.
 */
typedef struct {
    char _0[0x14];
    int tileBase;        /* +0x14 */
    char _18[0x2c - 0x18];
    short *map;          /* +0x2c */
} Ov002MapOwner;

void func_ov002_02052650(Ov002MapOwner *owner)
{
    int i, j;
    for (i = 0; i < 0xf; i++) {
        for (j = 0; j < 0xf; j++) {
            owner->map[(i + 8) * 32 + j + 0x11] =
                (j + i * 0xf + 0x15 + owner->tileBase) | 0xc000;
        }
    }
}
