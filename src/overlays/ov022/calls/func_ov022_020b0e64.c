/* func_ov022_020b0e64 -- record a slot id in the global 8x3 "seen" bitmap.
 * The id byte packs three fields: bits 0-2 the bit index inside a byte, bits 3-5 the row
 * (stride 3 bytes) and bits 6-7 the column. Sets that bit in the bitmap at
 * data_ov022_020b2eb8 + 0x2b0, then refreshes the global pointer field via func_02030e50.
 *
 * The three fields are a bitfield STRUCT, not shifts on a loaded byte: mwcc folds a
 * shift pair with equal counts -- `(u << 0x1d) >> 0x1d` -- into a single `and #7`, and only
 * a real bitfield read keeps the ROM's lsl/lsr pair. The other two fields survive either
 * way because their shift counts differ. */
extern int data_ov022_020b2eb8;
extern void func_02030e50(void);

struct Slot020b0e64 {
    unsigned char bit : 3;
    unsigned char row : 3;
    unsigned char col : 2;
};

void func_ov022_020b0e64(unsigned char *arg0) {
    struct Slot020b0e64 *s = (struct Slot020b0e64 *)arg0;
    int g = data_ov022_020b2eb8;
    int row;

    if (g == 0) return;
    row = g + 0x2b0 + s->row * 3;
    *(unsigned char *)(row + s->col) |= 1 << s->bit;
    func_02030e50();
}
