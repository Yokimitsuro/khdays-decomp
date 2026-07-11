/* Map an index 0..7 to a mask: 0-3 -> 0xf, 4-7 -> 0x1f, anything else -> -1. */
int func_02024a28(unsigned int x) {
    switch (x) {
        case 0: case 1: case 2: case 3: return 0xf;
        case 4: case 5: case 6: case 7: return 0x1f;
    }
    return -1;
}
