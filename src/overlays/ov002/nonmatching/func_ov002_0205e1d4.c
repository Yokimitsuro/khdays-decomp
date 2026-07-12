/* NONMATCHING — pool-load scheduling tie (28/28), twin of func_ov002_0205e1b8:
 * same code, reads the u16 at slot+2. The original loads both literal-pool words up
 * front then dereferences the global; mwcc dereferences first and loads the offset
 * pool afterward (base register r2->r1). Byte-identical past the prologue; unsteerable
 * pool/register scheduling. Blob keeps the build byte-exact. */
extern int data_ov002_0207f620;

unsigned int func_ov002_0205e1d4(void) {
    int base = *(int *)&data_ov002_0207f620;
    int slot = *(int *)(base + 0x4a4);
    unsigned int r = 0;

    if (slot != 0) {
        r = *(unsigned short *)(slot + 2);
    }
    return r;
}
