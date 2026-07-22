/* func_ov008_0208a5e8 -- item-id validity test: an id is valid (1) when it is below 0x201 and
 * is not one of the excluded singletons {1, 0x1a0, 0x1c8, 0x1c9}; otherwise 0. It is the exact
 * complement of func_ov008_0208b7a8, which tests the same four ids.
 *
 * Parked with a two-part diagnosis -- "build 139 collapses `id==0x1a0 || id==1` into a
 * flag-reusing cmpne chain, and range-folds `id==0x1c8 || id==0x1c9` into
 * `(unsigned)(id-0x1c8) <= 1`" -- both accurate about what happens to an `||` chain and both
 * beside the point. The bisecting compare tree with the pooled 0x1c9 is mwcc's SWITCH layout;
 * written as four fall-through cases it comes out byte-exact, collapse and range-fold included,
 * because neither transformation applies to case labels. The `id < 0x201` tail stays an
 * ordinary ternary. */
int func_ov008_0208a5e8(int id) {
    switch (id) {
    case 1:
    case 0x1a0:
    case 0x1c8:
    case 0x1c9:
        return 0;
    }
    return id < 0x201 ? 1 : 0;
}
