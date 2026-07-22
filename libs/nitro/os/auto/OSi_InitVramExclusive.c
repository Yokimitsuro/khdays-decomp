/* Clears the VRAM exclusive-owner table and its request word.
 * The stored zero is taken FROM the counter (`z = i`), which is the ROM's `mov r2, r3`,
 * and the halfword store is an array index so the offset is re-derived every iteration. */
extern int data_02044698[];
extern unsigned short data_0204469c[];

void OSi_InitVramExclusive(void) {
    int i = 0;
    int z = i;
    data_02044698[0] = z;
    do {
        data_0204469c[i] = (unsigned short)z;
        i = i + 1;
    } while (i < 9);
}
