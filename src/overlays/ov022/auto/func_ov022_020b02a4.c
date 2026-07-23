/* Find or claim the slot for `param2` in the 16-entry table at obj+0x1a8 (stride 0x2c):
 * the first free entry (tag byte -1) is claimed and returned, an entry already tagged
 * with `param2` is returned as is, and a full table with no match returns NULL.
 *
 * Two separate things had to line up, and each one alone leaves the other wrong:
 *   - the DECLARATION order (i, result, slot) colours the callee-saved registers
 *     r4/r5/r6 the way the ROM does;
 *   - the ASSIGNMENT order decides which of the two zeros is materialised and which
 *     is copied. The ROM emits `movs r5,#0` for `result` and then derives i, the load
 *     index and the -1 from it, so `result = 0;` has to be the first statement even
 *     though `i` is declared first. Initialising at the declarations instead makes
 *     mwcc materialise i's zero and copy result from it -- same instructions, wrong
 *     registers throughout. */
char *func_ov022_020b02a4(int obj, int param2) {
    int i;
    char *result;
    char *slot;

    result = 0;
    slot = (char *)(obj + 0x1a8);
    i = 0;
    do {
        if (*slot == -1) {
            *slot = (char)param2;
            result = slot;
            break;
        }
        if (*slot == param2) {
            result = slot;
            break;
        }
        slot += 0x2c;
        i++;
    } while (i < 0x10);
    return result;
}
