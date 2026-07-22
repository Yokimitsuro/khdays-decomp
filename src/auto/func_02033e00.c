/* Writes the three-word payload into the 32-byte slot selected by the top byte of
 * `handle`, but only while the slot is live (halfword at +0x14) and its stored id at +0x18
 * still matches the handle's low 24 bits. */
struct V3 {
    int x;
    int y;
    int z;
};

extern char *data_0204c234;

void func_02033e00(unsigned int handle, struct V3 *src) {
    char *rec = data_0204c234 + 0xb44e4 + (handle >> 24) * 32;
    if (*(unsigned short *)(rec + 0x14) == 0) {
        return;
    }
    if (*(unsigned int *)(rec + 0x18) == (handle & 0xffffff)) {
        *(struct V3 *)(rec + 8) = *src;
    }
}
