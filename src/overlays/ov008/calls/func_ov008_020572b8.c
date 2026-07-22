/* Map a menu page id to its icon row. Ids 1 and 7 have no icon and report 0,
 * which is also the answer above 8.
 *
 * Case 1 must assign the default EXPLICITLY (`r = 0`) rather than being an empty
 * case: written empty, mwcc folds its jump-table entry into the default target,
 * while the ROM points it at case 8's break. Case order in the source is
 * 0, 8, 1, 2..6, and that is the order the bodies appear in. */
int func_ov008_020572b8(int page) {
    int r = 0;

    switch (page) {
    case 0: r = 6; break;
    case 8: r = 7; break;
    case 1: r = 0; break;
    case 2: r = 1; break;
    case 3: r = 2; break;
    case 4: r = 3; break;
    case 5: r = 4; break;
    case 6: r = 5; break;
    }

    return r;
}
