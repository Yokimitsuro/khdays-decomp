/* Returns slot `i` of the four-entry table data_020429c8 when the index is in range and
 * the slot's first word is non-zero, otherwise NULL.
 *
 * The hit path must be reached by a `goto` so it lands out of line: written as
 * `if (...) return &slot; return 0;` mwcc predicates the hit (addne/bxne) instead of
 * emitting the ROM's `bne` to a separate block.  The table is a struct array so the
 * index scales by 8 in one `lsl #3` rather than through an int index doubled first. */
struct Pair {
    int a;
    int b;
};

extern struct Pair data_020429c8[];

struct Pair *func_020315c0(int i) {
    if (i >= 0 && i < 4 && data_020429c8[i].a != 0) {
        goto hit;
    }
    return 0;
hit:
    return &data_020429c8[i];
}
