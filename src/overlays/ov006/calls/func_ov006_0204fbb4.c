/* Read the 1-bit flag at bit 0 of the word at +0x4a8 of the ov006 global object. */
extern int data_ov006_020565e4;
struct bf006 { unsigned int b0 : 1; };
int func_ov006_0204fbb4(void) {
    return ((struct bf006 *)(data_ov006_020565e4 + 0x4a8))->b0;
}
