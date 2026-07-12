/* Report the +0x498 busy flag or, when idle, bit 1 of the +0x42c byte. */
extern int data_ov006_020565e4;
struct bf_byte { unsigned char b0:1, b1:1; };
int func_ov006_0204fe4c(void) {
    if (*(int *)(data_ov006_020565e4 + 0x498) != 0) return 1;
    return ((struct bf_byte *)(data_ov006_020565e4 + 0x42c))->b1;
}
