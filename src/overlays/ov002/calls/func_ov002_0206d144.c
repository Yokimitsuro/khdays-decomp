/* Find the index of the key entry that matches, or report that none does.
 *
 * The table header sits at 0x8d14 of the root context: a pointer to the entries and, five bytes
 * in, how many there are. Entries are 0x44 bytes apart and keep their key at 0x40. A miss comes
 * back as -1.
 *
 * The count is declared as the byte it actually is, with the two comparisons casting to int. That
 * is what the original does: an int-typed count swaps the registers holding the count and the
 * entry pointer, and twenty spellings of declaration order and loop form leave that swap in place.
 *
 * Ghidra carries the entry as Ov002KeyEntry, and the two header fields as pKeyEntries and
 * bKeyEntryCount.
 */

typedef unsigned char u8;
typedef short s16;

extern char *data_ov002_0207fa00;

typedef struct {
    char pad0000[0x40];
    s16 nKey;
    char pad0042[2];
} Ov002KeyEntry;

int func_ov002_0206d144(int key) {
    char *table = data_ov002_0207fa00 + 0x8d14;
    int i = 0;
    u8 count = *(u8 *)(table + 5);

    if ((int)count > 0) {
        Ov002KeyEntry *entry = *(Ov002KeyEntry **)table;
        do {
            if (key == entry->nKey) {
                return i;
            }
            i++;
            entry++;
        } while (i < (int)count);
    }
    return -1;
}
