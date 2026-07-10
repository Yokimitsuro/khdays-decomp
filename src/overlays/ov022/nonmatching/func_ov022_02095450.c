/*
 * [nonmatching: shared-body jump-table: cases 2-10 all return 1; mwcc merges the identical returns (20B short) where the original lays a separate jump-table block per case]
 *
 * Equivalent C; mwcc 3.0/139 diverges only in the noted codegen. Left uncarved.
 */
int func_ov022_02095450(int arg0) {
    switch (*(int *)(arg0 + 4)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        return 1;
    default:
        if ((*(unsigned int *)(*(int *)(arg0 + 0x328) + 0x464) & 0x10000) == 0) {
            return 0;
        }
        return 1;
    }
}
