/* NONMATCHING: strength-reduction tie. ROM recomputes base+i<<4 inline each iteration and
 * splits +0x390 as add#0x300 + ldrh[#0x90]; our mwcc holds a base copy + increments an induction
 * pointer. Linear id search over a 0xd1-entry 0x10-stride table. */
/* func_ov008_0205da50 -- find the table entry whose id matches, ov008.
 * Scans the 0xd1-entry table at base+0x390 (0x10-byte stride), comparing the caller's id
 * (decremented when positive to a 0-based index) against each entry's u16 id at +0x390;
 * returns the matching entry's address, or 0 if none match. */
int func_ov008_0205da50(int base, unsigned int id) {
    int i;
    if (0 < (int)id) {
        id = id - 1;
    }
    i = 0;
    do {
        int e = base + i * 0x10 + 0x390;
        if (id == *(unsigned short *)e) {
            return e;
        }
        i++;
    } while (i < 0xd1);
    return 0;
}
