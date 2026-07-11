#pragma thumb on
/* Write one byte to the buffer (buf[0]=remaining count, buf[1]=cursor), if room;
 * always advance the cursor. */
void func_02025800(int *buf, unsigned char val) {
    if (buf[0] != 0) {
        *(unsigned char *)buf[1] = val;
        buf[0] = buf[0] - 1;
    }
    buf[1] = buf[1] + 1;
}
