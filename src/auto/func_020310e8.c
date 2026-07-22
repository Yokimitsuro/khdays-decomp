/* Resets the 32-entry, 6-byte-stride table at +0xc of the block held by data_0204c230:
 * every entry's halfword at +4 goes to 0xffff, the header word at +0xc to -1 and the
 * halfword at +0x744 to 0.
 *
 * Two spellings matter: the -1 is written as `i - 1` (the ROM derives it with `sub` from
 * the zeroed counter) while the 0xffff is an UNSIGNED SHORT literal -- as a plain -1 mwcc
 * notices the two constants agree in 16 bits and reuses the register, dropping the pool
 * entry and eight bytes.  And `i` must be declared before `p` to keep the ROM's r3/ip. */
extern char *data_0204c230;

void func_020310e8(void) {
    int i;
    char *p;
    char *base;
    base = data_0204c230;
    p = base + 0xc;
    i = 0;
    *(short *)(p + 0x744) = (short)i;
    *(int *)(base + 0xc) = i - 1;
    do {
        i = i + 1;
        *(unsigned short *)(p + 4) = 0xffff;
        p = p + 6;
    } while (i < 0x20);
}
