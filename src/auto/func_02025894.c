#pragma thumb on
/* Byte-copy sibling of func_02025860: copy up to `count` bytes from `src` into
 * buf[1], clamped to buf[0]; advance buf[1], shrink buf[0]. */
void func_02025894(unsigned int *buf, char *src, unsigned int count) {
    unsigned int i;
    unsigned int n;
    if ((int)count > 0) {
        n = buf[0];
        if (n > count) {
            n = count;
        }
        i = 0;
        if (i < n) {
            do {
                *(unsigned char *)(buf[1] + i) = src[i];
                i++;
            } while (i < n);
        }
        buf[0] = buf[0] - n;
        buf[1] = buf[1] + count;
    }
}
