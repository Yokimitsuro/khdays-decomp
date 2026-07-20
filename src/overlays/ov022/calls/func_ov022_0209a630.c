/*
 * Raise the "ready" bit on the node when the global gate is clear, the caller's byte at
 * +0x179 is 1, and the node's own guard bit is not already set.
 *
 * THE PARK SAID THIS WAS UNREPRODUCIBLE FROM CLEAN C.  Its note read the ROM's
 * `ldr ; and r1, r1, #0 ; cmp` as a live load AND-ed with a zeroed register, and the trailing
 * `field[1] = field[1] | 0` as a no-op self-store, and concluded both came from a build-time
 * 0-valued flag macro in a header we do not have.
 *
 * They are two 64-BIT FIELDS.  `and #0` on one word and a real mask on the word beside it is
 * one 64-bit operation, and which word carries the mask tells you where the field starts:
 *   - the guard is `*(long long *)&p[0x119] & 0x400000000` -- the mask sits in the HIGH half,
 *     so the field begins at +0x464 and the tested bit is 4 << 32;
 *   - the set is `*(long long *)p |= 0x80000`, whose high half is the "no-op self-store".
 * Nothing was lost to a missing header, and nothing needed a macro.
 *
 * Worth keeping as a warning about the shape of the wrong conclusion: the note was detailed,
 * confident, and reasoned from a real observation (mwcc does fold a literal `& 0`).  It just
 * never asked what ELSE emits an `and #0`.
 */
extern int data_0204c240;

void func_ov022_0209a630(int arg0, int arg1) {
    unsigned int *p = *(unsigned int **)(arg0 + 0x18c);
    if ((*(unsigned char *)&data_0204c240 & 4) != 0) return;
    if (*(unsigned char *)(arg1 + 0x179) != 1) return;
    if ((*(long long *)&p[0x119] & 0x400000000LL) != 0) return;
    *(long long *)p |= 0x80000;
}
