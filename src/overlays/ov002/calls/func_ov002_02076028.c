/* Set which physical LCD shows the main engine. While the deferred-swap slot at
 * data_ov002_0207f408 is still armed (non-negative) the request is only parked
 * there and applied later; once it has gone negative the swap goes straight into
 * POWCNT1 bit 15. */
extern int data_ov002_0207f408;

void func_ov002_02076028(int top) {
    volatile unsigned short *reg304;

    if (data_ov002_0207f408 >= 0) {
        data_ov002_0207f408 = top;
        return;
    }

    reg304 = (volatile unsigned short *)0x04000304;
    *reg304 = (*reg304 & ~0x8000) | (top << 15);
}
