/* Read the u8 field at (*(&data)) + 0x100. */
extern int data_ov006_020565e4;
int func_ov006_0204fa1c(void) {
    return *(unsigned char *)(*(int *)&data_ov006_020565e4 + 0x100);
}
