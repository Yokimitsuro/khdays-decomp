/* strncpy for null-terminated 16-bit strings: copy up to n units from src into
 * dst, stopping right after the terminator, then zero-filling the remainder of the
 * n-unit field. Returns the original dst. The terminator test re-reads the slot it
 * just wrote (store-then-reload), matching the ROM's saved-pointer sequence. */
unsigned short *func_02020104(unsigned short *dst, unsigned short *src, int n) {
    unsigned short *p = dst;
    if (n == 0) return dst;
    do {
        unsigned short *q = p;
        *p++ = *src++;
        if (*(volatile unsigned short *)q == 0) {
            n--;
            if (n != 0) {
                do {
                    *p++ = 0;
                    n--;
                } while (n != 0);
            }
            return dst;
        }
        n--;
    } while (n != 0);
    return dst;
}
