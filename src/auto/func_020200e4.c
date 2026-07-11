/* strcpy for null-terminated 16-bit (UTF-16) strings: copy src into dst and
 * return the original dst. The loop's terminator test re-reads the slot it just
 * wrote (store-then-reload), matching the ROM's saved-pointer sequence. */
unsigned short *func_020200e4(unsigned short *dst, unsigned short *src) {
    unsigned short *p = dst, *q;
    unsigned short v;
    do {
        q = p++;
        *q = *src++;
        v = *(volatile unsigned short *)q;
    } while (v != 0);
    return dst;
}
