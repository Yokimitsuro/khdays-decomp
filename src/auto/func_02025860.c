#pragma thumb on
/* Write up to `count` copies of `val` (halfwords) into the buffer at buf[1],
 * clamped to the remaining count buf[0]; advance buf[1] and shrink buf[0]. */
void func_02025860(unsigned int *buf, unsigned short val, unsigned int count) {
    unsigned int i;
    unsigned int n;
    if ((int)count > 0) {
        n = buf[0];
        if (n > count) {
            n = count;
        }
        i = 0;
        if (i < n) {
            int off = i;
            do {
                i++;
                *(unsigned short *)(buf[1] + off) = val;
                off += 2;
            } while (i < n);
        }
        buf[0] = buf[0] - n;
        buf[1] = buf[1] + count * 2;
    }
}
