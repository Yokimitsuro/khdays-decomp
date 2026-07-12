/* Report whether either of bits 0/3 of the shared status u16 is set. */
extern unsigned short data_0204c190;
int func_ov000_0204d338(void) {
    return (data_0204c190 & 9) != 0;
}
