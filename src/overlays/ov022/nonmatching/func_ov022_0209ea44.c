/*
 * [nonmatching: byte-extract + search-loop: the low-byte guard (x<<0x18)>>0x18 folds to & 1 and the break-loop rotation does not reproduce (8B short)]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
int func_ov022_0209ea44(int arg0, int arg1, int arg2) {
    int found;
    int i;
    if ((*(unsigned short *)(arg0 + 0x1ac) & 2) != 0 && arg2 != 0 &&
        ((unsigned int)(*(unsigned int *)(arg2 + 8) << 0x18) >> 0x18 & 1) == 0) {
        return 0;
    }
    if ((*(unsigned short *)(arg0 + 0x60) & 1) == 0) {
        return 0;
    }
    if (arg1 == 0) {
        return arg0;
    }
    found = 0;
    i = 0;
    do {
        if ((int)*(short *)(arg1 + i * 2) == (int)*(unsigned short *)(arg0 + 2)) {
            found = 1;
            break;
        }
        i = i + 1;
    } while (i < 8);
    if (found) {
        arg0 = 0;
    }
    return arg0;
}
