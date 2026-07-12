/* Read the u8 field at (*(&data)) + 0x4ef. */
extern int data_ov006_020565e4;
int func_ov006_0204fe74(void) {
    return *(unsigned char *)(*(int *)&data_ov006_020565e4 + 0x4ef);
}
