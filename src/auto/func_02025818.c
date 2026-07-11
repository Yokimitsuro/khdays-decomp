#pragma thumb on
/* Write one halfword to the buffer (buf[0]=remaining count, buf[1]=cursor), if
 * room; always advance the cursor by 2. */
void func_02025818(int *buf, unsigned short val) {
    if (buf[0] != 0) {
        *(unsigned short *)buf[1] = val;
        buf[0] = buf[0] - 1;
    }
    buf[1] = buf[1] + 2;
}
