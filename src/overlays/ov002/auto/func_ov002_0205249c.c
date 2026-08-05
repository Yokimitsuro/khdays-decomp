/*
 * func_ov002_0205249c - symmetric halfword row-fill (ARM, reloc-free).
 *
 * Writes `val` into a row of the owner's halfword buffer, filling width/2 cells outward from the
 * row centre in both directions: the left half descends from index 0xf and the right half ascends
 * from 0x10. Each row is 32 halfwords, selected by `col`. No-op when width/2 <= 0.
 *
 * `i` is declared before `half` so the loop counter claims the lower register (r4).
 */
typedef struct {
    char _0[0x28];
    short *buf;   /* +0x28 */
} Ov002RowOwner;

void func_ov002_0205249c(Ov002RowOwner *owner, int col, int width, short val)
{
    int i;
    int half = width / 2;
    for (i = 0; i < half; i++) {
        owner->buf[col * 32 + (0xf - i)] = val;
        owner->buf[col * 32 + 0x10 + i] = val;
    }
}
