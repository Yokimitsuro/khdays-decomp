/* Maps queue index `i` (0 .. count-1) onto the four-slot ring at +0xb47a2 of the block held
 * by data_0204c234: the slot is (head + count + 3 - i) % 4.  Returns NULL when the index is
 * past the count byte at +0xb47b3.
 *
 * The `% 4` is the point: the ROM's lsr#31 / rsb lsl#30 / add ror#30 triple is mwcc's
 * SIGNED REMAINDER idiom, not a division -- `/ 4` compiles to asr#1 / add lsr#30 / asr#2. */
extern char *data_0204c234;

int *func_02032cbc(int i) {
    char *base = data_0204c234;
    int n = *(unsigned char *)(base + 0xb47b3);
    int q;
    if (i >= n) {
        return 0;
    }
    q = (*(unsigned char *)(base + 0xb47b2) + n + 3 - i) % 4;
    return (int *)(base + 0xb47a2) + (unsigned short)q;
}
