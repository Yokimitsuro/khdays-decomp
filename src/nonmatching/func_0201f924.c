/* NONMATCHING — register-permutation tie (every instruction matches the original
 * in opcode, operand shape, shift and order; only the register NUMBERS differ).
 *
 * This is a word-at-a-time strcpy (NNS/SDK-style library routine). The full body is
 * byte-shape identical — same push set, alignment prologue, magic zero-byte test
 * ((w-0x01010101) & ~w & 0x80808080), word-copy loop with str writeback, and byte
 * tail. The ROM keeps the long-lived working destination in the caller-saved r2 (it
 * can, being a leaf) and the src alignment in r4; every mwcc build we have swaps
 * those (working dst -> r4, alignment -> r3, byte temp r2 vs r3). From the first
 * `and Rx, src, #3` onward the split is purely which register holds which live value.
 *
 * Proven unsteerable: swept all 27 checked-in mwccarm builds x {-O4,p / -O4,s / -O4 /
 * -O3,p / -O2 / -O4,p,speed} x 2 decl orders — none reproduces the ROM's coloring.
 * Same library-code class as the strcmp at func_0201fabc. Blob keeps build byte-exact.
 *
 * Copy the NUL-terminated string at src into dst and return dst. When src and dst
 * share alignment, copy leading bytes to a word boundary then copy whole words while
 * none of their 4 bytes is zero, else fall back to a byte copy. */
unsigned int *func_0201f924(unsigned int *dst, unsigned int *src) {
    unsigned char c;
    unsigned int *d = dst;
    unsigned int a = (unsigned int)src & 3;
    if (((unsigned int)d & 3) == a) {
        if (a != 0) {
            c = *(unsigned char *)src;
            *(unsigned char *)d = c;
            if (c == 0) return dst;
            {
                int k;
                for (k = 3 - a; k != 0; k--) {
                    src = (unsigned int *)((int)src + 1);
                    c = *(unsigned char *)src;
                    d = (unsigned int *)((int)d + 1);
                    *(unsigned char *)d = c;
                    if (c == 0) return dst;
                }
            }
            d = (unsigned int *)((int)d + 1);
            src = (unsigned int *)((int)src + 1);
        }
        {
            unsigned int m1 = 0xfefefeff;
            unsigned int m2 = 0x80808080;
            unsigned int w = *src;
            if (((w + m1) & ~w & m2) == 0) {
                unsigned int *pd = d - 1;
                do {
                    pd = pd + 1;
                    *pd = w;
                    src = src + 1;
                    w = *src;
                } while (((w + m1) & ~w & m2) == 0);
                d = pd + 1;
            }
        }
    }
    c = *(unsigned char *)src;
    *(unsigned char *)d = c;
    if (c != 0) {
        do {
            src = (unsigned int *)((int)src + 1);
            c = *(unsigned char *)src;
            d = (unsigned int *)((int)d + 1);
            *(unsigned char *)d = c;
        } while (c != 0);
    }
    return dst;
}
