/* Search a 4-entry table of {s16 key1, s16 key2, s16 value}; return the value
 * for the (key1,key2) match, else -1. */
int func_020241b0(short *table, int key1, int key2) {
    int i;
    short *p = table;
    for (i = 0; i < 4; i++) {
        if (key1 == p[0] && key2 == p[1]) {
            return ((short *)((char *)table + i * 6))[2];
        }
        p += 3;
    }
    return -1;
}
