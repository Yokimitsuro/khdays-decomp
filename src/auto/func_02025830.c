#pragma thumb on
/* Byte-fill sibling of func_02025860: write up to `count` copies of `val` (bytes)
 * into buf[1], clamped to the remaining count buf[0]; advance buf[1], shrink buf[0]. */
void func_02025830(unsigned int *buf, unsigned char val, unsigned int count) {
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
                *(unsigned char *)(buf[1] + i) = val;
                i++;
            } while (i < n);
        }
        buf[0] = buf[0] - n;
        buf[1] = buf[1] + count;
    }
}
