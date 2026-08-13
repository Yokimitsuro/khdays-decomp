/* Find the next entry whose name matches, resuming from the caller's position.
 *
 * The owner keeps how many entries there are at 0x82 and the table itself at 0xac, with 0x14 bytes
 * per entry and the name at the front. The position is an in-out parameter: on a hit it is left
 * pointing at the match, so the caller can step past it and search again, and on a miss it ends up
 * at the count and the function returns null.
 *
 * The byte offset is declared long rather than int on purpose. Both are 32 bits here, but the int
 * version makes the compiler keep the table in the callee-saved register and spill the offset,
 * where the original does the opposite and copies the index into that register to multiply in
 * place. Declaration order, the multiply written either way round, the compound form, the
 * subscript form and holding the entry in a local all leave it as it was.
 *
 * Ghidra carries the record as Ov002NamedEntry.
 */

typedef unsigned short u16;

extern int strncmp(const char *a, const char *b, int n);

char *func_ov002_020713cc(char *self, const char *name, int length, int *pIndex) {
    if (*pIndex < *(u16 *)(self + 0x82)) {
        do {
            long offset = *pIndex * 0x14;
            char *table = *(char **)(self + 0xac);

            if (strncmp(table + offset, name, length) == 0) {
                return table + offset;
            }
            *pIndex = *pIndex + 1;
        } while (*pIndex < *(u16 *)(self + 0x82));
    }
    return 0;
}
