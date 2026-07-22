/* func_ov253_020d27f8 -- find the entry whose key (the short at +2) matches, in the 16-entry
 * 4-byte table at +0x3e4 of the object. Returns the entry, or 0.
 * The index must be declared BEFORE the table pointer: that is what colours the index r3 and the
 * table ip as the ROM does (tools/declperm.py, 1 of the 2 orders). */
typedef struct { short pad; short key; } Ov253Entry;

Ov253Entry *func_ov253_020d27f8(int obj, int key) {
    int i;
    Ov253Entry *table;
    table = *(Ov253Entry **)(obj + 0x3e4);
    for (i = 0; i < 0x10; i++) {
        if (key == table[i].key) {
            return &table[i];
        }
    }
    return 0;
}
