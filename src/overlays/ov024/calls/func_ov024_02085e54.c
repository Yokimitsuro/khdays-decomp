/* func_ov024_02085e54 -- MobiClip: bind a bitstream cursor to a source buffer.
 * Caches the source's length (end - start) and its second span (limit - start) so the
 * reader can bounds-check without touching the source object again, and clears the
 * end-of-data flag. */
int func_ov024_02085e54(int cur, int src) {
    *(int *)(cur + 0xc) = src;
    *(int *)(cur + 4) = *(int *)(src + 0x28) - *(int *)(src + 0x24);
    *(int *)(cur + 8) = *(int *)(*(int *)(cur + 0xc) + 0x2c) - *(int *)(*(int *)(cur + 0xc) + 0x24);
    *(char *)(cur + 0x10) = 0;
    return 1;
}
