/*
 * Record the mode on the view and refresh every slot that holds a positive value.
 *
 * The mode byte lands at +0x1a0 and the work is gated on bit 2 of the flag halfword at +0x12.
 * The five slot values are signed shorts at +0x10c; each positive one is refreshed through
 * 0202accc with the block at +0x2c, the slot index as a halfword, the table base, and the mode
 * re-read from where it was just stored, as a signed byte.
 *
 * The index cast belongs INSIDE the subscript. Written outside it, mwcc strength-reduces the
 * array walk into a moving pointer and the function comes out at 66 bytes; with the zero
 * extension to sixteen bits happening per iteration, it recomputes the address exactly as the
 * ROM does.
 */

typedef unsigned char u8;
typedef unsigned short u16;

extern void func_0202accc(void *a, u16 index, void *table, int flag);

void func_ov002_0207a700(char *self, u8 flag) {
    int i;

    *(u8 *)(self + 0x1a0) = flag;
    if ((*(u16 *)(self + 0x12) & 4) != 0) {
        for (i = 0; i < 5; i++) {
            if (((short *)(self + 0x10c))[(u16)i] > 0) {
                func_0202accc(self + 0x2c, (u16)i, self + 0x10c,
                              *(signed char *)(self + 0x1a0));
            }
        }
    }
}
