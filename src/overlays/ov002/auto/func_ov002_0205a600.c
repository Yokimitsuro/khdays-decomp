/* True when entry `i` of the two-byte table at +0x32 is both enabled (its bit index at
 * +0x32 is set in the mask at +0x4a8) and has a positive count at +0x33.
 *
 * The count is read BEFORE the mask test -- the ROM's `ldrb r1,[r3,#0x33]` sits above the
 * branch -- and the failure paths share one `return 0` reached with a goto; written the
 * obvious way mwcc predicates the whole thing (ldrbne / cmpne / moveq). */
extern char *data_ov002_0207f620;

int func_ov002_0205a600(int i) {
    char *self = data_ov002_0207f620;
    unsigned char *e = (unsigned char *)(self + i * 2);
    int one = 1;
    int mask = *(int *)(self + 0x4a8) & (one << e[0x32]);
    int v = e[0x33];
    if (mask == 0) {
        goto no;
    }
    if (v > 0) {
        return one;
    }
no:
    return 0;
}
