/* Suspends the pair of sub-objects (bit 1 of their flag word at +0x5c) and clears bit 0 of
 * the high nibble of the two mode bytes at +0x398 / +0x39c, then closes the update and
 * releases the pending request at +0x3c4 if there is one.
 *
 * The mode byte is a 4-bit bitfield pair: the ROM's lsl#24 / lsr#28 ... lsl#28 / lsr#24
 * round trip is exactly what `unsigned char hi : 4` generates. */
typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} Nib;

extern void func_ov107_020c7da4(char *self);
extern void func_ov107_020cb100(void *p);

void func_ov278_020cd834(char *self) {
    *(int *)(*(char **)(self + 0x384) + 0x5c) |= 2;
    *(int *)(*(char **)(self + 0x38c) + 0x5c) |= 2;
    ((Nib *)*(char **)(self + 0x398))->hi &= ~1;
    ((Nib *)*(char **)(self + 0x39c))->hi &= ~1;
    func_ov107_020c7da4(self);
    if (*(void **)(self + 0x3c4) == 0) {
        return;
    }
    func_ov107_020cb100(*(void **)(self + 0x3c4));
    *(int *)(self + 0x3c4) = 0;
}
