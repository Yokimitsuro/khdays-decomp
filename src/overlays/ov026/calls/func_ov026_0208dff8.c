/* How many of an id's owned copies are still unassigned: start from the per-id counter at
 * +0x810 of the table and decrement it once for every entry equal to that id across the three
 * 0x28-slot id tables (one per 0x50-byte bank, at bank+0xee0), stopping at zero. A negative id
 * has no counter and answers 0.
 *
 * Parked as a strength-reduction tie with "no spelling reproduces the recompute-from-base form".
 * Two spellings do, and they are the same two that unparked func_ov008_0205ffe8:
 *   - `((u16 *)(base + 0xee0))[j]` keeps the index an index and lets mwcc split the displacement
 *     the way the original does (add #0xe00, then a #0xe0 load offset);
 *   - `(base + id)[0x810]`, not `base[id + 0x810]` -- the first gives `add r1,base,id` plus a
 *     0x810 load displacement, the second folds id+0x810 into a register offset.
 * The declaration order (count, i, j, base) is load-bearing too: register assignment follows it,
 * and the other 23 orders are all byte-identical except for which register each local lands in. */
typedef unsigned char u8;
typedef unsigned short u16;

extern u8 *data_0204be18;

int func_ov026_0208dff8(int id) {
    u8 count;
    int i;
    int j;
    u8 *base;

    if (id < 0) {
        return 0;
    }
    base = data_0204be18;
    count = (base + id)[0x810];
    i = 0;
    do {
        j = 0;
        do {
            if (id == ((u16 *)(base + 0xee0))[j] && count != 0) {
                count = count - 1;
            }
            j++;
        } while (j < 0x28);
        i++;
        base += 0x50;
    } while (i < 3);
    return count;
}
