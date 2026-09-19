/* Suspends the pair of sub-objects (bit 1 of their flag word at +0x5c, +0x388 / +0x390) and
 * clears bit 0 of the high nibble of the four mode bytes at +0x398 / +0x39c / +0x3a0 / +0x3a4,
 * then tail-calls the base update. */
typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} Nib;

extern void func_ov107_020c7da4(char *self);

void func_ov278_020ce708(char *self) {
    *(int *)(*(char **)(self + 0x388) + 0x5c) |= 2;
    *(int *)(*(char **)(self + 0x390) + 0x5c) |= 2;
    ((Nib *)*(char **)(self + 0x398))->hi &= ~1;
    ((Nib *)*(char **)(self + 0x39c))->hi &= ~1;
    ((Nib *)*(char **)(self + 0x3a0))->hi &= ~1;
    ((Nib *)*(char **)(self + 0x3a4))->hi &= ~1;
    func_ov107_020c7da4(self);
}
