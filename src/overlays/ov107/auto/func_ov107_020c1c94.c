/* Counts how many of the *(short *)(self + 0x4c) entries in the 0xc-stride table at +0x51
 * have bit 0 of their flag byte clear.
 *
 * The flag is a BITFIELD (the ROM's lsl#31 / lsr#31), and the declaration order below is the
 * one that colours n->ip, i->r1, c->r2, f->r3 the way the ROM does. */
typedef struct { unsigned char b0 : 1; unsigned char rest : 7; } Flags;
int func_ov107_020c1c94(char *self) {
    int i;
    int c;
    Flags *f;
    int n;
    n = *(short *)(self + 0x4c);
    i = 0;
    c = i;
    if (n > 0) {
        f = (Flags *)(self + 0x51);
        do {
            i = i + 1;
            if (f->b0 == 0) {
                c = c + 1;
            }
            f = (Flags *)((char *)f + 0xc);
        } while (i < n);
    }
    return c;
}
