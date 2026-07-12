/* NONMATCHING — pool-load scheduling tie (28/28 bytes, byte-identical after the first
 * three instructions). The original loads both literal-pool words up front (&global
 * into r0, the 0x4a4 offset into r1) and only then dereferences the global into r2;
 * mwcc instead dereferences the global first (into r1) and loads the 0x4a4 pool
 * afterward, shifting the base register r2->r1. Every later byte matches. Unsteerable
 * pool/register scheduling; the raw blob keeps the build byte-exact.
 *
 * Read the u16 at the object referenced by (*global)+0x4a4, or 0 when null.
 */
extern int data_ov002_0207f620;

unsigned int func_ov002_0205e1b8(void) {
    int base = *(int *)&data_ov002_0207f620;
    int slot = *(int *)(base + 0x4a4);
    unsigned int r = 0;

    if (slot != 0) {
        r = *(unsigned short *)slot;
    }
    return r;
}
