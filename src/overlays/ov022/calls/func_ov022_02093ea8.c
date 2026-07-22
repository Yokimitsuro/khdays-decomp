/* For each of the four 0x108-byte panels whose bit is set in the dirty mask at +0x1c, copy the
 * three-word block at +0x48c of the shared source, add 0xe00 to its middle word, store it at the
 * panel's +0xc4 and notify the panel's widget at +0x20.
 *
 * Parked as a base-coalescing tie -- the original keeps the object pointer in its own register
 * and reads the two invariant fields through it, while mwcc folded it into the walking pointer
 * and hoisted the addresses. Same two levers as func_ov022_02088830: reach the invariant fields
 * through a STRUCT, and declare the block temp FIRST so the walkers land in the higher
 * callee-saved registers. */
extern void func_0202aa9c(unsigned short *widget);

struct Blk3 { int a, b, c; };

struct Ov022Panel {
    char _pad0[0x1c];
    unsigned int uMask;         /* +0x1c: one dirty bit per panel */
    char _pad20[0x4d8 - 0x20];
    int pSrc;                   /* +0x4d8 */
};

void func_ov022_02093ea8(struct Ov022Panel *self) {
    struct Blk3 tmp;
    unsigned int i;
    char *row;
    unsigned short *dst;

    dst = (unsigned short *)((char *)self + 0x20);
    row = (char *)self;
    i = 0;
    do {
        if ((self->uMask & (1 << i)) != 0) {
            tmp = *(struct Blk3 *)(self->pSrc + 0x48c);
            tmp.b += 0xe00;
            *(struct Blk3 *)(row + 0xc4) = tmp;
            func_0202aa9c(dst);
        }
        i++;
        row += 0x108;
        dst += 0x84;
    } while ((int)i < 4);
}
