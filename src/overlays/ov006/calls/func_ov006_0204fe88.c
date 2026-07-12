/* Read the field at (*(&data)) + 0x49c. */
extern int data_ov006_020565e4;
int func_ov006_0204fe88(void) {
    return *(int *)(*(int *)&data_ov006_020565e4 + 0x49c);
}
