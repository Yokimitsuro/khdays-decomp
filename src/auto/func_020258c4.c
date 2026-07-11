#pragma thumb on
/* Halfword-copy sibling of func_02025860: copy up to `count` halfwords from `src`
 * into buf[1], clamped to buf[0]; advance buf[1], shrink buf[0]. */
void func_020258c4(unsigned int *buf, unsigned short *src, unsigned int count) {
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
                *(unsigned short *)(buf[1] + off) = *src;
                src++;
                off += 2;
            } while (i < n);
        }
        buf[0] = buf[0] - n;
        buf[1] = buf[1] + count * 2;
    }
}
