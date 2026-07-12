/* Read the byte at +0x4f0 of the ov006 global object. */
extern int data_ov006_020565e4;
int func_ov006_0204fe9c(void) {
    return *(unsigned char *)(data_ov006_020565e4 + 0x4f0);
}
