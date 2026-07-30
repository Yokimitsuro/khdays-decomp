/*
 * Table_FindKey - find the entry with a given key in record param_1's key sub-array.
 *
 * The table data_0204c678 holds 0x104-byte records; each record has a sub-array of 0x18 entries
 * (stride 4) at +0x3c whose first halfword is a key. Scans that sub-array for the entry whose key
 * equals param_2 and returns a pointer to it, or NULL when param_2 is 0 or no entry matches.
 * THUMB; the result is a NULL-initialized local returned once (not per-path returns).
 */

extern char data_0204c678[];

unsigned short *func_0203583c(int param_1, unsigned int param_2)
{
    unsigned short *result = 0;
    unsigned short *p;
    int i;

    if (param_2 == 0)
        return result;
    i = 0;
    p = (unsigned short *)(data_0204c678 + param_1 * 0x104 + 0x3c);
    do {
        if (*p == param_2) {
            result = p;
            break;
        }
        i = i + 1;
        p = p + 2;
    } while (i < 0x18);
    return result;
}
