/* Walks the chunk list looking for the entry with the given id; on a hit it records the entry
 * and the address just past it in the header.
 * `i` is initialised from `found` on purpose: that copy is the ROM's `adds r3, r4, #0`. */
int func_ov002_02067948(int *hdr, unsigned short id) {
    unsigned i;
    int found = 0;
    char *cur = (char *)hdr[1];
    unsigned count = (unsigned)hdr[4];
    i = (unsigned)found;
    while (i < count) {
        if (*(unsigned short *)(cur + 0xc) == id) {
            hdr[2] = (int)cur;
            found = 1;
            hdr[3] = (int)(cur + *(int *)(cur + 8));
            break;
        }
        i++;
        cur += *(int *)cur;
    }
    return found;
}
