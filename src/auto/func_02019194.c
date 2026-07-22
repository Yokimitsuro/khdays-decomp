/* Initialises the channel block: copies the global default word into +0xc, takes the
 * channel count from src[0x17] and fills the halfword table at +0x1a with 0x100 | index.
 *
 * The count is re-read from o[0x19] on every iteration (it is the loop bound, and the ROM
 * really does reload it), and the store must be written as an index into the halfword
 * array -- `o + 0x1a + i * 2` makes mwcc build a second induction variable instead of the
 * ROM's `add r1, r0, ip, lsl #1`. */
extern int data_02042494;

void func_02019194(unsigned char *o, int b, unsigned char *src) {
    unsigned int i;
    *(int *)(o + 0xc) = data_02042494;
    o[0x19] = src[0x17];
    *(int *)(o + 8) = b;
    for (i = 0; i < o[0x19]; i++) {
        ((unsigned short *)o)[i + 0xd] = (unsigned short)(i | 0x100);
    }
}
