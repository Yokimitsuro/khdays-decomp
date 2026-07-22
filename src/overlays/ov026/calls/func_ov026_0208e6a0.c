/* Can this entry be shown? Only when its area is unlocked (the byte at +0x810 of
 * the progress table, indexed by the entry's area id) and its kind is not one of
 * the three hidden ones.
 *
 * The three kinds must be a SWITCH: as `== 4 || == 5 || == 6` mwcc range-folds
 * them into one unsigned compare, while the ROM tests all three with
 * cmp/cmpne/cmpne. */
extern char *data_0204be18;

int func_ov026_0208e6a0(char *self) {
    char *entry = *(char **)(self + 0xc);

    if (*(unsigned char *)(data_0204be18 + *(int *)(entry + 0x14) + 0x810) != 0) {
        switch (*(int *)(entry + 0x18)) {
        case 4:
        case 5:
        case 6:
            return 0;
        }
    }

    return 1;
}
