/* Scan the three-bank card grid at +0x19c4 (3 banks of 0x28 slots, 0xa0 apart) for the first
 * card whose id (+0x14) falls in the reaction-command range [0xbf, 0xf0]. On a hit, cache the
 * tier-0x1e record at +0x2078 and answer 1; otherwise 0.
 *
 * Parked as a strength-reduction tie -- mwcc turning the inner `j*4` into a running pointer it
 * has to reset each outer pass. Two things fix it, and both are now general:
 *   - write the slot read as `((int *)(base + 0x19c4))[j]`, so the big displacement stays split
 *     the way the original splits it (`add #0x1000` then a `#0x9c4` load offset) and the index
 *     stays an index;
 *   - declare i, j and base in that order, up front and uninitialised. Register assignment
 *     follows declaration order here, and with base declared before j the two come out
 *     transposed even though everything else is byte-identical. */
extern int func_ov008_02055c84(int obj, int tier);

int func_ov008_0205ffe8(int self) {
    int i;
    int j;
    char *base;
    i = 0;
    base = (char *)self;
    do {
        j = 0;
        do {
            int card = ((int *)(base + 0x19c4))[j];
            if (card != 0) {
                int id = *(int *)(card + 0x14);
                if (id >= 0xbf && id <= 0xf0) {
                    *(int *)(self + 0x2078) = func_ov008_02055c84(self + 0x28c, 0x1e);
                    return 1;
                }
            }
            j++;
        } while (j < 0x28);
        i++;
        base += 0xa0;
    } while (i < 3);
    return 0;
}
