/* Read the u16 at +0x434 of the ov006 global object, or 0 if absent. */
extern int data_ov006_020565e4;
int func_ov006_0204fad0(void) {
    if (data_ov006_020565e4 != 0) return *(unsigned short *)(data_ov006_020565e4 + 0x434);
    return 0;
}
