/* func_ov023_02089208 -- is this slot free? Mode 0 asks about the handle at +0x15d8; any other
 * mode asks about the pair at +0x53c (a -1 id) and +0x544 (a zero state byte). */
int func_ov023_02089208(int obj, int mode) {
    if (mode == 0) {
        if (*(int *)(obj + 0x15d8) == 0) {
            return 1;
        }
        return 0;
    }
    if (*(short *)(obj + 0x53c) == -1 && *(signed char *)(obj + 0x544) == 0) {
        return 1;
    }
    return 0;
}
