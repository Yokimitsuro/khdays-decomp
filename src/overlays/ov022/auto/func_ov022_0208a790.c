/* Clears the active entry: zeroes its +4 field and stores 0xFF at +0x110, invalidates the
 * slot index when flag 4 is clear, and clears status bits 3-9 of the halfword at obj[0].
 *
 * The seven single-bit clears must be written as a bitfield struct in the ROM's own order
 * (5,3,4,6,7,8,9) -- that order is load-bearing, not cosmetic.
 */
struct Flags0208a790 {
    unsigned short lo3 : 3;
    unsigned short b3 : 1;
    unsigned short b4 : 1;
    unsigned short b5 : 1;
    unsigned short b6 : 1;
    unsigned short b7 : 1;
    unsigned short b8 : 1;
    unsigned short b9 : 1;
    unsigned short rest : 6;
};

void func_ov022_0208a790(int obj) {
    struct Flags0208a790 *f = (struct Flags0208a790 *)obj;
    if (*(int *)(obj + 0xc) >= 0) {
        *(int *)(*(int *)(obj + *(int *)(obj + 0xc) * 4 + 0x18) + 4) = 0;
        *(signed char *)(*(int *)(obj + *(int *)(obj + 0xc) * 4 + 0x18) + 0x110) = -1;
    }
    if ((*(unsigned short *)obj & 4) == 0)
        *(int *)(obj + 0xc) = -1;
    *(unsigned char *)(obj + 2) = 0;
    f->b5 = 0;
    f->b3 = 0;
    f->b4 = 0;
    f->b6 = 0;
    f->b7 = 0;
    f->b8 = 0;
    f->b9 = 0;
}
