/*
 * [nonmatching: shared-body jump-table layout — 92B vs 96B]
 *
 * Value switch mapping {5,6,7,0xb}->1, {8,9}->2, {10}->3, else 0. mwcc does not
 * dedup identical case bodies; the original lays an extra branch-to-default block
 * for the shared r=1/r=2 targets reached by both goto and fall-through that no
 * source case-ordering (grouped or goto-based) reproduces (4B short). Left uncarved.
 */
int func_ov022_02093a1c(int arg0) {
    int r = 0;
    switch (arg0) {
    case 5:
    case 6:
    case 7:
    case 0xb:
        r = 1;
        break;
    case 8:
    case 9:
        r = 2;
        break;
    case 10:
        r = 3;
        break;
    }
    return r;
}
