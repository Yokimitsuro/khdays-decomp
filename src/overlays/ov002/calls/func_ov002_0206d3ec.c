/* Set or clear one seat's bit in the flag byte at +0x8c98. The byte is cleared
 * and stored, then re-read and OR-ed -- two separate read-modify-writes, not one.
 *
 * The `on` argument is normalised through an if/else that materialises 1 and 0
 * on separate paths; writing it as `on != 0` folds into a single compare and
 * comes out short. The OR-ed value is narrowed to a byte before the shift result
 * is applied, which is the lsl #24 / lsr #24 pair. */
typedef struct {
    char pad0000[4];
    unsigned char bFlags;   /* +4 */
} Ov002SeatFlags;

extern char *data_ov002_0207fa00;

void func_ov002_0206d3ec(int seat, int on) {
    Ov002SeatFlags *p = (Ov002SeatFlags *)(data_ov002_0207fa00 + 0x8c94);
    int value;

    if (on != 0) {
        value = 1;
    } else {
        value = 0;
    }

    p->bFlags &= ~(1 << seat);
    p->bFlags |= (unsigned char)(value << seat);
}
